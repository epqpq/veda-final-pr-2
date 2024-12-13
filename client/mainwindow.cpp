#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_addclientwidget.h"
#include "ui_selecteclientlist.h"
#include "clickeventfilter.h"
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), selectDialog(std::make_unique<QDialog>(this)), videoPlayer(std::make_unique<QMediaPlayer>()), monitor(std::make_unique<FtpMonitor>()),
    widgetCount(0), enlargementFlag(false), videoPlayFlag(false)
{
    ui->setupUi(this);

    // Set main window to full screen size
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        this->setGeometry(screenGeometry);
    }
    setFixedSize(this->width(), this->height());

    // Setup video player
    videoPlayer->setVideoOutput(ui->cctvVideoPlayer);

    // Initialize client list widget
    selectClientList = new Ui::SelecteClientList();
    selectClientList->setupUi(selectDialog.get());

    // Connect functions
    connect(ui->menu, &QTreeWidget::itemClicked, this, &MainWindow::selectMenu);
    connect(ui->registerClientBtn, &QPushButton::clicked, this, &MainWindow::registerClient);
    connect(ui->deleteClientBtn, &QPushButton::clicked, this, &MainWindow::deleteClient);
    connect(ui->connectClientBtn, &QPushButton::clicked, this, &MainWindow::connectClient);
    connect(ui->openWidgetBtn, &QPushButton::clicked, this, [this]() {
        selectClient(false);
    });
    connect(ui->closeWidgetBtn, &QPushButton::clicked, this, [this]() {
        selectClient(true);
    });
    connect(ui->searchFileBtn, &QPushButton::clicked, this, &MainWindow::setFilePath);

    connect(videoPlayer.get(), &QMediaPlayer::durationChanged, this, [=](qint64 duration) {
        ui->progressBar->setRange(0, duration);
    });
    connect(videoPlayer.get(), &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->progressBar->setValue(position);
    });
    connect(ui->progressBar, &QSlider::sliderMoved, this, [=](int position) {
        videoPlayer->setPosition(position);
    });
    connect(ui->videoPlayBtn, &QPushButton::clicked, this, &MainWindow::playVideo);
    connect(ui->videoSpeedUpBtn, &QPushButton::clicked, this, &MainWindow::speedUpVideo);
    connect(ui->videoSpeedDownBtn, &QPushButton::clicked, this, &MainWindow::speedDownVideo);
}

MainWindow::~MainWindow() {
    clientList.clear();

    delete selectClientList;
    delete ui;
}

