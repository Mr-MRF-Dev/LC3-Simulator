#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QLabel* lab = new QLabel(this);
    lab->setText("Hello World!");
}

MainWindow::~MainWindow() {}
