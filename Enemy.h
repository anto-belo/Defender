#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(int enemyType, QGraphicsItem * parent = NULL);

    void setHealth(int health);
    int getHealth();

    int getType();

    void changeDirection(QPointF to);
public slots:
    void move();
private:
    int type;
    int health;
    int cost;
    QGraphicsRectItem * healthLine;
    QList<QPointF> pathList;

    QPointF curDest;
    int curPointIndex;
};

#endif // ENEMY_H
