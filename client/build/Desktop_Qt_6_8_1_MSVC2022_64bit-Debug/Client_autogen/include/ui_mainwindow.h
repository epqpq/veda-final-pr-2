/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QTreeWidget *menu;
    QStackedWidget *stackedWidget;
    QWidget *cctvMainPage;
    QPushButton *openWidgetBtn;
    QPushButton *closeWidgetBtn;
    QWidget *FtpPage;
    QGroupBox *groupBoxConnection;
    QGridLayout *gridLayoutConnection;
    QLabel *labelUrl;
    QLineEdit *lineEditUrl;
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QPushButton *connectBtn;
    QGroupBox *groupBoxDownload;
    QGridLayout *gridLayoutDownload;
    QLabel *labelRemoteFile;
    QLineEdit *lineEditRemoteFileDownload;
    QLabel *labelLocalFileDownload;
    QLineEdit *lineEditLocalFileDownload;
    QPushButton *downloadBtn;
    QWidget *logPage;
    QTextEdit *logTextEdit;
    QWidget *clientManagePage;
    QWidget *registerClientWidget;
    QPushButton *registerClientBtn;
    QPushButton *deleteClientBtn;
    QTableWidget *clientTable;
    QPushButton *connectClientBtn;
    QWidget *settingsPage;
    QVBoxLayout *settingsLayout;
    QWidget *recordingsPage;
    QVBoxLayout *recordingsLayout;
    QWidget *recordingWidget;
    QVideoWidget *cctvVideoPlayer;
    QLineEdit *filePath;
    QPushButton *searchFileBtn;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *videoSpeedDownBtn;
    QPushButton *videoPlayBtn;
    QPushButton *videoSpeedUpBtn;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *progressBar;
    QLabel *videoPlayRateLabel;
    QWidget *cctvMainWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1440, 900);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        menu = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(menu);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(menu);
        new QTreeWidgetItem(menu);
        new QTreeWidgetItem(menu);
        new QTreeWidgetItem(menu);
        menu->setObjectName("menu");
        menu->setEnabled(true);
        sizePolicy.setHeightForWidth(menu->sizePolicy().hasHeightForWidth());
        menu->setSizePolicy(sizePolicy);
        menu->setMinimumSize(QSize(256, 400));
        QFont font;
        font.setPointSize(10);
        menu->setFont(font);
        menu->setHeaderHidden(true);

        mainLayout->addWidget(menu);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        cctvMainPage = new QWidget();
        cctvMainPage->setObjectName("cctvMainPage");
        openWidgetBtn = new QPushButton(cctvMainPage);
        openWidgetBtn->setObjectName("openWidgetBtn");
        openWidgetBtn->setGeometry(QRect(10, 0, 31, 24));
        closeWidgetBtn = new QPushButton(cctvMainPage);
        closeWidgetBtn->setObjectName("closeWidgetBtn");
        closeWidgetBtn->setGeometry(QRect(50, 0, 31, 24));
        stackedWidget->addWidget(cctvMainPage);
        FtpPage = new QWidget();
        FtpPage->setObjectName("FtpPage");
        groupBoxConnection = new QGroupBox(FtpPage);
        groupBoxConnection->setObjectName("groupBoxConnection");
        groupBoxConnection->setGeometry(QRect(20, 30, 851, 157));
        gridLayoutConnection = new QGridLayout(groupBoxConnection);
        gridLayoutConnection->setObjectName("gridLayoutConnection");
        labelUrl = new QLabel(groupBoxConnection);
        labelUrl->setObjectName("labelUrl");

        gridLayoutConnection->addWidget(labelUrl, 0, 0, 1, 1);

        lineEditUrl = new QLineEdit(groupBoxConnection);
        lineEditUrl->setObjectName("lineEditUrl");

        gridLayoutConnection->addWidget(lineEditUrl, 0, 1, 1, 1);

        labelUsername = new QLabel(groupBoxConnection);
        labelUsername->setObjectName("labelUsername");

        gridLayoutConnection->addWidget(labelUsername, 1, 0, 1, 1);

        lineEditUsername = new QLineEdit(groupBoxConnection);
        lineEditUsername->setObjectName("lineEditUsername");

        gridLayoutConnection->addWidget(lineEditUsername, 1, 1, 1, 1);

        labelPassword = new QLabel(groupBoxConnection);
        labelPassword->setObjectName("labelPassword");

        gridLayoutConnection->addWidget(labelPassword, 2, 0, 1, 1);

        lineEditPassword = new QLineEdit(groupBoxConnection);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayoutConnection->addWidget(lineEditPassword, 2, 1, 1, 1);

        connectBtn = new QPushButton(groupBoxConnection);
        connectBtn->setObjectName("connectBtn");

        gridLayoutConnection->addWidget(connectBtn, 3, 0, 1, 2);

        groupBoxDownload = new QGroupBox(FtpPage);
        groupBoxDownload->setObjectName("groupBoxDownload");
        groupBoxDownload->setGeometry(QRect(20, 240, 851, 127));
        gridLayoutDownload = new QGridLayout(groupBoxDownload);
        gridLayoutDownload->setObjectName("gridLayoutDownload");
        labelRemoteFile = new QLabel(groupBoxDownload);
        labelRemoteFile->setObjectName("labelRemoteFile");

        gridLayoutDownload->addWidget(labelRemoteFile, 0, 0, 1, 1);

        lineEditRemoteFileDownload = new QLineEdit(groupBoxDownload);
        lineEditRemoteFileDownload->setObjectName("lineEditRemoteFileDownload");

        gridLayoutDownload->addWidget(lineEditRemoteFileDownload, 0, 1, 1, 1);

        labelLocalFileDownload = new QLabel(groupBoxDownload);
        labelLocalFileDownload->setObjectName("labelLocalFileDownload");

        gridLayoutDownload->addWidget(labelLocalFileDownload, 1, 0, 1, 1);

        lineEditLocalFileDownload = new QLineEdit(groupBoxDownload);
        lineEditLocalFileDownload->setObjectName("lineEditLocalFileDownload");

        gridLayoutDownload->addWidget(lineEditLocalFileDownload, 1, 1, 1, 1);

        downloadBtn = new QPushButton(groupBoxDownload);
        downloadBtn->setObjectName("downloadBtn");

        gridLayoutDownload->addWidget(downloadBtn, 2, 0, 1, 2);

        stackedWidget->addWidget(FtpPage);
        logPage = new QWidget();
        logPage->setObjectName("logPage");
        logTextEdit = new QTextEdit(logPage);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setGeometry(QRect(10, 10, 1131, 821));
        logTextEdit->setReadOnly(true);
        stackedWidget->addWidget(logPage);
        clientManagePage = new QWidget();
        clientManagePage->setObjectName("clientManagePage");
        registerClientWidget = new QWidget(clientManagePage);
        registerClientWidget->setObjectName("registerClientWidget");
        registerClientWidget->setGeometry(QRect(0, 0, 1121, 791));
        registerClientBtn = new QPushButton(registerClientWidget);
        registerClientBtn->setObjectName("registerClientBtn");
        registerClientBtn->setGeometry(QRect(10, 30, 80, 24));
        deleteClientBtn = new QPushButton(registerClientWidget);
        deleteClientBtn->setObjectName("deleteClientBtn");
        deleteClientBtn->setGeometry(QRect(120, 30, 80, 24));
        clientTable = new QTableWidget(registerClientWidget);
        if (clientTable->columnCount() < 3)
            clientTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        clientTable->setObjectName("clientTable");
        clientTable->setGeometry(QRect(10, 70, 601, 481));
        clientTable->setColumnCount(3);
        clientTable->horizontalHeader()->setDefaultSectionSize(200);
        clientTable->horizontalHeader()->setStretchLastSection(false);
        connectClientBtn = new QPushButton(registerClientWidget);
        connectClientBtn->setObjectName("connectClientBtn");
        connectClientBtn->setGeometry(QRect(230, 30, 80, 24));
        stackedWidget->addWidget(clientManagePage);
        settingsPage = new QWidget();
        settingsPage->setObjectName("settingsPage");
        settingsLayout = new QVBoxLayout(settingsPage);
        settingsLayout->setObjectName("settingsLayout");
        stackedWidget->addWidget(settingsPage);
        recordingsPage = new QWidget();
        recordingsPage->setObjectName("recordingsPage");
        recordingsLayout = new QVBoxLayout(recordingsPage);
        recordingsLayout->setObjectName("recordingsLayout");
        recordingWidget = new QWidget(recordingsPage);
        recordingWidget->setObjectName("recordingWidget");
        cctvVideoPlayer = new QVideoWidget(recordingWidget);
        cctvVideoPlayer->setObjectName("cctvVideoPlayer");
        cctvVideoPlayer->setGeometry(QRect(20, -70, 1091, 741));
        filePath = new QLineEdit(recordingWidget);
        filePath->setObjectName("filePath");
        filePath->setGeometry(QRect(20, 750, 551, 24));
        searchFileBtn = new QPushButton(recordingWidget);
        searchFileBtn->setObjectName("searchFileBtn");
        searchFileBtn->setGeometry(QRect(580, 750, 21, 24));
        horizontalLayoutWidget = new QWidget(recordingWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 690, 201, 42));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        videoSpeedDownBtn = new QPushButton(horizontalLayoutWidget);
        videoSpeedDownBtn->setObjectName("videoSpeedDownBtn");
        videoSpeedDownBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 0, 0, 0.3);\n"
