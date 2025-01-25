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

    console = new QLabel(this);
    console->setText("open file\n");
    console->setStyleSheet("border: 1px solid gray;");

    step = new QPushButton;
    step->setText("Step");
    connect(step, &QPushButton::clicked, this, &SimulatorWindow::stepFunc);

    QVBoxLayout* l_con = new QVBoxLayout;
    l_con->addLayout(fn_layout);
    l_con->addWidget(console);
    l_con->addWidget(step);

    ///////////////// PC
    QLabel* lab_pc = new QLabel;
    lab_pc->setText("PC:");

    pc = new QLineEdit(this);
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
    n->setEnabled(false);

    QHBoxLayout* l_n = new QHBoxLayout;
    l_n->addWidget(lab_n);
    l_n->addWidget(n);

    /// z
    QLabel* lab_z = new QLabel;
    lab_z->setText("Z:");

    z = new QLineEdit(this);
    z->setEnabled(false);

    QHBoxLayout* l_z = new QHBoxLayout;
    l_z->addWidget(lab_z);
    l_z->addWidget(z);

    /// z
    QLabel* lab_p = new QLabel;
    lab_p->setText("P:");

    p = new QLineEdit(this);
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

    ram = new QTableWidget(this);
    ram->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ram->setRowCount(MEMORY_SIZE);
    ram->setColumnCount(2);
    ram->verticalHeader()->setVisible(false);


    QTableWidgetItem *newItem = new QTableWidgetItem("Address", 0);
    ram->setHorizontalHeaderItem(0, newItem);
    newItem = new QTableWidgetItem("Value", 0);
    ram->setHorizontalHeaderItem(1, newItem);

    ram->setMaximumWidth(220);

    for (int i=0; i < MEMORY_SIZE; i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString("0x%1").arg(i, 4, 16, QLatin1Char( '0' )), 0);
        ram->setItem(i, 0,  newItem);
    }

    QLabel* lab_ram = new QLabel;
    lab_ram->setText("« RAM »");
    lab_ram->setAlignment(Qt::AlignCenter);

    QVBoxLayout* l_ram = new QVBoxLayout;
    l_ram->addWidget(lab_ram);
    l_ram->addWidget(ram);

    // set main
    QHBoxLayout* l_main = new QHBoxLayout(this);
    l_main->addLayout(l_ram);
    l_main->addLayout(line1);
    l_main->addLayout(l_body);

    clear();
}

void SimulatorWindow::stepFunc() {

    console->setStyleSheet("color:black;");

    simErrCode err = Sim->step();
    console->setText(QString::fromStdString(Sim->getMsg()));

    if (err != OK) {
        console->setStyleSheet("color:red;");
    }

    // update datas
    update();

    // or call init function :)))
    // init();
}

void SimulatorWindow::update() {

    for (auto i : Sim->getEdit()) {
        if (i == "PC") {
            auto num = Sim->getData("PC");
            pc->setText(QString::fromStdString(to_string(num)));
        }

        // ir
        else if (i == "IR") {
            auto num = Sim->getData("IR");
            ir->setText(QString::fromStdString(to_string(num)));
        }

        // mdr
        else if (i == "MDR") {
            auto num = Sim->getData("MDR");
            mdr->setText(QString::fromStdString(to_string(num)));
        }

        // mar
        else if (i == "MAR") {
            auto num = Sim->getData("MAR");
            mar->setText(QString::fromStdString(to_string(num)));
        }

        // n
        else if (i == "N") {
            auto num = Sim->getData("N");
            n->setText(QString::fromStdString(to_string(num)));
        }

        // p
        else if (i == "P") {
            auto num = Sim->getData("P");
            p->setText(QString::fromStdString(to_string(num)));
        }

        // z
        else if (i == "Z") {
            auto num = Sim->getData("Z");
            z->setText(QString::fromStdString(to_string(num)));
        }

        // r0
        else if (i == "R0") {
            auto num = Sim->getData("R0");
            r0->setText(QString::fromStdString(to_string(num)));
        }

        // r1
        else if (i == "R1") {
            auto num = Sim->getData("R1");
            r1->setText(QString::fromStdString(to_string(num)));
        }

        // r2
        else if (i == "R2") {
            auto num = Sim->getData("R2");
            r2->setText(QString::fromStdString(to_string(num)));
        }

        // r3
        else if (i == "R3") {
            auto num = Sim->getData("R3");
            r3->setText(QString::fromStdString(to_string(num)));
        }

        // r4
        else if (i == "R4") {
            auto num = Sim->getData("R4");
            r4->setText(QString::fromStdString(to_string(num)));
        }

        // r5
        else if (i == "R5") {
            auto num = Sim->getData("R5");
            r5->setText(QString::fromStdString(to_string(num)));
        }

        // r6
        else if (i == "R6") {
            auto num = Sim->getData("R6");
            r6->setText(QString::fromStdString(to_string(num)));
        }

        // r7
        else if (i == "R7") {
            auto num = Sim->getData("R7");
            r7->setText(QString::fromStdString(to_string(num)));
        }

        else if (i == "ARR") {
            auto addr = Sim->getData("MAR");
            auto new_val = Sim->getData("ARR");

            // edit table
            ram->item(addr, 1)->setText(QString("0x%1").arg(new_val, 4, 16, QLatin1Char( '0' )));
        }
    }
}

