#include "TextEditor.h"
#include <qmessagebox.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFontDialog>
#include <QColorDialog>
#include <QStatusBar>
#include <QInputDialog>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("My First Qt Text Editor");
    ui.textEdit->setPlainText("Hello Qt!");
    updateStatusBar();

    connect(ui.actionNw, &QAction::triggered, ui.textEdit, &QTextEdit::clear);
    connect(ui.actionOpen,&QAction::triggered,this,&TextEditor::openFile);
    //connect(ui.actionOpen,&QAction::triggered,ui.textEdit,&QTextEdit::clear);
    connect(ui.actionSave,&QAction::triggered,this,&TextEditor::saveFile);
    connect(ui.actionSave_As, &QAction::triggered, this, &TextEditor::saveAsFile);
    connect(ui.actionExit,&QAction::triggered,this,&TextEditor::exitApp);//Custom slot
    //connect(ui.actionExit,&QAction::triggered,this,&QWidget::close);//Direct connection slot
    connect(ui.textEdit,&QTextEdit::textChanged, this, &TextEditor::documentModified);
    connect(ui.actionFont,&QAction::triggered, this, &TextEditor::selectFont);//SelectColor()
    connect(ui.actionText_Color, &QAction::triggered, this, &TextEditor::SelectColor);
    connect(ui.textEdit, &QTextEdit::textChanged, this, &TextEditor::updateStatusBar);
    connect(ui.actionFind, &QAction::triggered, this, &TextEditor::FindText);
}

TextEditor::~TextEditor()
{}

void TextEditor::openFile()
{
    //QMessageBox::information(this,"Open","Open menu clicked");

    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream IN(&file);

        ui.textEdit->setPlainText(IN.readAll());

        file.close();

        currentFile = fileName;
        isFileModified = false;
        setWindowTitle(currentFile);
    }
}

void TextEditor::saveFile()
{
    //QMessageBox::information(this, "save", "Save menu clicked");

    if (currentFile.isEmpty())
    {
        saveAsFile();
        return;
    }

    QFile file(currentFile);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        out << ui.textEdit->toPlainText();

        file.close();

        isFileModified = false;

        setWindowTitle(currentFile);
    }
}

void TextEditor::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save As","","Text Files (*.txt)");

    if (fileName.isEmpty())
        return;

    currentFile = fileName;

    QFile file(currentFile);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        out << ui.textEdit->toPlainText();

        file.close();

        setWindowTitle(currentFile);
    }
}

void TextEditor::exitApp()
{
    //QMessageBox::information(this, "Exit", "Exit menu clicked");

    auto reply = QMessageBox::question(this,"Exit","Are you sure you want to exit?",QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        close();
    }
}

void TextEditor::documentModified()
{
    isFileModified = true;

    if (currentFile.isEmpty())
    {
        setWindowTitle("Untitled *");
    }
    else
    {
        setWindowTitle(currentFile + " *");
    }
}

void TextEditor::selectFont()
{
    bool ok;

    QFont font =QFontDialog::getFont(&ok,ui.textEdit->font(),this,"Select Font");

    if (ok)
    {
        ui.textEdit->setFont(font);
    }
}

void TextEditor::SelectColor()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"Select Text Color");

    if (color.isValid())
    {
        ui.textEdit->setTextColor(color);
    }
}

void TextEditor::updateStatusBar()
{
    QString text = ui.textEdit->toPlainText();

    int len = text.length();
    int lines = ui.textEdit->document()->lineCount();

    statusBar()->showMessage(
        QString("Characters: %1    Lines: %2").arg(len).arg(lines));
}

void TextEditor::FindText()
{
    bool ok;

    QString searchText =QInputDialog::getText(this,"Find","Enter text:", QLineEdit::Normal,"",&ok);

    if (!ok || searchText.isEmpty())
        return;

    if (!ui.textEdit->find(searchText))
    {
        QMessageBox::information(
            this,
            "Find",
            "Text not found");
    }
}