"    color: white;\n"
"    border-radius: 15px;\n"
"    font-size: 18px;\n"
"    width: 40px;\n"
"    height: 40px;\n"
"}QPushButton:hover {\n"
"    background-color: rgba(255, 255, 255, 0.2);\n"
"}"));

        horizontalLayout->addWidget(videoSpeedDownBtn);

        videoPlayBtn = new QPushButton(horizontalLayoutWidget);
        videoPlayBtn->setObjectName("videoPlayBtn");
        videoPlayBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 0, 0, 0.3);\n"
"    color: white;\n"
"    border-radius: 15px;\n"
"    font-size: 18px;\n"
"    width: 40px;\n"
"    height: 40px;\n"
"}QPushButton:hover {\n"
"    background-color: rgba(255, 255, 255, 0.2);\n"
"}"));

        horizontalLayout->addWidget(videoPlayBtn);

        videoSpeedUpBtn = new QPushButton(horizontalLayoutWidget);
        videoSpeedUpBtn->setObjectName("videoSpeedUpBtn");
        videoSpeedUpBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0, 0, 0, 0.3);\n"
"    color: white;\n"
"    border-radius: 15px;\n"
"    font-size: 18px;\n"
"    width: 40px;\n"
"    height: 40px;\n"
"}QPushButton:hover {\n"
"    background-color: rgba(255, 255, 255, 0.2);\n"
"}"));

        horizontalLayout->addWidget(videoSpeedUpBtn);

        verticalLayoutWidget = new QWidget(recordingWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 670, 1091, 21));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        progressBar = new QSlider(verticalLayoutWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"  height: 5px;\n"
"  background: #cccccc;\n"
"  border-radius: 2px;\n"
"}QSlider::handle:horizontal {\n"
"  width: 15px;\n"
"  background: #007BFF;\n"
"  border: 1px solid #0056b3;\n"
"  border-radius: 7px;\n"
"  margin: -5px 0;\n"
"}"));
        progressBar->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout->addWidget(progressBar);

        videoPlayRateLabel = new QLabel(recordingWidget);
        videoPlayRateLabel->setObjectName("videoPlayRateLabel");
        videoPlayRateLabel->setGeometry(QRect(240, 695, 41, 31));
        QFont font1;
        font1.setPointSize(15);
        videoPlayRateLabel->setFont(font1);

        recordingsLayout->addWidget(recordingWidget);

        stackedWidget->addWidget(recordingsPage);

        mainLayout->addWidget(stackedWidget);

        cctvMainWidget = new QWidget(centralwidget);
        cctvMainWidget->setObjectName("cctvMainWidget");

        mainLayout->addWidget(cctvMainWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1440, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CCTV Monitor", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = menu->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Menu", nullptr));

        const bool __sortingEnabled = menu->isSortingEnabled();
        menu->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = menu->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "CCTV", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("MainWindow", "- CCTV", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("MainWindow", "- \354\266\224\352\260\200", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = menu->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("MainWindow", "\352\270\260\353\212\245 \354\204\244\354\240\225", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = menu->topLevelItem(2);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("MainWindow", "\353\241\234\352\267\270", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = menu->topLevelItem(3);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("MainWindow", "\353\205\271\355\231\224 \354\230\201\354\203\201 \355\231\225\354\235\270", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = menu->topLevelItem(4);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("MainWindow", "FTP", nullptr));
        menu->setSortingEnabled(__sortingEnabled);

        openWidgetBtn->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        closeWidgetBtn->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        groupBoxConnection->setTitle(QCoreApplication::translate("MainWindow", "FTP Connection", nullptr));
        labelUrl->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        labelUsername->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        labelPassword->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        connectBtn->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        groupBoxDownload->setTitle(QCoreApplication::translate("MainWindow", "Download File", nullptr));
        labelRemoteFile->setText(QCoreApplication::translate("MainWindow", "Remote File Path:", nullptr));
        labelLocalFileDownload->setText(QCoreApplication::translate("MainWindow", "Local Save Path:", nullptr));
        downloadBtn->setText(QCoreApplication::translate("MainWindow", "Download", nullptr));
        registerClientBtn->setText(QCoreApplication::translate("MainWindow", "\354\266\224\352\260\200", nullptr));
        deleteClientBtn->setText(QCoreApplication::translate("MainWindow", "\354\202\255\354\240\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        connectClientBtn->setText(QCoreApplication::translate("MainWindow", "\354\227\260\352\262\260", nullptr));
        searchFileBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\223\201", nullptr));
        videoSpeedDownBtn->setText(QCoreApplication::translate("MainWindow", "\342\217\252", nullptr));
        videoPlayBtn->setText(QCoreApplication::translate("MainWindow", "\342\217\270", nullptr));
        videoSpeedUpBtn->setText(QCoreApplication::translate("MainWindow", "\342\217\251", nullptr));
        videoPlayRateLabel->setText(QCoreApplication::translate("MainWindow", "1.0x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
