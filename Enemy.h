#ifndef ENEMY_H
#define ENEMY_H

#include "Definitions.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QPointF>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(EnemyType enemyType, QGraphicsItem * parent = NULL);
    void changeDirection(QPointF to);
public slots:
    void move();
private:
    QList<QPointF> pathList;
    QPointF curDest;
    int curPointIndex;
    const int ENEMY_DXDY = 5;
};

#endif // ENEMY_H
