#include "saver.h"

Saver::Saver(){}

void Saver::SaveInImages(vector<customScene*>& scene, const QString &filename, const QSize &size){

    if(filename.size() > 0){

        for(size_t i = 0; i < scene.size();i++){

            QImage* img = renderScene(scene.at(i),size);
            img->save((filename.toStdString() + "_" + to_string(i) + ".png").c_str());

            delete img;
        }
    }

}

void Saver::SaveInPDF(vector<customScene*>& scene, const QString &filename, const QSize &size){

    if(filename.size() > 0){

        QPdfWriter writer(filename + ".pdf");

        writer.setPageSize(QPageSize(size));
        writer.setPageMargins(QMargins(0, 0, 0, 0));

        QPainter painter(&writer);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Times", 10));

        for (size_t i = 0 ; i < scene.size(); i++) {

            QImage* img = Saver::renderScene(scene.at(i),size);

            painter.drawImage(QRect(0,0,painter.device()->width(),painter.device()->height()), *img);

            writer.newPage();

            delete img;

         }

         painter.end();


    }


}

void Saver::SaveImage(QGraphicsScene* scene,const QString& filename,const QSize& size){

    if(filename.size() > 0){

        QImage* img = renderScene(scene,size);
        img->save((filename.toStdString() + ".png").c_str());

        delete img;
    }
}

void Saver::SaveProject(QGraphicsScene *scenes){


}

QImage* Saver::renderScene(QGraphicsScene* scene,const QSize& size){


    QImage* img = new QImage(size * 2,QImage::Format_ARGB32);
    QPainter* painter = new QPainter(img);
    painter->setRenderHint(QPainter::Antialiasing);

    scene->render(painter);


    delete painter;

    return img;

}
