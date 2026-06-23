#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

private:
    void refreshPort();
    void log(const QString &text);
    void connectSerial();
    void disConnectSerial();
    void baudRateClicked(QString baud);
    void comClicked(QString com);
    void dataBitsClicked(QString data);
    void parityClicked(QString prt);
    void clearLogs();
private:
    QComboBox *portCom = nullptr;
    QTextEdit *logBox = nullptr;
    QPushButton *actionConn = nullptr;
    QPushButton *actionDisconn = nullptr;
    QComboBox *baudRate = nullptr;
    QLabel *comSelected = nullptr;
    QComboBox *dataBits = nullptr;
    QComboBox *parity = nullptr;
    QPushButton *clearLine = nullptr;

};
#endif // MAINWINDOW_H
