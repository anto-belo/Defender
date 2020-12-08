#ifndef BULLET_H
#define BULLET_H

#include "Definitions.h"

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsPixmapItem {
       Q_OBJECT
public:
    Bullet(TowerType towerType, QGraphicsItem * parent = NULL);
public slots:
    void move();
private:
    int speed;
    const int BULLET_DXDY = 20;
};

#endif // BULLET_H
