#ifndef ASSEMBLER_WINDOW_H
#define ASSEMBLER_WINDOW_H

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPainter>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QSize>
#include <QTextBlock>
#include <QVBoxLayout>
#include <QWidget>

#include "assembler.h"

class LineNumberArea;

class CodeEditor : public QPlainTextEdit {
        Q_OBJECT

    public:
        CodeEditor(QWidget *parent = nullptr);

        QString getText();
        void lineNumberAreaPaintEvent(QPaintEvent *event);
        int lineNumberAreaWidth();

    protected:
        void resizeEvent(QResizeEvent *event) override;

    private slots:
        void updateLineNumberAreaWidth(int newBlockCount);
        void highlightCurrentLine();
        void updateLineNumberArea(const QRect &rect, int dy);

    private:
        QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget {
    private:
        CodeEditor *codeEditor;

    public:
        LineNumberArea(CodeEditor *editor)
            : QWidget(editor), codeEditor(editor) {}

        QSize sizeHint() const override {
            return QSize(codeEditor->lineNumberAreaWidth(), 0);
        }

    protected:
        void paintEvent(QPaintEvent *event) override {
            codeEditor->lineNumberAreaPaintEvent(event);
        }
};

class AssemblerWindow : public QWidget {
        Q_OBJECT

    private:
        Assembler *ASB;

        QLineEdit *file_name_lineE;
        CodeEditor *editor;

    public:
        AssemblerWindow(QWidget *parent = nullptr);

    public slots:
        void changeFileName();
        void compile();
        void saveFile();
};

#endif  // ASSEMBLER_WINDOW_H
