#include "notepad.h"
#include "ui_notepad.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionOpen_triggered()
{
    //Launches an openfile dialog which returns the selected filename
    //`tr()` is used to make strings translateable
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("All files (*.*);;Text Files (*.txt);;C++ Files(*.cpp, *.h)"));

    if(!fileName.isEmpty())
    {
        QFile file(fileName);

        //Atempt to open the selected file
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }

        //Read the file into a TextStream, and set it to the TextEdit widget, then close the file.
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}

void Notepad::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"), QString(), tr("All files (*.*);;Text Files (*.txt);;C++ Files(*.cpp, *.h)"));

    if(!fileName.isEmpty())
    {
        QFile file(fileName);

        if(!file.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
            return;
        }
        else
        {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}
