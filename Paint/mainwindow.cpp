#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene();
    ui->graphicsView->setScene(scene);
    timer = new QTimer();
    timer_1 = new QTimer();
    connect(timer_1, &QTimer::timeout, this, &MainWindow::notifyTimer);
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0, 0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::notifyTimer()
{
    ui->label->setText("");
    timer_1->stop();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void MainWindow::on_circleButton_clicked()
{
    scene->mode = 2;
}

void MainWindow::on_lineButton_clicked()
{
    scene->mode = 1;
}

void MainWindow::on_brushButton_clicked()
{
    scene->mode = 0;
}

void MainWindow::on_moveButton_clicked()
{
    scene->mode = 3;
}

void MainWindow::on_actionNew_triggered()
{
    scene->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    //Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    if (!fileName.isEmpty()) {
        QImage image(fileName);

        if (image.isNull()) {
            QMessageBox::information(this, "Image Viewer", "Error Displaying image");
            return;
        }
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->clear();
        scene->addItem(item);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QImage image(scene->width(), scene->height(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    scene->render(&painter);
    image.save("test.png", "PNG", 100);
    ui->label->setText("Saving");
    timer_1->start(2000);
}

void MainWindow::on_actionPrint_triggered()
{
    //Allows for interacting with printer
    QPrinter printer;
    //You'll put your printer name here
    printer.setPrinterName("Printer Name");
    // create the print dialog and pass the name and parent
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        //Send the image to the printer
        scene->render(&painter);
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
