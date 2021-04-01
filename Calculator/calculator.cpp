#include "calculator.h"
#include "ui_calculator.h"

//Holds value in calculator
double calcVal = 0;
double memVal;
double solution;
//Defines the last button pressed
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

//Constructor
Calculator::Calculator(QWidget *parent)
    //call a library constructor
    : QMainWindow(parent)
      //create the ui class and assign it to ui member
      ,
      ui(new Ui::Calculator)
{
    // Setup the UI
    ui->setupUi(this);
    //Sets the display to 0 by default
    ui->Display->setText(QString::number(calcVal));
    //An array that holds the references to all the number buttons
    QPushButton *numButtons[10];
    //Cycle through locating the buttons
    for (int i = 0; i < 10; ++i)
    {
        QString butName = "Button" + QString::number(i);
        //Get the buttons by name and add to array
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        //When the button is released call num_pressed()
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    //Connect Decimal
    connect(ui->Decimal, SIGNAL(released()), this, SLOT(DecButtonPressed()));
    //Connect Backspace
    connect(ui->Delete, SIGNAL(released()), this, SLOT(Backspace()));
    //Connect signals and slots for math buttons
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    //Connect equals button
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    //Connect change sign
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    //Connect clear button
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearAll()));
    //Connect mem buttons
    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(Mem()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(Mem()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(Mem()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();
    // Get number on button
    QString butVal = button->text();
    // Get the value in the display
    QString displayVal = ui->Display->text();
    // Put the new number to the right of whats there
    QString newVal = displayVal + butVal;
    // Converts number to double type
    double dblNewVal = newVal.toDouble();
    // Set value in display and allow up to 15 digits before using exponents
    ui->Display->setText(QString::number(dblNewVal, 'g', 15));
    //}
}

void Calculator::MathButtonPressed()
{
    // Cancel out previous math button clicks
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    // Store current value in Display
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();
    // Get math symbol on the button
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }
    else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }
    // Clear display
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    // Holds new calculation
    solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    // Make sure a math button was pressed
    if (addTrigger || subTrigger || multTrigger || divTrigger)
    {
        if (addTrigger)
        {
            solution = calcVal + dblDisplayVal;
        }
        else if (subTrigger)
        {
            solution = calcVal - dblDisplayVal;
        }
        else if (multTrigger)
        {
            solution = calcVal * dblDisplayVal;
        }
        else
        {
            solution = calcVal / dblDisplayVal;
        }
    }
    // Put solution in display
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign()
{
    // Get the value in the display
    QString displayVal = ui->Display->text();
    // Regular expression checks if it is a number plus sign
    QRegExp reg("[-+]?[0-9.]*");
    // If it is a number change the sign
    if (reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        // Put solution in display
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearAll()
{
    ui->Display->setText("0");
}

void Calculator::Mem()
{
    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();
    // Regular expression checks if it is a add clear or get
    QRegExp reg("M([-+]?)");
    reg.exactMatch(button->text());
    QString match = reg.capturedTexts()[1];
    // If it is a number change the sign
    if (QString::compare(match, "-") == 0)
    {
        memVal = 0;
    }
    else if (QString::compare(match, "+") == 0)
    {
        memVal += solution;
    }
    else
        //
        ui->Display->setText(QString::number(memVal, 'g', 16));
}

void Calculator::DecButtonPressed()
{
    //Check to make sure there are no other decimals
    if (ui->Display->text().contains("."))
    {
        return;
    }
    ui->Display->setText(ui->Display->text() + ".");
}

void Calculator::Backspace()
{
        ui->Display->backspace();
}
