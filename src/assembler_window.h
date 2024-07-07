#ifndef ASSEMBLER_WINDOW_H
#define ASSEMBLER_WINDOW_H

#include <QPaintEvent>
#include <QPlainTextEdit>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>

class LineNumberArea;

class CodeEditor : public QPlainTextEdit {
        Q_OBJECT

    public:
        CodeEditor(QWidget *parent = nullptr);

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

class assemblerWindow : public QWidget {
public:
    assemblerWindow(QWidget*);


    
};

#endif  // ASSEMBLER_WINDOW_H
