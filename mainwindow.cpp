#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>

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

        QLabel *portCom = new QLabel("COM 4");
        portCom->setObjectName("portCom");
        portCom->setStyleSheet(R"(
            #portCom {
                color: #6A6F78;
            }
        )");

        QLabel *portRefresh = new QLabel("Refresh Ports");
        portRefresh->setObjectName("portRefresh");
        portRefresh->setStyleSheet(R"(
            #portRefresh {
                color: #6A6F78;
            }
        )");
        portSecBox->addWidget(portSel);
        portSecBox->addWidget(portCom);
        portSecBox->addWidget(portRefresh);

    QLabel *action = new QLabel("ACTIONS");
    action->setObjectName("action");
    action->setStyleSheet(R"(
        #action {
            color: black;
        }
    )");

    QLabel *about = new QLabel("ABOUT");
    about->setObjectName("about");
    about->setStyleSheet(R"(
        #about {
            color: black;
        }
    )");

    connBoxLayout->addWidget(connectionSection, 0, 0);
    connBoxLayout->addWidget(portSection, 1, 0);
    connBoxLayout->addWidget(action, 2, 0);
    connBoxLayout->addWidget(about, 3, 0);
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

    QLabel *command = new QLabel("Command");
    command->setObjectName("comm");
    command->setStyleSheet(R"(
        #comm {
            color: black;
        }
    )");commBoxLayout->addWidget(command);



    topLayout->addWidget(connBox, 0, 0);
    topLayout->setSpacing(40);
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

    QLabel *readyConn = new QLabel("Ready Connection");
    readyConn->setObjectName("readyConn");
    readyConn->setStyleSheet(R"(
        #readyConn {
            color: black;
        }
    )");

    bottomLayout->addWidget(readyConn);
    // ----------------------------------------------------------------------

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(bottomBox);

}

MainWindow::~MainWindow()
{
    delete ui;
}