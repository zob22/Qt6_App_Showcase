#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>

#include <scene.h>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer_1;
    Scene *scene;
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
    void notifyTimer();
    void on_brushButton_clicked();
    void on_lineButton_clicked();
    void on_circleButton_clicked();
    void on_moveButton_clicked();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionPrint_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
