#include "customscene.h"

customScene::customScene(QObject *parent) : QGraphicsScene(parent)
{

}

customScene::~customScene(){


}

void customScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    previousPoint = event->scenePos();
}

void customScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(color,size,Qt::SolidLine,Qt::RoundCap));



    previousPoint = event->scenePos();
}
