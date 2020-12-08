#include "Bullet.h"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>

Bullet::Bullet(TowerType towerType, QGraphicsItem * parent) :
                                QObject(), QGraphicsPixmapItem(parent) {
    QString path = ":/img/img/";
    switch (towerType) {
        case TowerType::SimpleTower:
            path += "SimpleTowerBullet.png";
        break;
        case TowerType::AirTower:
            path += "AirTowerBullet.png";
        break;
    }
    setPixmap(QPixmap(path));

    QTimer * move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(15);//AUTO (speed property)
}

void Bullet::move() {
    double angle = rotation();
    double dy = BULLET_DXDY * qSin(qDegreesToRadians(angle));
    double dx = BULLET_DXDY * qCos(qDegreesToRadians(angle));
    setPos(x() + dx, y() + dy);
}
