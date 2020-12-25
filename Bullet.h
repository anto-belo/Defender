#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(int towerType, int dmg, QGraphicsItem * parent = NULL);
public slots:
    void move();
private:
    int dmg;
    int speed;
};

#endif // BULLET_H
