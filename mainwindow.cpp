#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Serial Forge");

    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainWidget->setObjectName("mainWidget");
    mainWidget->setStyleSheet(R"(
        #mainWidget {
            background-color: #FAFAFB;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    QGridLayout *topLayout = new QGridLayout;

    // CONNECTION -----------------------------------------------------------
    QWidget *connBox = new QWidget;
    connBox->setObjectName("connBox");
    connBox->setStyleSheet(R"(
        #connBox {
            border-radius: 5px;
            border: .5px solid #E9E9EB;
            background-color: #FFFFFF;
        }
    )");

    QGridLayout *connBoxLayout = new QGridLayout(connBox);
    connBoxLayout->setAlignment(Qt::AlignTop);

    QWidget *connectionSection = new QWidget;
    connectionSection->setObjectName("connSection");
    connectionSection->setStyleSheet(R"(
        #connSection{
            border-bottom: .5px solid #E9E9EB;
        }
    )");
    connectionSection->setContentsMargins(0, 0, 20, 20);
    QGridLayout *connectionSecBox = new QGridLayout(connectionSection);
        QLabel *connection = new QLabel("CONNECTION");
        connection->setObjectName("conn");
        connection->setStyleSheet(R"(
            #conn {
                color: #6A6F78;
            }
        )");

        QLabel *icon = new QLabel("Icon");
        icon->setObjectName("conn");
        icon->setStyleSheet(R"(
            #conn {
                color: #6A6F78;
            }
        )");

        QLabel *disconnect = new QLabel("Disconnected");
        disconnect->setObjectName("conn");
        disconnect->setStyleSheet(R"(
            #conn {
                color: #202733;
            }
        )");

    connectionSecBox->addWidget(connection, 0, 0);
    connectionSecBox->addWidget(icon, 1, 0);
    connectionSecBox->addWidget(disconnect, 1, 1);



    QWidget *portSection = new QWidget;
    portSection->setObjectName("portSection");
    portSection->setStyleSheet(R"(
        #portSection{
            border-bottom: .5px solid #E9E9EB;
        }
    )");
    portSection->setContentsMargins(0, 0, 20, 20);

    QGridLayout *portSecBox = new QGridLayout(portSection);

        QLabel *portSel = new QLabel("PORT SELECTION");
        portSel->setObjectName("portSel");
        portSel->setStyleSheet(R"(
            #portSel {
                color: #6A6F78;
            }
        )");

        QComboBox *portCom = new QComboBox(this);
        portCom->addItem("COM 4");
        portCom->addItem("COM 8");
        portCom->setObjectName("portCom");
        portCom->setStyleSheet(R"(
            #portCom {
                color: #6A6F78;
            }
        )");

        QPushButton *portRefresh = new QPushButton("Refresh Ports");
        portRefresh->setObjectName("portRefresh");
        portRefresh->setStyleSheet(R"(
            #portRefresh {
                color: #027D85;
                border: .5px solid #D5D7DA;
                border-radius: 5px;
                padding-top: 6px;
                padding-bottom: 6px;
            }
            #portRefresh:hover {
                background-color: #FAFAFB;
                color: #027D85;
            }
        )");
    portSecBox->addWidget(portSel);
    portSecBox->addWidget(portCom);
    portSecBox->addWidget(portRefresh);


    QWidget *actionSection = new QWidget;
    actionSection->setObjectName("actionSection");
    actionSection->setStyleSheet(R"(
        #actionSection{
            border-bottom: .5px solid #E9E9EB;
        }
    )");
    actionSection->setContentsMargins(0, 0, 20, 20);

        QGridLayout *actionSecBox = new QGridLayout(actionSection);

        QLabel *action = new QLabel("ACTIONS");
        action->setObjectName("action");
        action->setStyleSheet(R"(
            #action {
                color: #6A6F78;
            }
        )");

        QPushButton *actionConn = new QPushButton("Connect");
        actionConn->setObjectName("actionConn");
        actionConn->setStyleSheet(R"(
            #actionConn {
                color: white;
                border: .5px solid #D5D7DA;
                border-radius: 5px;
                padding-top: 6px;
                padding-bottom: 6px;
                background-color: #038189;
            }
            #actionConn:hover {
                background-color: #038189;
                color: white;
            }
        )");

        QPushButton *actionDiconn = new QPushButton("Disconnect");
        actionDiconn->setObjectName("actionDiconn");
        actionDiconn->setStyleSheet(R"(
            #actionDiconn {
                color: black;
                border: .5px solid #D5D7DA;
                border-radius: 5px;
                padding-top: 6px;
                padding-bottom: 6px;
            }
            #actionDiconn:hover {
                background-color: #FAFAFB;
                color: black;
            }
        )");

    actionSecBox->addWidget(action);
    actionSecBox->addWidget(actionConn);
    actionSecBox->addWidget(actionDiconn);


    QWidget *aboutSection = new QWidget;
    aboutSection->setContentsMargins(0, 0, 20, 20);

    QGridLayout *aboutSecBox = new QGridLayout(aboutSection);

    QLabel *about = new QLabel("ABOUT");
    about->setObjectName("about");
    about->setStyleSheet(R"(
        #about {
            color: #6A6F78;
        }
    )");

    aboutSecBox->addWidget(about);

    connBoxLayout->addWidget(connectionSection, 0, 0);
    connBoxLayout->addWidget(portSection, 1, 0);
    connBoxLayout->addWidget(actionSection, 2, 0);
    connBoxLayout->addWidget(aboutSection, 3, 0);
    // ----------------------------------------------------------------------

    QWidget *commBox = new QWidget;
    commBox->setObjectName("commBox");
    commBox->setStyleSheet(R"(
        #commBox {
            border-radius: 5px;
            border: .5px solid #E9E9EB;
            background-color: #FFFFFF;
        }
    )");

    QVBoxLayout *commBoxLayout = new QVBoxLayout(commBox);

    QWidget *commandSection = new QWidget;
    QGridLayout *commandSectionBox = new QGridLayout(commandSection);
    commandSection->setObjectName("commandSection");
    commandSection->setStyleSheet(R"(
        #commandSection {
            border-bottom: .5px solid #E9E9EB;
            background-color: #FFFFFF;
        }
    )");

    QLabel *command = new QLabel("COMMAND");
    command->setObjectName("comm");
    command->setStyleSheet(R"(
        #comm {
            color: #7A56ED;
        }
    )");

    QLineEdit *chat = new QLineEdit();
    chat->setObjectName("chat");
    chat->setPlaceholderText("Type text to send...");
    chat->setStyleSheet(R"(
        #chat {
            padding: 5px;
            border-radius: 5px;
            border: .5px solid #E9E9EB;
        }
    )");

    QWidget *sendLineWidget = new QWidget;
    QHBoxLayout *sendLineBox = new QHBoxLayout(sendLineWidget);
    sendLineBox->setContentsMargins(0, 0, 0, 0);

    QPushButton *sendLine = new QPushButton("Send Line");
    sendLine->setObjectName("sendLine");
    sendLine->setStyleSheet(R"(
        #sendLine {
            color: white;
            background-color: #7A56ED;
            border-radius: 5px;
            padding: 8px 20px;
        }
    )");

    QPushButton *clearLine = new QPushButton("Clear");
    clearLine->setObjectName("clearLine");
    clearLine->setStyleSheet(R"(
        #clearLine {
            color: white;
            background-color: #7A56ED;
            border-radius: 5px;
            padding: 8px 20px;
        }
    )");
    sendLineBox->setAlignment(Qt::AlignRight);
    sendLineBox->addWidget(sendLine);
    sendLineBox->addWidget(clearLine);

    commandSectionBox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    commandSectionBox->addWidget(command, 0, 0);
    commandSectionBox->addWidget(chat, 1, 0);
    commandSectionBox->addWidget(sendLineWidget, 2, 0);


    QWidget *serialSection = new QWidget;
    QGridLayout *serialSectionBox = new QGridLayout(serialSection);
    serialSection->setObjectName("serialSection");
    serialSection->setStyleSheet(R"(
        #serialSection {
            border-top: .5px solid #E9E9EB;
            background-color: #FFFFFF;
        }
    )");

    QLabel *serialLog = new QLabel("SERIAL LOG");
    serialLog->setObjectName("serialLog");
    serialLog->setStyleSheet(R"(
        #serialLog {
            color: #027D85;
        }
    )");

    serialSectionBox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    serialSectionBox->addWidget(serialLog);

    commBoxLayout->addWidget(commandSection);
    commBoxLayout->addWidget(serialSection);



    topLayout->addWidget(connBox, 0, 0);
    topLayout->setSpacing(20);
    topLayout->addWidget(commBox, 0, 1);
    topLayout->setColumnStretch(0, 1);
    topLayout->setColumnStretch(1, 4);


    // READY CONN ------------------------------------------------------------
    QWidget *bottomBox = new QWidget;
    bottomBox->setObjectName("bottomBox");
    bottomBox->setFixedHeight(50);
    bottomBox->setStyleSheet(R"(
        #bottomBox {
            border-radius: 5px;
            border: .5px solid #E9E9EB;
            background-color: #FFFFFF;
        }
    )");

    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomBox);

    QLabel *readyConn = new QLabel("Ready");
    readyConn->setObjectName("readyConn");
    readyConn->setStyleSheet(R"(
        #readyConn {
            color: black;

        }
    )");

    QLabel *activeConn = new QLabel("No active connection");
    activeConn->setObjectName("activeConn");
    activeConn->setStyleSheet(R"(
        #activeConn {
            color: #6A6F78;
        }
    )");

    bottomLayout->addWidget(readyConn);
    bottomLayout->addWidget(activeConn);
    // ----------------------------------------------------------------------

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(bottomBox);

}

MainWindow::~MainWindow()
{
    delete ui;
}