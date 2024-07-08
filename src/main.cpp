#include <QApplication>

#include "assembler_window.h"
#include "simulator_window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // AssemblerWindow s;
    // s.show();

    SimulatorWindow sim;
    sim.show();

    return a.exec();
}
