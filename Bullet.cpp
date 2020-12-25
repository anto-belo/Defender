#include "Bullet.h"

#include "Definitions.h"
#include "Enemy.h"

#include <QTimer>
#include <qmath.h>

Bullet::Bullet(int towerType, int dmg, QGraphicsItem * parent) :
                                QObject(), QGraphicsPixmapItem(parent) {
    QString path = "";
    switch (towerType) {
        case TowerType::SimpleTower:
            path = ":/img/img/SimpleTowerBullet.png";
        break;
        case TowerType::AirTower:
            path = ":/img/img/AirTowerBullet.png";
        break;
        case TowerType::UniTower:
            path = ":/img/img/UniTowerBullet.png";
    }
    setPixmap(QPixmap(path));
    this->dmg = dmg;

    QTimer * move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(BULLET_SPEED);
}

void Bullet::move() {
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (int i = 0; i < collidingItems.size(); i++) {
        Enemy * enemy = dynamic_cast<Enemy *>(collidingItems[i]);
        if (enemy) {
            enemy->setHealth(enemy->getHealth() - dmg);
            delete this;
            return;
        }
    }

    double angle = rotation();
    double dy = BULLET_DXDY * qSin(qDegreesToRadians(angle));
    double dx = BULLET_DXDY * qCos(qDegreesToRadians(angle));
    setPos(x() + dx, y() + dy);
    if (x() < MAP_START_X - BULLET_PAST_THE_TARGET_DIST
     || x() > MAP_START_X + MAP_TILE_WIDTH * TILE_SIZE + BULLET_PAST_THE_TARGET_DIST
     || y() < MAP_START_Y - BULLET_PAST_THE_TARGET_DIST
     || y() > MAP_START_Y + MAP_TILE_HEIGHT * TILE_SIZE + BULLET_PAST_THE_TARGET_DIST) {
        delete this;
    }
}
