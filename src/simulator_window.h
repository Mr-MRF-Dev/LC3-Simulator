#ifndef SIMULATOR_WINDOW_H
#define SIMULATOR_WINDOW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

#include "simulator.h"

class SimulatorWindow : public QWidget {
    Q_OBJECT

private:
    Simulator* Sim;
    QTableWidget* ram;
    QLabel* console;
    QPushButton* step;

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

    void init();
    void clear();

public:
    SimulatorWindow(QWidget *parent = nullptr);

public slots:
    void openFile();
    void stepFunc();

};

#endif // SIMULATOR_WINDOW_H
