#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QPainter>
#include <QFileDialog>
#include <qpixmap.h>
#include <qdebug.h>
#include <qpdfwriter.h>
#include <qmessagebox.h>
#include <locale>

#include "saver.h"


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

       standart_cursor.load(":/new/cursor/cursor.png");
       circle_cursor.load(":/new/cursor/circle_cursor.png");
       cleaner_cursor.load(":/new/cursor/cleaner_cursor.png");
       rectangle_cursor.load(":/new/cursor/rectangle_cursor.png");
       line_cursor.load(":/new/cursor/line_cursor.png");



       this->setWindowTitle("Доска для лекций");

       custom_cursor = QCursor(QPixmap::fromImage(standart_cursor),0,32);

       ui->graphicsView->viewport()->setCursor(custom_cursor);

       timer = new QTimer();
       connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
       timer->start(100);

       connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(Cleaner()));
       connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setColor()));
       connect(ui->buttonLeft, SIGNAL(clicked()), this, SLOT(prevScene()));
       connect(ui->buttonRigth, SIGNAL(clicked()), this, SLOT(nextScene()));
       connect(ui->actionClear_canvas, SIGNAL(triggered()), this, SLOT(clearScene()));
       connect(ui->actionImage, SIGNAL(triggered()), this, SLOT(saveInImage()));
       connect(ui->actionImage_list, SIGNAL(triggered()), this, SLOT(saveInImages()));
       connect(ui->actionPDF_2, SIGNAL(triggered()), this, SLOT(saveInPDF()));
       connect(ui->action_3, SIGNAL(triggered()), this, SLOT(verification()));
       connect(ui->action_7, SIGNAL(triggered()), this, SLOT(CleanerVariant()));
       connect(ui->actionSet_background_color, SIGNAL(triggered()), this, SLOT(SetBackgroundColor()));

       connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(Checked(int)));
       connect(ui->comboBox_2, SIGNAL(activated(int)), this, SLOT(resizePen(int)));

       Scene()->setBackgroundBrush(QBrush(QColor(255,255,255)));

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

void MainWindow::CleanerVariant(){

    Scene()->CleanerVariant = !Scene()->CleanerVariant;

}

void MainWindow::SetBackgroundColor(){


    QColor _color = QColorDialog::getColor(Scene()->color,this,tr("Color"),QColorDialog::ColorDialogOption::ShowAlphaChannel);

    Scene()->setBackgroundBrush(QBrush(_color));

}

void MainWindow::Cleaner(){

    Scene()->phigure = Phigure::cleaner;

    reloadCustomCursor();

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    ui->graphicsView->resize(event->size().width() - 20,event->size().height() - 10);
    QWidget::resizeEvent(event);
}

void MainWindow::setColor(){

    Scene()->color = QColorDialog::getColor(Scene()->color,this,tr("Color"),QColorDialog::ColorDialogOption::ShowAlphaChannel);

    QString red = std::to_string(Scene()->color.red()).c_str();
    QString green = std::to_string(Scene()->color.green()).c_str();
    QString blue = std::to_string(Scene()->color.blue()).c_str();

    std::string style = "rgb(" + red.toStdString() + "," + green.toStdString() + "," + blue.toStdString() + ")";

    ui->pushButton->setStyleSheet(("background-color: " + style).c_str());

}

void MainWindow::resizePen(int value){

    Scene()->size = ui->comboBox_2->itemText(value).toInt();


}

void MainWindow::clearScene(){

    Scene()->clear();
    Scene()->initialize();

}

void MainWindow::nextScene(){

    QColor color = Scene()->color;
    qreal real = Scene()->size;
    QRectF rect = Scene()->sceneRect();
    int phigure = Scene()->phigure;

    sceneId++;

    if(sceneId >= scene.size()){

        scene.push_back(new customScene());

        Scene()->size = real;
        Scene()->color = color;
        Scene()->setSceneRect(rect);

        Scene()->setBackgroundBrush(scene.at(sceneId - 1)->backgroundBrush());

    }else {

        Scene()->size = real;
        Scene()->color = color;

    }

    Scene()->phigure = phigure;
    ui->graphicsView->setScene(Scene());



    ui->label_2->setText(tr(("Полотно : " + std::to_string(sceneId+1)).c_str()));
    ui->label_4->setText(tr(("Количество : " + std::to_string(scene.size())).c_str()));

}
void MainWindow::prevScene(){



    if(sceneId > 0){
        QColor color = Scene()->color;
        qreal real = Scene()->size;
        int phigure = Scene()->phigure;

        sceneId--;

        Scene()->size = real;
        Scene()->color = color;
        Scene()->phigure = phigure;
        Scene()->setSceneRect(Scene()->sceneRect());


        ui->graphicsView->setScene(Scene());
        ui->label_2->setText(tr(("Полотно : " + std::to_string(sceneId+1)).c_str()));
        ui->label_4->setText(tr(("Количество : " + std::to_string(scene.size())).c_str()));
    }

}

