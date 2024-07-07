#include "assembler_window.h"

CodeEditor::CodeEditor(QWidget* parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this,
            &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this,
            &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this,
            &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 5 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect& rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(),
                               rect.height());

    if (rect.contains(viewport()->rect())) updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent* e) {
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();

    lineNumberArea->setGeometry(
        QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::darkGray).lighter(180);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::darkGray);

    QTextBlock block = firstVisibleBlock();

    int blockNumber = block.blockNumber();
    int top =
        qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(),
                             fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

QString CodeEditor::getText() {
    QTextDocument* docs = this->document();
    QString txt = docs->toRawText();

    QString final;

    // the char is split point \u2029
    for (auto i : txt.split(u'\u2029', Qt::SkipEmptyParts)) {
        // qDebug() << i;
        if (!i.isEmpty()) {
            final += i;
            final += '\n';
        }
    }

    // qDebug() << final;

    return final;
}

AssemblerWindow::AssemblerWindow(QWidget* parent) : QWidget(parent) {

    string file_name = "MEMMORY";
    ASB = new Assembler(file_name);

    QLabel* file_name_label = new QLabel(this);
    file_name_label->setText("File Name:");

    QLabel* file_format_label = new QLabel(this);
    file_format_label->setText(".bin");

    file_name_lineE = new QLineEdit(this);
    file_name_lineE->setText(QString::fromStdString(file_name));

    QPushButton* fn_save_button = new QPushButton(this);
    fn_save_button->setText("Save");
    connect(fn_save_button, &QPushButton::clicked, this,
            &AssemblerWindow::changeFileName);

    QHBoxLayout* fn_layout = new QHBoxLayout();
    fn_layout->addWidget(file_name_label);
    fn_layout->addWidget(file_name_lineE);
    fn_layout->addWidget(file_format_label);
    fn_layout->addWidget(fn_save_button);

    editor = new CodeEditor(this);
    editor->setFocus();

    QPushButton* compiler_button = new QPushButton(this);
    compiler_button->setText("Compile Code");
    connect(compiler_button, &QPushButton::clicked, this,
            &AssemblerWindow::compile);

    QPushButton* save_button = new QPushButton(this);
    save_button->setText("Save File");
    connect(save_button, &QPushButton::clicked, this,
            &AssemblerWindow::saveFile);

    msg = new QLabel;
    msg->hide();
    connect(editor, &QPlainTextEdit::selectionChanged, msg, &QLabel::hide);
    connect(file_name_lineE, &QLineEdit::textChanged, msg, &QLabel::hide);
    connect(file_name_lineE, &QLineEdit::selectionChanged, msg, &QLabel::hide);

    QVBoxLayout* body_layout = new QVBoxLayout(this);
    body_layout->addLayout(fn_layout);
    body_layout->addWidget(editor);
    body_layout->addWidget(compiler_button);
    body_layout->addWidget(save_button);
    body_layout->addWidget(msg);
}

void AssemblerWindow::changeFileName() {

    QString new_fn = file_name_lineE->text();
    ASB->setFileName(new_fn.toStdString());

    msgHandler(true, "File Name Change");

    // qDebug() << QString::fromStdString(ASB->getFileName());
}

void AssemblerWindow::compile() {
    QString codes = editor->getText();

    msgHandler(ASB->compiler(codes.toStdString()), "Compile");
}

void AssemblerWindow::saveFile() {
    msgHandler(ASB->saveFile(), "Save File");
}

void AssemblerWindow::msgHandler(errorCode err_code, QString label) {

    QString err_msg =  "[" + label + "]" + ": ";
    if (err_code == OK_VALID) {
        err_msg += "OK, Done!";
        msg->setStyleSheet("color: green;");
    }

    else {
        err_msg += QString::fromStdString(ASB->getMsg());
        msg->setStyleSheet("color: red;");
    }

    qDebug() << err_msg;
    msg->setText(err_msg);
    msg->show();
}

void AssemblerWindow::msgHandler(bool err_flag, QString label) {

    QString err_msg =  "[" + label + "]" + ": ";
    if (err_flag) {
        err_msg += "OK, Done!";
        msg->setStyleSheet("color: green;");
    }

    else {
        err_msg += QString::fromStdString(ASB->getMsg());
        msg->setStyleSheet("color: red;");
    }

    qDebug() << err_msg;
    msg->setText(err_msg);
    msg->show();
}

// EOF
