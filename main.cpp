#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    a.setStyleSheet(R"(
    /* Global */
    QWidget {
        background-color: white;
        color: #1f2937;
        font-size: 12px;
        font-family: "Segoe UI";
    }

    QMainWindow {
        background-color: #FAFAFB;
    }
)");

    MainWindow w;
    w.show();
    return QApplication::exec();
}
