#include "mainwindow.h"

#include <QApplication>
#include "assembler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Assembler A;
    w.setWindowTitle(QString::fromStdString(A.getMsg()));

    return a.exec();
}
