#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TextEditor.h"

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

private:
    Ui::TextEditorClass ui;

    QString currentFile;
    bool isFileModified;

private slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void exitApp();
    void documentModified();
    void selectFont();
    void SelectColor();
    void updateStatusBar();
    void FindText();
};

