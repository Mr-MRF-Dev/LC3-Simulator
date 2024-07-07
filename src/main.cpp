#include <QApplication>

#include "assembler.h"
#include "codeeditor.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CodeEditor s;
    s.show();

    Assembler A;
    s.setWindowTitle(QString::fromStdString(A.getMsg()));

    return a.exec();
}
