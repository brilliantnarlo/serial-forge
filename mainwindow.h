#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QLabel;
class QTextEdit;
class QPushButton;
class QComboBox;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void refreshPort();
    void connectSerial();
    void disConnectSerial();
    void sendSerial(QString packet);
    void readSerialData();

    void comClicked(QString com);
    void baudRateClicked(QString baud);
    void dataBitsClicked(QString data);
    void parityClicked(QString prt);

    void log(const QString &text);
    void clearLogs();
    QString bytesToHex(const QByteArray &data) const;

private:
    Ui::MainWindow *ui = nullptr;

    QSerialPort *serial = nullptr;

    QComboBox *portCom = nullptr;
    QComboBox *baudRate = nullptr;
    QComboBox *dataBits = nullptr;
    QComboBox *parity = nullptr;
    QComboBox *stopBits = nullptr;

    QLabel *comSelected = nullptr;
    QLabel *connectionStatus = nullptr;
    QLabel *activeConn = nullptr;

    QTextEdit *logBox = nullptr;
    QLineEdit *chat = nullptr;

    QPushButton *actionConn = nullptr;
    QPushButton *actionDisconn = nullptr;
    QPushButton *clearLine = nullptr;
};

#endif // MAINWINDOW_H