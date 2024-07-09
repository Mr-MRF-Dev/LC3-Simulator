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

    n->setAlignment(Qt::AlignCenter);
    z->setAlignment(Qt::AlignCenter);
    p->setAlignment(Qt::AlignCenter);
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

    ///
    ///
    ///
    ///
    ///

    QLabel* lab_r0 = new QLabel;
    lab_r0->setText("« R0 »");
    lab_r0->setAlignment(Qt::AlignCenter);

    r0 = new QLineEdit(this);
    r0->setText(QString("-"));
    r0->setAlignment(Qt::AlignCenter);
    r0->setEnabled(false);

    QVBoxLayout* l_r0 = new QVBoxLayout;
    l_r0->addWidget(lab_r0);
    l_r0->addWidget(r0);

    ///

    QLabel* lab_r1 = new QLabel;
    lab_r1->setText("« R1 »");
    lab_r1->setAlignment(Qt::AlignCenter);

    r1 = new QLineEdit(this);
    r1->setText(QString("-"));
    r1->setAlignment(Qt::AlignCenter);
    r1->setEnabled(false);

    QVBoxLayout* l_r1 = new QVBoxLayout;
    l_r1->addWidget(lab_r1);
    l_r1->addWidget(r1);


    ///

    QLabel* lab_r2 = new QLabel;
    lab_r2->setText("« R2 »");
    lab_r2->setAlignment(Qt::AlignCenter);

    r2 = new QLineEdit(this);
    r2->setText(QString("-"));
    r2->setAlignment(Qt::AlignCenter);
    r2->setEnabled(false);

    QVBoxLayout* l_r2 = new QVBoxLayout;
    l_r2->addWidget(lab_r2);
    l_r2->addWidget(r2);

    ///

    QLabel* lab_r3 = new QLabel;
    lab_r3->setText("« R3 »");
    lab_r3->setAlignment(Qt::AlignCenter);

    r3 = new QLineEdit(this);
    r3->setText(QString("-"));
    r3->setAlignment(Qt::AlignCenter);
    r3->setEnabled(false);

    QVBoxLayout* l_r3 = new QVBoxLayout;
    l_r3->addWidget(lab_r3);
    l_r3->addWidget(r3);

    ///

    QLabel* lab_r4 = new QLabel;
    lab_r4->setText("« R4 »");
    lab_r4->setAlignment(Qt::AlignCenter);

    r4 = new QLineEdit(this);
    r4->setText(QString("-"));
    r4->setAlignment(Qt::AlignCenter);
    r4->setEnabled(false);

    QVBoxLayout* l_r4 = new QVBoxLayout;
    l_r4->addWidget(lab_r4);
    l_r4->addWidget(r4);

    ///

    QLabel* lab_r5 = new QLabel;
    lab_r5->setText("« R5 »");
    lab_r5->setAlignment(Qt::AlignCenter);

    r5 = new QLineEdit(this);
    r5->setText(QString("-"));
    r5->setAlignment(Qt::AlignCenter);
    r5->setEnabled(false);

    QVBoxLayout* l_r5 = new QVBoxLayout;
    l_r5->addWidget(lab_r5);
    l_r5->addWidget(r5);

    ///

    QLabel* lab_r6 = new QLabel;
    lab_r6->setText("« R6 »");
    lab_r6->setAlignment(Qt::AlignCenter);

    r6 = new QLineEdit(this);
    r6->setText(QString("-"));
    r6->setAlignment(Qt::AlignCenter);
    r6->setEnabled(false);

    QVBoxLayout* l_r6 = new QVBoxLayout;
    l_r6->addWidget(lab_r6);
    l_r6->addWidget(r6);

    ///

    QLabel* lab_r7 = new QLabel;
    lab_r7->setText("« R7 »");
    lab_r7->setAlignment(Qt::AlignCenter);

    r7 = new QLineEdit(this);
    r7->setText(QString("-"));
    r7->setAlignment(Qt::AlignCenter);
    r7->setEnabled(false);

    QVBoxLayout* l_r7 = new QVBoxLayout;
    l_r7->addWidget(lab_r7);
    l_r7->addWidget(r7);

    ///
    ///
    ///

    QHBoxLayout* lr_14= new QHBoxLayout;
    lr_14->addLayout(l_r0);
    lr_14->addLayout(l_r1);
    lr_14->addLayout(l_r2);
    lr_14->addLayout(l_r3);

    QHBoxLayout* lr_58= new QHBoxLayout;
    lr_58->addLayout(l_r4);
    lr_58->addLayout(l_r5);
    lr_58->addLayout(l_r6);
    lr_58->addLayout(l_r7);

    QVBoxLayout* l_body = new QVBoxLayout;
    l_body->addLayout(l_header);
    l_body->addLayout(lr_14);
    l_body->addLayout(lr_58);

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


