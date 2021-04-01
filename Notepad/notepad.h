//Ensures header file is only loaded once
#ifndef NOTEPAD_H
#define NOTEPAD_H

//Provides the main application window on which the ui is built
#include <QMainWindow>
//Widgets that provide additional functionality to the ui
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

//Use the UI namespace which is tied to the .ui file
QT_BEGIN_NAMESPACE
namespace Ui{ class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    //Declare class as QObject
    Q_OBJECT

public:
    //Declare a constructor and state this widget has no parent
    Notepad(QWidget *parent = nullptr);
    //Destructor used to free resources
    ~Notepad();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    //Point to ui class
    Ui::Notepad *ui;
    //Creates a special Qt string which will hold the users input
    QString currentfile = "";
};
#endif // NOTEPAD_H
