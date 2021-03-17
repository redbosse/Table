#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QColor>

class customScene : public QGraphicsScene
{
    Q_OBJECT

   public:
       explicit customScene(QObject *parent = nullptr);
       ~customScene();
    qreal size = 10;
    QColor color;


   private:
       QPointF     previousPoint;

   private:

       void mousePressEvent(QGraphicsSceneMouseEvent * event);
       void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif
