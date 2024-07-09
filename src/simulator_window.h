#ifndef SIMULATOR_WINDOW_H
#define SIMULATOR_WINDOW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "simulator.h"

class SimulatorWindow : public QWidget {
    Q_OBJECT

private:
    Simulator* Sim;

    QLineEdit* file_name_lineE;
    QLineEdit* pc;
    QLineEdit* ir;
    QLineEdit* mdr;
    QLineEdit* mar;
    QLineEdit* n;
    QLineEdit* p;
    QLineEdit* z;

    QLineEdit* r0;
    QLineEdit* r1;
    QLineEdit* r2;
    QLineEdit* r3;
    QLineEdit* r4;
    QLineEdit* r5;
    QLineEdit* r6;
    QLineEdit* r7;

public:
    SimulatorWindow(QWidget *parent = nullptr);

public slots:
    void openFile();
};

#endif // SIMULATOR_WINDOW_H