void MainWindow::selectMenu(QTreeWidgetItem* item, int column) {
    QString selectedText = item->text(column);

    if (selectedText == "CCTV") {}
    else if (selectedText == "- CCTV") {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (selectedText == "- 추가") {
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if (selectedText == "기능 설정") {

    }
    else if (selectedText == "녹화 영상 확인") {
        ui->stackedWidget->setCurrentIndex(5);
    }
    else if (selectedText == "FTP") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (selectedText == "로그") {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

// register client
void MainWindow::registerClient() {
    QDialog* dialog = new QDialog(this);
    Ui::addClientWidget addClientUi;
    addClientUi.setupUi(dialog);

    connect(addClientUi.registerClientBtn, &QPushButton::clicked, [dialog, &addClientUi, this]() {
        QString id = addClientUi.idLine->text();
        QString ip = addClientUi.ipLine->text();

        if (id.isEmpty() || ip.isEmpty()) {
            QMessageBox::warning(dialog, "Warning", "ID와 IP를 입력하세요.");
            delete dialog;
            return;
        }

        // 중복 ID, IP 방지
        for (int row = 0; row < ui->clientTable->rowCount(); ++row) {
            QString existingId = ui->clientTable->item(row, 0)->text();
            QString existingIp = ui->clientTable->item(row, 1)->text();

            if (existingId == id) {
                QMessageBox::warning(dialog, "Warning", "이미 등록된 ID입니다.");
                delete dialog;
                return;
            }

            if (existingIp == ip) {
                QMessageBox::warning(dialog, "Warning", "이미 등록된 IP입니다.");
                delete dialog;
                return;
            }
        }

        int currentRow = ui->clientTable->rowCount();
        ui->clientTable->insertRow(currentRow);
        ui->clientTable->setItem(currentRow, 0, new QTableWidgetItem(id));
        ui->clientTable->setItem(currentRow, 1, new QTableWidgetItem(ip));
        ui->clientTable->setItem(currentRow, 2, new QTableWidgetItem("Not Connected"));

        dialog->accept();
        dialog->deleteLater();
    });

    dialog->exec();
}

void MainWindow::deleteClient() {
    QList<QTableWidgetItem*> selectedItem = ui->clientTable->selectedItems();
    if (selectedItem.isEmpty()) {
        QMessageBox::warning(this, "Error", "삭제할 클라이언트를 선택하세요");
        return;
    }

    int selectedRow = selectedItem.first()->row();
    QTableWidgetItem* id = ui->clientTable->item(selectedRow, 0);
    if (!id) {
        QMessageBox::warning(this, "Error", "유효하지 않은 클라이언트 데이터입니다");
        return;
    }

    QString clientId = id->text();
    // qDebug() << "삭제 요청 ID:" << clientId;

    auto it = std::find_if(clientList.begin(), clientList.end(),
                           [&clientId](const std::pair<std::shared_ptr<Client>, int>& clientPair) {
                               return clientPair.first->getClientID() == clientId;
                           });

    if (it != clientList.end()) {
        auto& selectedClient = it->first;
        // qDebug() << "삭제 중인 클라이언트 ID:" << selectedClient->getClientID();

        GstreamerClient* gstreamerClient = selectedClient->getGstreamerClient();
        if (gstreamerClient) {
            gstreamerClient->setParent(nullptr);
            gstreamerClient->hide();
        }

        // QStackedWidget에서 해당 Page 제거
        for (int i = 0; i < ui->stackedWidget->count(); ++i) {
            QWidget* page = ui->stackedWidget->widget(i);
            QLineEdit* idText = page->findChild<QLineEdit*>("idText");
            if (idText && idText->text() == clientId) {
                ui->stackedWidget->removeWidget(page);
                delete page; // Page 삭제
                break;
            }
        }

        // QTreeWidget에서 해당 항목 제거
        QTreeWidgetItem* parentPage = nullptr;
        for (int i = 0; i < ui->menu->topLevelItemCount(); ++i) {
            QTreeWidgetItem* item = ui->menu->topLevelItem(i);
            if (item->text(0) == "기능 설정") {
                parentPage = item;
                break;
            }
        }

        if (parentPage) {
            for (int i = 0; i < parentPage->childCount(); ++i) {
                QTreeWidgetItem* child = parentPage->child(i);
                if (child->text(0) == QString("- %1").arg(selectedClient->getServerIp())) {
                    delete parentPage->takeChild(i);
                    break;
                }
            }
        }
        qDebug() << "남은 클라이언트 수 :" << clientList.size();
        // clientList의 요소를 삭제하기 전에 해당 요소의 포인터가 UI 요소와 연결된 상태라면, 이로 인해 비정상 종료가 발생할 가능성이 있습니다.
        // clientList.erase(it); // 클라이언트 삭제
        qDebug() << "남은 클라이언트 수:" << clientList.size();
    }
    ui->clientTable->removeRow(selectedRow);
}

// Gstreamer 연결이 끊겼을 경우 client 삭제
void MainWindow::handleClientDisconnected(const QString& clientID)
{
    qDebug() << "클라이언트 연결 끊김 처리 중: ID =" << clientID;

    // 클라이언트 리스트에서 삭제
    auto it = std::find_if(clientList.begin(), clientList.end(),
                           [&clientID](const std::pair<std::shared_ptr<Client>, int>& clientPair) {
                               return clientPair.first->getClientID() == clientID;
                           });

    if (it != clientList.end()) {
        auto& client = it->first; // shared_ptr<Client>
        qDebug() << "삭제 중인 클라이언트 ID:" << client->getClientID();

        // GstreamerClient 처리
        GstreamerClient* gstreamerClient = client->getGstreamerClient();
        if (gstreamerClient) {
            gstreamerClient->setParent(nullptr);
            gstreamerClient->hide();
        }

        // QStackedWidget에서 해당 Page 제거
        for (int i = 0; i < ui->stackedWidget->count(); ++i) {
            QWidget* page = ui->stackedWidget->widget(i);
            QLineEdit* idText = page->findChild<QLineEdit*>("idText");
            if (idText && idText->text() == clientID) {
                ui->stackedWidget->removeWidget(page);
                delete page; // Page 삭제
                break;
            }
        }

        // QTreeWidget에서 해당 항목 제거
        QTreeWidgetItem* parentPage = nullptr;
        for (int i = 0; i < ui->menu->topLevelItemCount(); ++i) {
            QTreeWidgetItem* item = ui->menu->topLevelItem(i);
            if (item->text(0) == "기능 설정") {
                parentPage = item;
                break;
            }
        }

        if (parentPage) {
            for (int i = 0; i < parentPage->childCount(); ++i) {
                QTreeWidgetItem* child = parentPage->child(i);
                if (child->text(0) == QString("- %1").arg(client->getServerIp())) {
                    delete parentPage->takeChild(i); // 트리 항목 제거
                    break;
                }
            }
        }
        // clientList.erase(it);
        qDebug() << "남은 클라이언트 수:" << clientList.size();
    }
    else {
        qDebug() << "삭제하려는 클라이언트를 찾을 수 없습니다: ID =" << clientID;
    }
}


void MainWindow::connectClient() {
    // select cilent to connect
    QList<QTableWidgetItem*> selectedClient = ui->clientTable->selectedItems();
    if (selectedClient.isEmpty()) {
        QMessageBox::warning(this, "Warning", "연결할 항목을 선택하세요");
        return;
    }

    int selectedIndex = selectedClient.first()->row();
    QTableWidgetItem* id = ui->clientTable->item(selectedIndex, 0);
    QTableWidgetItem* ip = ui->clientTable->item(selectedIndex, 1);
    QTableWidgetItem* connectStatus = ui->clientTable->item(selectedIndex, 2);

    if (!id || !ip) {
        QMessageBox::warning(this, "Warning", "선택된 행에 데이터가 없습니다");
        return;
    }

    QString clientId = id->text();
    QString clientIp = ip->text();

    // Check if already connected
    if (connectStatus && connectStatus->text() == "Connected") {
        QMessageBox::warning(this, "Warning", "이미 연결된 클라이언트입니다");
        return;
    }

    // connect to client
    bool connectFlag = addClient(clientIp, clientId);
    if (!connectStatus) {
        connectStatus = new QTableWidgetItem();
        ui->clientTable->setItem(selectedIndex, 2, connectStatus);
    }

    if (connectFlag) {
        connectStatus->setText("Connected");
    }
    else {
        connectStatus->setText("Not Connected");
    }
}

bool MainWindow::addClient(QString& ip, QString& id) {
    QString pipelineStr = QString(PIPELINE).arg(id);
    auto client = std::make_unique<Client>();

    client->configureClient(pipelineStr, ip, id);
    if (!client->connectToServer()) {
        QMessageBox::warning(this, "Error", "클라이언트 서버 연결에 실패했습니다");
        return false;
    }

    clientList.push_back({std::move(client), -1});
    auto& addedClient = clientList.back().first;
    addClientTab(addedClient.get());
    connect(addedClient.get(), &Client::handleLogMessage, this, &MainWindow::appendLogMessage);
    connect(client.get(), &Client::clientDisconnected, this, &MainWindow::handleClientDisconnected);

    return true;
}


void MainWindow::addClientTab(Client* client) {
    QWidget* newClientPage = new QWidget(ui->stackedWidget);
    QVBoxLayout* newClientLayout = new QVBoxLayout(newClientPage);

    QWidget* clientSettingWidget = new QWidget(newClientPage);
    clientSettingWidget->setObjectName("clientSettingWidget");

    QCheckBox* motionDetectCheckBox = new QCheckBox("Motion Detect", clientSettingWidget);
    motionDetectCheckBox->setObjectName("motionDetectCheckBox");
    motionDetectCheckBox->setGeometry(20, 120, 171, 22);
    motionDetectCheckBox->setChecked(true);

    QCheckBox* fireDetectCheckBox = new QCheckBox("Fire Detect", clientSettingWidget);
    fireDetectCheckBox->setObjectName("fireDetectCheckBox");
    fireDetectCheckBox->setGeometry(20, 170, 78, 22);
    fireDetectCheckBox->setChecked(true);

    QCheckBox* recordingCheckBox = new QCheckBox("Recording", clientSettingWidget);
    recordingCheckBox->setObjectName("recordingCheckBox");
    recordingCheckBox->setGeometry(20, 220, 78, 22);
    recordingCheckBox->setChecked(true);

    connect(motionDetectCheckBox, &QCheckBox::toggled, this, [client] {
        if (!client->setMotionDetectOnOff()) {
            qWarning() << "Failed to turn motion detection";
        }
    });
    connect(fireDetectCheckBox, &QCheckBox::toggled, this, [client] {
        if (!client->setFireDetectOnOff()) {
            qWarning() << "Failed to turn fire detection";
        }
    });
    connect(recordingCheckBox, &QCheckBox::toggled, this, [client] {
        if (!client->setRecordOnOff()) {
            qWarning() << "Failed to turn recording";
        }
    });

    QLabel* idLabel = new QLabel("ID", clientSettingWidget);
    idLabel->setObjectName("idLabel");
    idLabel->setGeometry(10, 10, 50, 16);

    QLineEdit* idText = new QLineEdit(clientSettingWidget);
    idText->setObjectName("idText");
    idText->setGeometry(70, 10, 231, 24);
    idText->setText(client->getClientID());

    QLabel* ipLabel = new QLabel("IP", clientSettingWidget);
    ipLabel->setObjectName("ipLabel");
    ipLabel->setGeometry(10, 50, 50, 16);

    QLineEdit* ipText = new QLineEdit(clientSettingWidget);
    ipText->setObjectName("ipText");
    ipText->setGeometry(70, 50, 231, 24);
    ipText->setText(client->getServerIp());

    newClientLayout->addWidget(clientSettingWidget);

    ui->stackedWidget->addWidget(newClientPage);

    QTreeWidgetItem* parentPage = nullptr;
    for (int i = 0; i < ui->menu->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = ui->menu->topLevelItem(i);
        if (item->text(0) == "기능 설정") {
            parentPage = item;
            break;
        }
    }

    if (parentPage) {
        QTreeWidgetItem* clientItem = new QTreeWidgetItem(parentPage);
        clientItem->setText(0, QString("- %1").arg(client->getServerIp()));

        connect(ui->menu, &QTreeWidget::itemClicked, this, [this, newClientPage, clientItem](QTreeWidgetItem* item, int) {
            if (item == clientItem) {
                ui->stackedWidget->setCurrentWidget(newClientPage);
            }
        });

        parentPage->setExpanded(true);
    }
    else {
        qWarning() << "기능 설정 항목을 찾을 수 없습니다.";
    }
}

void MainWindow::selectClient(bool mode) {
    selectClientList->clientListWidget->clear();
    if (clientList.empty()) {
        QMessageBox::warning(this, "Error", "등록된 클라이언트가 없습니다");
        return;
    }

    for (int i = 0; i < clientList.size(); i++) {
        QString clientInfo = QString("%1").arg(clientList[i].first->getClientID());
        selectClientList->clientListWidget->addItem(clientInfo);
    }

    disconnect(selectClientList->clientListWidget, &QListWidget::itemClicked, nullptr, nullptr);
    // client open mode
    if (mode) {
        connect(selectClientList->clientListWidget, &QListWidget::itemClicked, this, &MainWindow::closeClientWidget);
    }
    // client close mode
    else {
        connect(selectClientList->clientListWidget, &QListWidget::itemClicked, this, &MainWindow::openClientWidget);
    }

    selectDialog->exec();
}

// 선택한 widget 확대
void MainWindow::enlargeClientWidget(Client* selectedClient) {
    if (!enlargementFlag) {
        // 부모 위젯 크기 계산
        int parentWidth = ui->cctvMainPage->width();
        int parentHeight = ui->cctvMainPage->height();

        int x = (parentWidth - ENLARGE_WIDTH) / 2;
        int y = (parentHeight - ENLARGE_HEIGHT) / 2;

        // 선택한 위젯 확대
        GstreamerClient* selectedWidget = selectedClient->getGstreamerClient();
        if (selectedWidget) {
            selectedWidget->setGeometry(x, y, ENLARGE_WIDTH, ENLARGE_HEIGHT);
            selectedWidget->setMinimumSize(ENLARGE_WIDTH, ENLARGE_HEIGHT);
            selectedWidget->setMaximumSize(ENLARGE_WIDTH, ENLARGE_HEIGHT);
            selectedWidget->raise();
            selectedWidget->show();
        }

        enlargementFlag = true;

        // 다른 클라이언트의 위젯 숨기기
        for (auto& client : clientList) {
            if (client.first.get() != selectedClient) {
                GstreamerClient* otherWidget = client.first->getGstreamerClient();
                if (otherWidget) {
                    otherWidget->hide();
                }
            }
        }
    }
    else {
        enlargementFlag = false;

        // 선택한 위젯 축소
        GstreamerClient* selectedWidget = selectedClient->getGstreamerClient();
        if (selectedWidget) {
            selectedWidget->setMinimumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
            selectedWidget->setMaximumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
        }

        // 다른 위젯 복원
        for (auto& client : clientList) {
            GstreamerClient* otherWidget = client.first->getGstreamerClient();
            if (otherWidget) {
                int idx = client.second;
                if (idx >= 0) {
                    int x = widgetPos[idx][0];
                    int y = widgetPos[idx][1];
                    otherWidget->setGeometry(x, y, WIDGET_WIDTH, WIDGET_HEIGHT);
                    otherWidget->show();
                }
            }
        }
    }
    update();
}

void MainWindow::openClientWidget() {
    if (widgetCount >= 4) {
        QMessageBox::warning(this, "Error", "최대 4개만 열 수 있습니다");
        return;
    }

    QListWidgetItem* selectedItem = selectClientList->clientListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "클라이언트를 선택하세요");
        return;
    }

    int selectedIndex = selectClientList->clientListWidget->currentRow();
    if (selectedIndex < 0 || selectedIndex >= clientList.size()) {
        QMessageBox::warning(this, "Error", "유효하지 않은 선택입니다");
        return;
    }

    if (clientList[selectedIndex].second >= 0) {
        QMessageBox::information(this, "Info", "이미 열려 있습니다");
        return;
    }

    auto& selectedClient = clientList[selectedIndex].first; // 참조로 사용
    GstreamerClient* gstreamerWidget = selectedClient->getGstreamerClient();
    if (!gstreamerWidget) {
        QMessageBox::warning(this, "Error", "Gstreamer 위젯을 초기화할 수 없습니다");
        return;
    }

    // 설정 위젯
    gstreamerWidget->setParent(ui->cctvMainPage);
    gstreamerWidget->setMinimumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    gstreamerWidget->setMaximumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    gstreamerWidget->move(widgetPos[widgetCount][0], widgetPos[widgetCount][1]);
    gstreamerWidget->show();

    // 클릭 이벤트 필터
    auto clickFilter = new ClickEventFilter(gstreamerWidget);
    gstreamerWidget->installEventFilter(clickFilter);

    connect(clickFilter, &ClickEventFilter::clicked, this, [=]() {
        enlargeClientWidget(selectedClient.get());
    });

    clientList[selectedIndex].second = widgetCount;
    widgetCount++;

    selectDialog->close();
}


void MainWindow::closeClientWidget() {
    if (widgetCount <= 0) {
        QMessageBox::information(this, "Info", "현재 열려 있는 화면이 없습니다.");
        return;
    }

    QListWidgetItem* selectedItem = selectClientList->clientListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "클라이언트를 선택하세요");
        return;
    }

    int selectedIndex = selectClientList->clientListWidget->currentRow();
    if (selectedIndex < 0 || selectedIndex >= clientList.size()) {
        QMessageBox::warning(this, "Error", "유효하지 않은 선택입니다");
        return;
    }

    if (clientList[selectedIndex].second < 0) {
        QMessageBox::warning(this, "Error", "열려 있지 않습니다");
        return;
    }

    auto& selectedClient = clientList[selectedIndex].first;
    GstreamerClient* gstreamerWidget = selectedClient->getGstreamerClient();
    if (!gstreamerWidget) {
        QMessageBox::warning(this, "Error", "위젯이 존재하지 않습니다");
        return;
    }

    int idx = clientList[selectedIndex].second;

    // 위젯 숨기기 및 부모 해제
    gstreamerWidget->setParent(nullptr);
    gstreamerWidget->hide();

    clientList[selectedIndex].second = -1;

    // 다른 클라이언트 위젯 위치 조정
    for (auto& client : clientList) {
        if (client.second > idx) {
            client.second--;
            GstreamerClient* updateWidget = client.first->getGstreamerClient();
            if (updateWidget) {
                int x = widgetPos[client.second][0];
                int y = widgetPos[client.second][1];
                updateWidget->move(x, y);
            }
        }
    }
    widgetCount--;
}