void SimulatorWindow::openFile() {
    // load file path
    Sim->setFilePath(file_name_lineE->text().toStdString());

    // open file
    if (Sim->openFile()) {
        init();
    }

    else {
        clear();
    }

    console->setText(QString::fromStdString(Sim->getMsg()));
}

void SimulatorWindow::init() {

    console->setStyleSheet("color:black;");
    step->setEnabled(true);

    // pc
    auto num = Sim->getData("PC");
    pc->setText(QString::fromStdString(to_string(num)));

    // ir
    num = Sim->getData("IR");
    ir->setText(QString::fromStdString(to_string(num)));

    // mdr
    num = Sim->getData("MDR");
    mdr->setText(QString::fromStdString(to_string(num)));

    // mar
    num = Sim->getData("MAR");
    mar->setText(QString::fromStdString(to_string(num)));

    // n
    num = Sim->getData("N");
    n->setText(QString::fromStdString(to_string(num)));

    // p
    num = Sim->getData("P");
    p->setText(QString::fromStdString(to_string(num)));

    // z
    num = Sim->getData("Z");
    z->setText(QString::fromStdString(to_string(num)));

    // r0
    num = Sim->getData("R0");
    r0->setText(QString::fromStdString(to_string(num)));

    // r1
    num = Sim->getData("R1");
    r1->setText(QString::fromStdString(to_string(num)));

    // r2
    num = Sim->getData("R2");
    r2->setText(QString::fromStdString(to_string(num)));

    // r3
    num = Sim->getData("R3");
    r3->setText(QString::fromStdString(to_string(num)));

    // r4
    num = Sim->getData("R4");
    r4->setText(QString::fromStdString(to_string(num)));

    // r5
    num = Sim->getData("R5");
    r5->setText(QString::fromStdString(to_string(num)));

    // r6
    num = Sim->getData("R6");
    r6->setText(QString::fromStdString(to_string(num)));

    // r7
    num = Sim->getData("R7");
    r7->setText(QString::fromStdString(to_string(num)));

    // load ram into ram table
    _16_BIT* load_ram = Sim->getMem();
    for (int i=0; i < MEMORY_SIZE; i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString("0x%1").arg(load_ram[i], 4, 16, QLatin1Char( '0' )), 0);
        ram->setItem(i, 1,  newItem);
    }
}

void SimulatorWindow::clear() {

    console->setStyleSheet("color:black;");
    step->setEnabled(false);

    // pc
    pc->setText("-");

    // ir
    ir->setText("-");

    // mdr
    mdr->setText("-");

    // mar
    mar->setText("-");

    // n
   n->setText("-");

    // p
    p->setText("-");

    // z
    z->setText("-");

    // r0
    r0->setText("-");

    // r1
    r1->setText("-");

    // r2
    r2->setText("-");

    // r3
    r3->setText("-");

    // r4
    r4->setText("-");

    // r5
    r5->setText("-");

    // r6
    r6->setText("-");

    // r7
    r7->setText("-");

    // claer ram into ram table
    for (int i=0; i < MEMORY_SIZE; i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem("", 0);
        ram->setItem(i, 1,  newItem);
    }
}
