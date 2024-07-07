#include <QApplication>

#include "assembler_window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    AssemblerWindow s;
    s.show();

    return a.exec();
}