void MainWindow::setFilePath() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select a File", "C:/", "Video Files (*.mp4 *.avi *.mkv *.mov *.wmv);;All Files (*.*)");
    if (!filePath.isEmpty()) {
        ui->filePath->setText(filePath);
        videoPlayer->setSource(QUrl::fromLocalFile(filePath));

        videoPlayer->play();
    }
}



void MainWindow::playVideo() {
    // 영상이 재생 중일때
    if (videoPlayFlag) {
        videoPlayer->pause();
        ui->videoPlayBtn->setText("⏸");
        videoPlayFlag = false;
    }
    // 영상이 정지 중일때
    else {
        videoPlayer->play();
        ui->videoPlayBtn->setText("▶");
        videoPlayFlag = true;
    }
}

// 영상 빠르게 배속
void MainWindow::speedUpVideo() {
    qreal currentRate = videoPlayer->playbackRate();
    videoPlayer->setPlaybackRate(currentRate + 0.5);
    ui->videoPlayRateLabel->setText(QString("%1x").arg(videoPlayer->playbackRate(), 0, 'f', 1));
}

// 영상 느리게 배속
void MainWindow::speedDownVideo() {
    const qreal minRate = 0.2;
    qreal currentRate = videoPlayer->playbackRate();
    qreal newRate = currentRate - 0.5;
    if (newRate < minRate) {
        newRate = minRate;
    }
    videoPlayer->setPlaybackRate(newRate);
    ui->videoPlayRateLabel->setText(QString("%1x").arg(newRate, 0, 'f', 1));
}

// 로그 메세지 입력
void MainWindow::appendLogMessage(const QString& message)
{
    if (ui->logTextEdit) {
        ui->logTextEdit->append(message);
    }
}
