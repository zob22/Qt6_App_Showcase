#include "notepad.h"
//Handles widgets, event handling, mouse, windows look and feel
#include <QApplication>

int main(int argc, char *argv[])
{
    //Create the application object
    QApplication a(argc, argv);
    //Create the notepad object
    Notepad w;
    //Displays object on screen
    w.show();
    //Place the application in a loop where events are handled
    return a.exec();
}
