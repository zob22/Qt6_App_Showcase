#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QRegExp>

//Use the standard UI namespace which is tied to the .ui file
QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    //Declares our class as a QObject
    Q_OBJECT

public:
    //Declare a constructor
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void ClearAll();
    void Mem();
    void DecButtonPressed();
    void Backspace();
};
#endif // CALCULATOR_H
