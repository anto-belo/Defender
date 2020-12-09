#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"

#include <QPixmap>
#include <QRectF>
#include <QLineF>
#include <QTimer>
#include <QList>

extern Game * game;

Tower::Tower(TowerType towerType, QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent) {
    /* Tower picture setup */
    QString path = ":/img/img/";
    switch (towerType) {
        case TowerType::SimpleTower:
            path += "SimpleTower.png";
        break;
        case TowerType::AirTower:
            path += "AirTower.png";
        break;
    }
    setPixmap(QPixmap(path));
    setTransformOriginPoint(TOWER_CENTER);
    setPos(QPointF(1000, 500));//AUTO

    /* Creating an ellipse range and moving it onto the tower */
    int rangeRadius = 400;//AUTO (range property)
    range = new QGraphicsEllipseItem(QRectF(0, 0, 2 * rangeRadius, 2 * rangeRadius), this);
    QPointF rangeCenter(rangeRadius, rangeRadius);
    rangeCenter = mapToScene(rangeCenter);

    QLineF vec(rangeCenter, TOWER_CENTER);
    range->setPos(range->x() + vec.dx(), range->y() + vec.dy());

    /* Setting the tower to attack the "aim" QPointF */
    QTimer * attack_timer = new QTimer(this);
    connect(attack_timer, SIGNAL(timeout()), this, SLOT(setAim()));
    attack_timer->start(300);//AUTO (fireRate property)
}

void Tower::attack() {
    Bullet * b = new Bullet(TowerType::SimpleTower);
    b->setPos(TOWER_CENTER_X - BULLET_WIDTH / 2, TOWER_CENTER_Y - BULLET_HEIGHT / 2);
    b->setTransformOriginPoint(BULLET_WIDTH / 2, BULLET_HEIGHT / 2);
    int angle = -1 * QLineF(TOWER_CENTER, aim).angle();
    b->setRotation(angle);
    game->scene->addItem(b);
    setRotation(angle);
}

void Tower::setAim() {
    QList<QGraphicsItem *> collidingItems = range->collidingItems();
    hasAim = false;
    double minDist = 400;
    QPointF attackPoint = QPointF(0, 0);
    for (size_t i = 0, n = collidingItems.size(); i < n; i++) {
        Enemy * enemy = dynamic_cast<Enemy *>(collidingItems[i]);
        if (enemy) {
            double curDist = QLineF(pos(), enemy->pos()).length();
            if (curDist < minDist) {
                minDist = curDist;
                attackPoint = QPointF(enemy->pos());
            }
            hasAim = true;
        }
    }
    if (hasAim) {
        aim = attackPoint;
        attack();
    }
}