void MainWindow::saveInImage(){

    QUrl url = QFileDialog::getSaveFileUrl(this, tr("Save As"));
    QString fileName = url.toLocalFile();

    Saver::SaveImage(Scene(),fileName,ui->graphicsView->sizeHint() * 2);

}

void MainWindow::saveInImages(){

    QUrl url = QFileDialog::getSaveFileUrl(this, tr("Save As"));
    QString fileName = url.toLocalFile();

   Saver::SaveInImages(scene,fileName,ui->graphicsView->sizeHint() * 2);

}

void MainWindow::saveInPDF(){

    QUrl url = QFileDialog::getSaveFileUrl(this, tr("Save As"));
    QString fileName = url.toLocalFile();

    Saver::SaveInPDF(scene,fileName,ui->graphicsView->sizeHint() * 2);

}

void MainWindow::Checked(int index){


    Scene()->phigure = index;
    reloadCustomCursor();

}


void MainWindow::verification(){

    this->setWindowTitle("Доска для лекций");



}

void MainWindow::closeEvent(QCloseEvent *event){

    event->ignore();

   if(QMessageBox::Yes == QMessageBox::question(this,"Выход","Вы дейсвительно хотите выйти?",QMessageBox::Yes | QMessageBox::No)){

       event->accept();
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Control){

      Scene()->phigure = Phigure::cleaner;

    }else
    if(event->key() == Qt::Key_Z){

      Scene()->phigure = Phigure::pen;
      ui->comboBox->setCurrentIndex(Scene()->phigure);
    }else
    if(event->key() == Qt::Key_X){

      Scene()->phigure = Phigure::rectangle;
      ui->comboBox->setCurrentIndex(Scene()->phigure);

    }else
    if(event->key() == Qt::Key_S){

      Scene()->phigure = Phigure::dash_rectangle;
      ui->comboBox->setCurrentIndex(Scene()->phigure);

    }else
    if(event->key() == Qt::Key_C){

      Scene()->phigure = Phigure::line;
      ui->comboBox->setCurrentIndex(Scene()->phigure);

    }else
    if(event->key() == Qt::Key_D){

      Scene()->phigure = Phigure::dash_line;
      ui->comboBox->setCurrentIndex(Scene()->phigure);

    }else
    if(event->key() == Qt::Key_V){

      Scene()->phigure = Phigure::circle;
      ui->comboBox->setCurrentIndex(Scene()->phigure);

    }else
    if(event->key() == Qt::Key_F){

      Scene()->phigure = Phigure::dash_circle;
      ui->comboBox->setCurrentIndex(Scene()->phigure);

    }else
    if(event->key() == Qt::Key_Left){

        prevScene();
    }else
    if(event->key() == Qt::Key_Right){

        nextScene();

    }else
    if(event->key() >= 49 && event->key() < 55){

        int index = event->key() - 49;

        Scene()->size = ui->comboBox_2->itemText(index).toDouble();
        ui->comboBox_2->setCurrentIndex(index);
    }


    reloadCustomCursor();

}

void MainWindow::reloadCustomCursor(){
    switch (Scene()->phigure) {

    case Phigure::pen:
        custom_cursor = QCursor(QPixmap::fromImage(standart_cursor),0,32);
        break;
    case Phigure::circle:
        custom_cursor = QCursor(QPixmap::fromImage(circle_cursor),16,16);
        break;
    case Phigure::cleaner:
        custom_cursor = QCursor(QPixmap::fromImage(cleaner_cursor),0,0);
        break;
    case Phigure::dash_circle:
        custom_cursor = QCursor(QPixmap::fromImage(circle_cursor),16,16);
        break;
    case Phigure::line:
        custom_cursor = QCursor(QPixmap::fromImage(line_cursor),2,2);
        break;
    case Phigure::dash_line:
        custom_cursor = QCursor(QPixmap::fromImage(line_cursor),2,2);
        break;
    case Phigure::rectangle:
        custom_cursor = QCursor(QPixmap::fromImage(rectangle_cursor),0,0);
        break;
    case Phigure::dash_rectangle:
        custom_cursor = QCursor(QPixmap::fromImage(rectangle_cursor),0,0);
        break;

    }

           ui->graphicsView->viewport()->setCursor(custom_cursor);

}
