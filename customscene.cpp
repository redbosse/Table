#include "customscene.h"

customScene::customScene(QObject *parent) : QGraphicsScene(parent)
{
   initialize();
}


customScene::~customScene(){


}

void customScene::initialize(){

    dashpolyItem = addPolygon(QPolygon(),color);
    polyItem = addPolygon(QPolygon(),color);
    ellipse = addEllipse(previousPoint.x(),previousPoint.y(),0,0,color);
    dashellipse = addEllipse(previousPoint.x(),previousPoint.y(),0,0,color);
    lineItem = addLine(0,0,0,0,color);
    dashlineItem = addLine(0,0,0,0,color);

}

void customScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    previousPoint = event->scenePos();

    if(Phigure::rectangle == phigure){

        QPolygonF polygon;
        polygon.append(QPointF(event->scenePos()));
        polygon.append(QPointF(event->scenePos().x() + 10,event->scenePos().y()));
        polygon.append(QPointF(event->scenePos().x() + 10,event->scenePos().y() - 10));
        polygon.append(QPointF(event->scenePos().x(),event->scenePos().y() - 10));

        polyItem = addPolygon(polygon,color);

    }

    if(Phigure::dash_rectangle == phigure){

            QPolygonF polygon;
            polygon.append(QPointF(event->scenePos()));
            polygon.append(QPointF(event->scenePos().x() + 10,event->scenePos().y()));
            polygon.append(QPointF(event->scenePos().x() + 10,event->scenePos().y() - 10));
            polygon.append(QPointF(event->scenePos().x(),event->scenePos().y() - 10));

            dashpolyItem = addPolygon(polygon,color);

    }

    if(Phigure::circle == phigure){

       ellipse = addEllipse(previousPoint.x(),previousPoint.y(),0,0,color);


    }

    if(Phigure::dash_circle == phigure){

           dashellipse = addEllipse(previousPoint.x(),previousPoint.y(),0,0,color);


    }

    if(Phigure::line == phigure){

       lineItem = addLine(0,0,0,0,color);


    }

    if(Phigure::dash_line == phigure){

       dashlineItem = addLine(0,0,0,0,color);


    }
}

void customScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos() - previousPoint;
    float magnitude;
    QPolygonF polygon;

    switch (phigure) {

    case Phigure::line:

        removeItem(lineItem);

        lineItem = addLine(previousPoint.x(),previousPoint.y(),event->scenePos().x(),event->scenePos().y(),QPen(color,size,Qt::SolidLine,Qt::RoundCap));


        break;

    case Phigure::dash_line:

        removeItem(dashlineItem);

        dashlineItem = addLine(previousPoint.x(),previousPoint.y(),event->scenePos().x(),event->scenePos().y(),QPen(color,size,Qt::DashLine,Qt::RoundCap));


        break;

    case Phigure::circle:

        removeItem(ellipse);

        magnitude = sqrt(point.x() * point.x() + point.y() * point.y());

        ellipse = addEllipse(previousPoint.x() - magnitude/2,previousPoint.y() - magnitude/2,magnitude,magnitude,QPen(color,size,Qt::SolidLine,Qt::RoundCap));

        break;

    case Phigure::dash_circle:

        removeItem(dashellipse);

        magnitude = sqrt(point.x() * point.x() + point.y() * point.y());

        dashellipse = addEllipse(previousPoint.x() - magnitude/2,previousPoint.y() - magnitude/2,magnitude,magnitude,QPen(color,size,Qt::DashLine,Qt::RoundCap));

        break;

    case Phigure::pen:

        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(color,size,Qt::SolidLine,Qt::RoundCap));
        previousPoint = event->scenePos();

        break;
    case Phigure::rectangle:

        removeItem(polyItem);

        polygon.append(QPointF(previousPoint));
        polygon.append(QPointF(previousPoint.x() + point.x(),previousPoint.y()));
        polygon.append(QPointF(previousPoint.x() + point.x(),previousPoint.y() + point.y()));
        polygon.append(QPointF(previousPoint.x(),previousPoint.y() + point.y()));



        polyItem = addPolygon(polygon,QPen(color,size,Qt::SolidLine));

        break;

    case Phigure::dash_rectangle:

        removeItem(dashpolyItem);



        polygon.append(QPointF(previousPoint));
        polygon.append(QPointF(previousPoint.x() + point.x(),previousPoint.y()));
        polygon.append(QPointF(previousPoint.x() + point.x(),previousPoint.y() + point.y()));
        polygon.append(QPointF(previousPoint.x(),previousPoint.y() + point.y()));



        dashpolyItem = addPolygon(polygon,QPen(color,size,Qt::DashLine));

        break;
    case Phigure::cleaner:


        if(CleanerVariant){

            addLine(previousPoint.x(),
                    previousPoint.y(),
                    event->scenePos().x(),
                    event->scenePos().y(),
                    QPen(this->backgroundBrush().color(),size * 3,Qt::SolidLine,Qt::RoundCap));
            previousPoint = event->scenePos();

        }
        else
        {

        cleanerLine = addLine(previousPoint.x(),
                 previousPoint.y(),
                 event->scenePos().x(),
                 event->scenePos().y(),
                 QPen(QColor(255,255,255,255),size * 2,Qt::SolidLine,Qt::RoundCap));

       QList<QGraphicsItem*> colliding = cleanerLine->collidingItems();

       for(qsizetype i = 0; i < colliding.size();i++){

           removeItem(colliding.at(i));

       }

       removeItem(cleanerLine);


       previousPoint = event->scenePos();

       break;

        }
    }



}

