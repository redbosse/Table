#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QColor>
#include <QGraphicsPolygonItem>

#include <vector>

enum Phigure{
    pen = 0,
    rectangle,
    dash_rectangle,
    line,
    dash_line,
    circle,
    dash_circle,
    cleaner

};

class customScene : public QGraphicsScene
{
    Q_OBJECT

   public:
       explicit customScene(QObject *parent = nullptr);
       ~customScene();
    void initialize();

    qreal size = 10;
    QColor color;
    bool CleanerVariant = false;

    int phigure = 0;



   private:
       QPointF     previousPoint;
       QGraphicsPolygonItem* polyItem;
       QGraphicsEllipseItem* ellipse;
       QGraphicsLineItem* lineItem;

       QGraphicsPolygonItem* dashpolyItem;
       QGraphicsEllipseItem* dashellipse;
       QGraphicsLineItem* dashlineItem;
       QGraphicsLineItem* cleanerLine;


   private:

       void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
       void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif
