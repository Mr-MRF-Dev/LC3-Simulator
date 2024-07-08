#include "simulator_window.h"

SimulatorWindow::SimulatorWindow(QWidget *parent):QWidget(parent) {

    string file_name = "MEMMORY";
    Sim = new Simulator(file_name);

    QLabel* file_name_label = new QLabel(this);
    file_name_label->setText("File Name:");

    QLabel* file_format_label = new QLabel(this);
    file_format_label->setText(".bin");

    file_name_lineE = new QLineEdit(this);
    file_name_lineE->setText(QString::fromStdString(file_name));

    QPushButton* fn_save_button = new QPushButton(this);
    fn_save_button->setText("Open");

    connect(fn_save_button, &QPushButton::clicked, this, &SimulatorWindow::openFile);

    QHBoxLayout* fn_layout = new QHBoxLayout;
    fn_layout->addWidget(file_name_label);
    fn_layout->addWidget(file_name_lineE);
    fn_layout->addWidget(file_format_label);
    fn_layout->addWidget(fn_save_button);

    QLabel* line1_label = new QLabel(this);
    line1_label->setText(">>");

    QVBoxLayout* line1 = new QVBoxLayout;
    line1->addWidget(line1_label);

    QLabel* line2_label = new QLabel(this);
    line2_label->setText(">>");

    QVBoxLayout* line2 = new QVBoxLayout;
    line2->addWidget(line2_label);


    QLabel* con = new QLabel(this);
    con->setText("MMD\n");

    QVBoxLayout* l_con = new QVBoxLayout;
    l_con->addLayout(fn_layout);
    l_con->addWidget(con);

    ///////////////// PC
    QLabel* lab_pc = new QLabel;
    lab_pc->setText("PC:");

    pc = new QLineEdit(this);
    pc->setText(QString("-"));
    pc->setEnabled(false);

    QHBoxLayout* l_pc = new QHBoxLayout;
    l_pc->addWidget(lab_pc);
    l_pc->addWidget(pc);
    ///////////////// PC
    ///
    ///////////////// IR
    QLabel* lab_ir = new QLabel;
    lab_ir->setText("IR:");

    ir = new QLineEdit(this);
    ir->setText(QString("-"));
    ir->setEnabled(false);

    QHBoxLayout* l_ir = new QHBoxLayout;
    l_ir->addWidget(lab_ir);
    l_ir->addWidget(ir);
    ///////////////// IR
    ///
    ///////////////// mdr
    QLabel* lab_mdr = new QLabel;
    lab_mdr->setText("MDR:");

    mdr = new QLineEdit(this);
    mdr->setText(QString("-"));
    mdr->setEnabled(false);

    QHBoxLayout* l_mdr = new QHBoxLayout;
    l_mdr->addWidget(lab_mdr);
    l_mdr->addWidget(mdr);
    ///////////////// mdr
    ///
    ///////////////// mar
    QLabel* lab_mar = new QLabel;
    lab_mar->setText("MAR:");

    mar = new QLineEdit(this);
    mar->setText(QString("-"));
    mar->setEnabled(false);

    QHBoxLayout* l_mar = new QHBoxLayout;
    l_mar->addWidget(lab_mar);
    l_mar->addWidget(mar);
    ///////////////// mar

    ///////////////// n z p
    QHBoxLayout* l_nzp = new QHBoxLayout;

    QLabel* lab_n = new QLabel;
    lab_n->setText("N:");

    n = new QLineEdit(this);
    n->setText(QString("-"));
    n->setEnabled(false);

    QHBoxLayout* l_n = new QHBoxLayout;
    l_n->addWidget(lab_n);
    l_n->addWidget(n);

    /// z
    QLabel* lab_z = new QLabel;
    lab_z->setText("Z:");

    z = new QLineEdit(this);
    z->setText(QString("-"));
    z->setEnabled(false);

    QHBoxLayout* l_z = new QHBoxLayout;
    l_z->addWidget(lab_z);
    l_z->addWidget(z);

    /// z
    QLabel* lab_p = new QLabel;
    lab_p->setText("P:");

    p = new QLineEdit(this);
    p->setText(QString("-"));
    p->setEnabled(false);

    QHBoxLayout* l_p = new QHBoxLayout;
    l_p->addWidget(lab_p);
    l_p->addWidget(p);

    n->setMaximumWidth(40);
    z->setMaximumWidth(40);
    p->setMaximumWidth(40);
    /// add to layout
    l_nzp->addLayout(l_n);
    l_nzp->addLayout(l_z);
    l_nzp->addLayout(l_p);
    ///////////////// n z p

    QVBoxLayout* l_side = new QVBoxLayout;
    l_side->addLayout(l_pc);
    l_side->addLayout(l_ir);
    l_side->addLayout(l_mdr);
    l_side->addLayout(l_mar);
    l_side->addLayout(l_nzp);

    QHBoxLayout* l_header = new QHBoxLayout;
    l_header->addLayout(l_con);
    l_header->addLayout(l_side);

    QVBoxLayout* l_body = new QVBoxLayout;
    l_body->addLayout(l_header);

    QHBoxLayout* l_main = new QHBoxLayout(this);
    l_main->addLayout(line1);
    // add table
    l_main->addLayout(line2);
    l_main->addLayout(l_body);

}

void SimulatorWindow::openFile() {
    // load file path
    Sim->setFilePath(file_name_lineE->text().toStdString());
}


