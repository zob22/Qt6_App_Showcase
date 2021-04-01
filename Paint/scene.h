#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>


class Scene : public QGraphicsScene
{

    Q_OBJECT

public:
    int mode;
    explicit Scene(QObject *parent = 0);
    ~Scene();

private:
    QPointF     previousPoint;
    QGraphicsEllipseItem* lastItem;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


#endif // SCENE_H
