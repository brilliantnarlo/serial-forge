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
#include <QTextEdit>
#include <QSerialPortInfo>
#include <QList>
#include <QDateTime>
#include <QByteArray>
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    serial(new QSerialPort(this))
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
        #connSection {
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
    icon->setObjectName("connIcon");
    icon->setStyleSheet(R"(
        #connIcon {
            color: #6A6F78;
        }
    )");

    connectionStatus = new QLabel("Disconnected");
    connectionStatus->setObjectName("connectionStatus");
    connectionStatus->setStyleSheet(R"(
        #connectionStatus {
            color: #202733;
        }
    )");

    connectionSecBox->addWidget(connection, 0, 0);
    connectionSecBox->addWidget(icon, 1, 0);
    connectionSecBox->addWidget(connectionStatus, 1, 1);

    // PORT SECTION ---------------------------------------------------------
    QWidget *portSection = new QWidget;
    portSection->setObjectName("portSection");
    portSection->setStyleSheet(R"(
        #portSection {
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

    portCom = new QComboBox(this);
    portCom->setObjectName("portCom");
    portCom->setStyleSheet(R"(
        #portCom {
            color: #6A6F78;
        }
    )");

    connect(portCom, &QComboBox::textActivated, this, &MainWindow::comClicked);

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

    connect(portRefresh, &QPushButton::clicked, this, [this]() {
        refreshPort();
    });

    portSecBox->addWidget(portSel);
    portSecBox->addWidget(portCom);
    portSecBox->addWidget(portRefresh);

    // ACTION SECTION -------------------------------------------------------
    QWidget *actionSection = new QWidget;
    actionSection->setObjectName("actionSection");
    actionSection->setStyleSheet(R"(
        #actionSection {
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

    QLabel *baudRateLabel = new QLabel("Baud Rate");
    baudRateLabel->setObjectName("baudRateLabel");
    baudRateLabel->setStyleSheet(R"(
        #baudRateLabel {
            color: black;
        }
    )");

    baudRate = new QComboBox;
    baudRate->setObjectName("baudRate");
    baudRate->setStyleSheet(R"(
        #baudRate {
            color: black;
        }
    )");

    connect(baudRate, &QComboBox::textActivated, this, &MainWindow::baudRateClicked);

    QLabel *dataBitsLabel = new QLabel("Data Bits");
    dataBitsLabel->setObjectName("dataBitsLabel");
    dataBitsLabel->setStyleSheet(R"(
        #dataBitsLabel {
            color: black;
        }
    )");

    dataBits = new QComboBox;
    dataBits->setObjectName("dataBits");
    dataBits->setStyleSheet(R"(
        #dataBits {
            color: black;
        }
    )");

    dataBits->addItem("8", QSerialPort::Data8);
    dataBits->addItem("7", QSerialPort::Data7);
    dataBits->addItem("6", QSerialPort::Data6);
    dataBits->addItem("5", QSerialPort::Data5);

    connect(dataBits, &QComboBox::textActivated, this, &MainWindow::dataBitsClicked);

    QLabel *parityLabel = new QLabel("Parity");
    parityLabel->setObjectName("parityLabel");
    parityLabel->setStyleSheet(R"(
        #parityLabel {
            color: black;
        }
    )");

    parity = new QComboBox;
    parity->setObjectName("parity");
    parity->setStyleSheet(R"(
        #parity {
            color: black;
        }
    )");

    parity->addItem("None", QSerialPort::NoParity);
    parity->addItem("Even", QSerialPort::EvenParity);
    parity->addItem("Odd", QSerialPort::OddParity);
    parity->addItem("Mark", QSerialPort::MarkParity);
    parity->addItem("Space", QSerialPort::SpaceParity);

    connect(parity, &QComboBox::textActivated, this, &MainWindow::parityClicked);

    QLabel *stopBitsLabel = new QLabel("Stop Bits");
    stopBitsLabel->setObjectName("stopBitsLabel");
    stopBitsLabel->setStyleSheet(R"(
        #stopBitsLabel {
            color: black;
        }
    )");

    stopBits = new QComboBox;
    stopBits->setObjectName("stopBits");
    stopBits->setStyleSheet(R"(
        #stopBits {
            color: black;
        }
    )");

    stopBits->addItem("1", QSerialPort::OneStop);
    stopBits->addItem("1.5", QSerialPort::OneAndHalfStop);
    stopBits->addItem("2", QSerialPort::TwoStop);

    actionConn = new QPushButton("Connect");
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

    connect(actionConn, &QPushButton::clicked, this, [this]() {
        connectSerial();
    });

    actionDisconn = new QPushButton("Disconnect");
    actionDisconn->setObjectName("actionDisconn");
    actionDisconn->setStyleSheet(R"(
        #actionDisconn {
            color: black;
            border: .5px solid #D5D7DA;
            border-radius: 5px;
            padding-top: 6px;
            padding-bottom: 6px;
        }

        #actionDisconn:hover {
            background-color: #FAFAFB;
            color: black;
        }
    )");

    connect(actionDisconn, &QPushButton::clicked, this, [this]() {
        disConnectSerial();
    });

    actionSecBox->addWidget(action);
    actionSecBox->addWidget(baudRateLabel);
    actionSecBox->addWidget(baudRate);
    actionSecBox->addWidget(dataBitsLabel);
    actionSecBox->addWidget(dataBits);
    actionSecBox->addWidget(parityLabel);
    actionSecBox->addWidget(parity);
    actionSecBox->addWidget(stopBitsLabel);
    actionSecBox->addWidget(stopBits);
    actionSecBox->addWidget(actionConn);
    actionSecBox->addWidget(actionDisconn);

    // ABOUT SECTION --------------------------------------------------------
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

    // COMMUNICATION BOX ----------------------------------------------------
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

    chat = new QLineEdit();
    chat->setObjectName("chat");
    chat->setPlaceholderText("Type text to send...");
    chat->setStyleSheet(R"(
        #chat {
            color: black;
            padding: 5px;
            border-radius: 5px;
            border: .5px solid #E9E9EB;
            background-color: #FAFAFB;
        }
    )");

    connect(chat, &QLineEdit::returnPressed, this, [this]() {
        sendSerial(chat->text());
    });

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

    connect(sendLine, &QPushButton::clicked, this, [this]() {
        sendSerial(chat->text());
    });

    clearLine = new QPushButton("Clear");
    clearLine->setObjectName("clearLine");
    clearLine->setStyleSheet(R"(
        #clearLine {
            color: black;
            border: .5px solid #E9E9EB;
            border-radius: 5px;
            padding: 8px 20px;
        }

        #clearLine:hover {
            background-color: #FAFAFB;
        }
    )");

    connect(clearLine, &QPushButton::clicked, this, [this]() {
        clearLogs();
    });

    sendLineBox->setAlignment(Qt::AlignRight);
    sendLineBox->addWidget(sendLine);
    sendLineBox->addWidget(clearLine);

    commandSectionBox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    commandSectionBox->addWidget(command, 0, 0);
    commandSectionBox->addWidget(chat, 1, 0);
    commandSectionBox->addWidget(sendLineWidget, 2, 0);

    // SERIAL LOG SECTION ---------------------------------------------------
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

    logBox = new QTextEdit();
    logBox->setReadOnly(true);
    logBox->setObjectName("logBox");
    logBox->setStyleSheet(R"(
        #logBox {
            background-color: #FAFAFB;
            border: .5px solid #E9E9EB;
            border-radius: 5px;
            color: #027D85;
        }
    )");

    serialSectionBox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    serialSectionBox->addWidget(serialLog);
    serialSectionBox->addWidget(logBox);

    commBoxLayout->addWidget(commandSection);
    commBoxLayout->addWidget(serialSection);

    topLayout->addWidget(connBox, 0, 0);
    topLayout->setSpacing(20);
    topLayout->addWidget(commBox, 0, 1);
    topLayout->setColumnStretch(0, 1);
    topLayout->setColumnStretch(1, 4);

    // BOTTOM STATUS --------------------------------------------------------
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

    comSelected = new QLabel();
    comSelected->setObjectName("comSelected");
    comSelected->setStyleSheet(R"(
        #comSelected {
            color: #7A56ED;
        }
    )");

    activeConn = new QLabel("No active connection");
    activeConn->setObjectName("activeConn");
    activeConn->setStyleSheet(R"(
        #activeConn {
            color: #6A6F78;
        }
    )");

    bottomLayout->addWidget(readyConn);
    bottomLayout->addWidget(comSelected);
    bottomLayout->addStretch();
    bottomLayout->addWidget(activeConn);

    // SERIAL SIGNALS -------------------------------------------------------
    connect(serial, &QSerialPort::readyRead, this, [this]() {
        readSerialData();
    });

    connect(serial, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error) {
        if (error == QSerialPort::NoError) {
            return;
        }

        log("SERIAL ERROR: " + serial->errorString());

        if (connectionStatus) {
            connectionStatus->setText("Error");
        }

        if (activeConn) {
            activeConn->setText("Error: " + serial->errorString());
        }
    });

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(bottomBox);

    refreshPort();
}

void MainWindow::refreshPort()
{
    portCom->clear();
    baudRate->clear();

    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &port : ports) {
        QString label = QString("%1 | %2 | %3")
        .arg(port.portName())
            .arg(port.description())
            .arg(port.manufacturer());

        portCom->addItem(label, port.portName());
    }

    const QList<qint32> bauds = QSerialPortInfo::standardBaudRates();

    for (qint32 baud : bauds) {
        baudRate->addItem(QString::number(baud), baud);
    }

    int index = baudRate->findData(115200);

    if (index != -1) {
        baudRate->setCurrentIndex(index);
    }

    if (ports.isEmpty()) {
        log("No serial ports found.");

        if (comSelected) {
            comSelected->setText("");
        }
    } else {
        log(QString("Found %1 serial port(s).").arg(ports.size()));
        comSelected->setText(portCom->currentData().toString());
    }
}

void MainWindow::comClicked(QString com)
{
    Q_UNUSED(com);

    const QString portName = portCom->currentData().toString();
    comSelected->setText(portName);
}

void MainWindow::baudRateClicked(QString baud)
{
    log(QString("Baud Rate: [%1]").arg(baud));
}

void MainWindow::dataBitsClicked(QString data)
{
    log(QString("Data Bits: [%1]").arg(data));
}

void MainWindow::parityClicked(QString prt)
{
    log(QString("Parity: [%1]").arg(prt));
}

void MainWindow::connectSerial()
{
    if (serial->isOpen()) {
        serial->close();
    }

    if (portCom->currentIndex() < 0) {
        log("No port selected.");
        return;
    }

    const QString selectedPort = portCom->currentData().toString();

    if (selectedPort.isEmpty()) {
        log("No serial port selected.");
        return;
    }

    const qint32 selectedBaudRate = baudRate->currentData().toInt();

    const QSerialPort::DataBits selectedDataBits =
        static_cast<QSerialPort::DataBits>(dataBits->currentData().toInt());

    const QSerialPort::Parity selectedParity =
        static_cast<QSerialPort::Parity>(parity->currentData().toInt());

    const QSerialPort::StopBits selectedStopBits =
        static_cast<QSerialPort::StopBits>(stopBits->currentData().toInt());

    serial->setPortName(selectedPort);
    serial->setBaudRate(selectedBaudRate);
    serial->setDataBits(selectedDataBits);
    serial->setParity(selectedParity);
    serial->setStopBits(selectedStopBits);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    log(QString("Opening %1...").arg(selectedPort));

    if (!serial->open(QIODevice::ReadWrite)) {
        log("OPEN FAILED: " + serial->errorString());

        if (connectionStatus) {
            connectionStatus->setText("Disconnected");
        }

        if (activeConn) {
            activeConn->setText("Failed to open " + selectedPort);
        }

        return;
    }

    const QString modeText = QString("%1 %2%3%4")
                                 .arg(selectedBaudRate)
                                 .arg(dataBits->currentText())
                                 .arg(parity->currentText() == "None" ? "N" : parity->currentText().left(1))
                                 .arg(stopBits->currentText());

    log("CONNECTED: " + selectedPort);
    log("MODE: " + modeText);

    if (connectionStatus) {
        connectionStatus->setText("Connected");
    }

    if (activeConn) {
        activeConn->setText("Connected to " + selectedPort + " at " + modeText);
    }

    if (comSelected) {
        comSelected->setText(selectedPort);
    }
}

void MainWindow::disConnectSerial()
{
    if (serial && serial->isOpen()) {
        const QString portName = serial->portName();
        serial->close();

        log("DISCONNECTED: " + portName);

        if (connectionStatus) {
            connectionStatus->setText("Disconnected");
        }

        if (activeConn) {
            activeConn->setText("No active connection");
        }

        return;
    }

    log("Serial port is not open.");

    if (connectionStatus) {
        connectionStatus->setText("Disconnected");
    }

    if (activeConn) {
        activeConn->setText("No active connection");
    }
}

void MainWindow::sendSerial(QString packet)
{
    if (packet.isEmpty()) {
        log("No command sent.");
        return;
    }

    if (!serial || !serial->isOpen()) {
        log("Cannot send. Serial port is not open.");
        return;
    }

    QByteArray data = packet.toLatin1();
    data.append("\r\n");

    const qint64 written = serial->write(data);

    if (written < 0) {
        log("SEND FAILED: " + serial->errorString());
        return;
    }

    log("TX ASCII: " + QString::fromLatin1(data).trimmed());
    log("TX HEX:   " + bytesToHex(data));
}

void MainWindow::readSerialData()
{
    if (!serial) {
        return;
    }

    const QByteArray data = serial->readAll();

    if (data.isEmpty()) {
        return;
    }

    log("RX ASCII: " + QString::fromLatin1(data).trimmed());
    log("RX HEX:   " + bytesToHex(data));
}

void MainWindow::log(const QString &text)
{
    if (!logBox) {
        return;
    }

    const QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    logBox->append(QString("[%1] %2").arg(time, text));
}

void MainWindow::clearLogs()
{
    if (!logBox) {
        return;
    }

    logBox->clear();

    const QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    logBox->append(QString("[%1] %2").arg(time, "Log Cleared!"));
}

QString MainWindow::bytesToHex(const QByteArray &data) const
{
    QString out;

    for (unsigned char byte : data) {
        out += QString("%1 ").arg(byte, 2, 16, QChar('0')).toUpper();
    }

    return out.trimmed();
}

MainWindow::~MainWindow()
{
    if (serial && serial->isOpen()) {
        serial->close();
    }

    delete ui;
}