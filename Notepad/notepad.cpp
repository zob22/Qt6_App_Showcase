#include "notepad.h"
#include "ui_notepad.h"

//Notepad constructor
Notepad::Notepad(QWidget *parent)
    //Call the QMainWindow constructor
    : QMainWindow(parent),
    //Create the UI class and assign it to the ui member
    ui(new Ui::Notepad)
{
    //Setup the UI
    ui->setupUi(this);
    //Have the textedit widget take up the whole window
    this->setCentralWidget(ui->textEdit);
}

//Destructor that deletes the UI
Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    //Global referencing the current file that we are clearing
    currentfile.clear();
    //Clear the textEdit widget buffer
    ui->textEdit->setText(QString());
}

void Notepad::on_actionOpen_triggered()
{
    //Opens a dialog that allows you to select a file to open
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    //An object for reading and writing files
    QFile file(filename);
    //Store the currentFile name
    currentfile= filename;
    // Try to open the file as a read only file if possible or display a warning dialog box
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    //Set the title for the window to the file name
    setWindowTitle(filename);
    //Interface for reading text
    QTextStream in(&file);
    //Copy text in the string
    QString text = in.readAll();
    //Put the text in the textEdit widget
    ui->textEdit->setText(text);
    //Close the file
    file.close();
}

void Notepad::on_actionSave_triggered()
{
    //Opens a dialog for saving a file
    QString filename =QFileDialog::getSaveFileName(this, "Save as");
    //An object for reading and writing files
    QFile file(filename);
    //Try to open a file with write only options
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    //Store the currentFile name
    currentfile= filename;
    //Set the title for the window to the file name
    setWindowTitle(filename);
    //Interface for writing text
    QTextStream out(&file);
    //Copy text in the textEdit widget and convert to plain text
    QString text = ui->textEdit->toPlainText();
    //Output to file
    out<<text;
    //Close the file
    file.close();
}

void Notepad::on_actionPrint_triggered()
{
    //Allows for interacting with printer
    QPrinter printer;
    //You'll put your printer name here
    printer.setPrinterName("Printer Name");
    //Create the print dialog and pass the name and parent
    QPrintDialog pDialog(&printer, this);
    if (pDialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }
    // Send the text to the printer
    ui->textEdit->print(&printer);
}

void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
