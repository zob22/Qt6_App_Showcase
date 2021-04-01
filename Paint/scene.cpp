#include "scene.h"
#include "math.h"


Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{

}

Scene::~Scene(){

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch(mode){
    case 0:
    addEllipse(event->scenePos().x() - 5, event->scenePos().y() - 5, 10, 10, QPen(Qt::NoPen), QBrush(Qt::black));
    previousPoint = event->scenePos();
        break;

    case 1:
    addEllipse(event->scenePos().x() - 5, event->scenePos().y() - 5, 10, 10, QPen(Qt::NoPen), QBrush(Qt::black));
    previousPoint = event->scenePos();
        break;

    case 2:
        previousPoint = event->scenePos();
        break;
    case 3:
        QGraphicsScene::mousePressEvent( event );
        break;
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    switch (mode) {
    case 0:
   addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(), QPen(Qt::black,5,Qt::SolidLine,Qt::RoundCap));
   previousPoint = event->scenePos();
        break;
    case 3:
        QGraphicsScene::mouseMoveEvent( event );
        break;
    }
}
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    switch (mode) {
    case 1:
    addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(), QPen(Qt::black,10,Qt::SolidLine,Qt::RoundCap));
        break;

    case 2:{
        double d = 2*sqrt(pow(event->scenePos().x()-previousPoint.x(),2)+pow(event->scenePos().y()-previousPoint.y(),2));
        lastItem = addEllipse(previousPoint.x() - d/2 , previousPoint.y()- d/2  , d, d, QPen(Qt::red), QBrush(Qt::NoBrush));
        lastItem->setFlag(QGraphicsItem::ItemIsMovable);
        break;
    }
    case 3:
         QGraphicsScene::mouseReleaseEvent( event );
        break;

    }
}
