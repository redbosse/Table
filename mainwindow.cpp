#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QPainter>
#include <QFileDialog>
#include <qpixmap.h>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene.push_back(new customScene());
    Scene()->size = 2;
    Scene()->color = Qt::black;

       ui->graphicsView->setScene(Scene());
       ui->graphicsView->setRenderHint(QPainter::Antialiasing);


       timer = new QTimer();
       connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
       timer->start(100);

       connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(resizePen(int)));

       connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(setColor()));
       connect(ui->buttonLeft, SIGNAL(clicked()), this, SLOT(prevScene()));
       connect(ui->buttonRigth, SIGNAL(clicked()), this, SLOT(nextScene()));
       connect(ui->actionClear_canvas, SIGNAL(triggered()), this, SLOT(clearScene()));
       connect(ui->actionImage, SIGNAL(triggered()), this, SLOT(saveInImage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{

    timer->stop();
    Scene()->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    ui->graphicsView->resize(event->size().width() - 20,event->size().height() - 10);
    QWidget::resizeEvent(event);
}

void MainWindow::setColor(){

    Scene()->color = QColorDialog::getColor(Scene()->color,this,tr("Color"),QColorDialog::ColorDialogOption::ShowAlphaChannel);

}

void MainWindow::resizePen(int value){

    Scene()->size = value;
    ui->label->setText(tr("Size : ") + std::to_string(value).c_str());

}

void MainWindow::clearScene(){

    Scene()->clear();

}

void MainWindow::nextScene(){

    QColor color = Scene()->color;
    qreal real = Scene()->size;
    QRectF rect = Scene()->itemsBoundingRect();

    sceneId++;

    if(sceneId >= scene.size()){

        scene.push_back(new customScene());

        Scene()->size = real;
        Scene()->color = color;

    }else {

        Scene()->size = real;
        Scene()->color = color;

    }

    ui->graphicsView->setScene(Scene());
    ui->graphicsView->setSceneRect(rect);

    ui->label_2->setText(tr(("Canvas number : " + std::to_string(sceneId+1)).c_str()));
    ui->label_4->setText(tr(("Canvas count : " + std::to_string(scene.size())).c_str()));

}
void MainWindow::prevScene(){



    if(sceneId > 0){
        QColor color = Scene()->color;
        qreal real = Scene()->size;
        QRectF rect = Scene()->itemsBoundingRect();

        sceneId--;

        Scene()->size = real;
        Scene()->color = color;

        ui->graphicsView->setScene(Scene());
        ui->graphicsView->setSceneRect(rect);
        ui->label_2->setText(tr(("Canvas number : " + std::to_string(sceneId+1)).c_str()));
        ui->label_4->setText(tr(("Canvas count : " + std::to_string(scene.size())).c_str()));
    }

}

void MainWindow::saveInImage(){


    QUrl url = QFileDialog::getSaveFileUrl(this, tr("Save As"));
    QString fileName = url.toLocalFile();

    if(fileName.size() > 0){

        QImage* img = new QImage(ui->graphicsView->sizeHint() * 2,QImage::Format_ARGB32);
        QPainter* painter = new QPainter(img);
        painter->setRenderHint(QPainter::Antialiasing);

        Scene()->render(painter);

        img->save(fileName + tr(".png"));


        img = new QImage(ui->graphicsView->sizeHint() * 2,QImage::Format_ARGB32);



    delete painter;
    delete img;
    }



}

