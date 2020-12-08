#include "Enemy.h"

#include <QLineF>
#include <QTimer>
#include <qmath.h>

Enemy::Enemy(EnemyType enemyType, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    QString path = ":/img/img/";
    switch (enemyType) {
        case EnemyType::SimpleEnemy:
            path += "SimpleEnemy.png";
        break;
        case EnemyType::AirEnemy:
            path += "AirEnemy.png";
        break;
        case EnemyType::BossEnemy:
            path += "BossEnemy.png";
        break;
    }
    setPixmap(QPixmap(path));

    pathList << QPoint(200, 300) << QPointF(1800, 300);//AUTO (pathList property)
    curPointIndex = 0;
    curDest = pathList[0];
    changeDirection(curDest);

    QTimer * move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(100);
}

void Enemy::changeDirection(QPointF to) {
    QLineF path(pos(), to);
    setRotation(-1 * path.angle());
}

void Enemy::move() {
    QLineF r(pos(), curDest);
    if (r.length() < 10) {
        curPointIndex++;
        if (curPointIndex >= pathList.size()) {
            return;
        } else {
            curDest = pathList[curPointIndex];
            changeDirection(curDest);
        }
    }
    double angle = rotation();
    double dy = ENEMY_DXDY * qSin(qDegreesToRadians(angle));
    double dx = ENEMY_DXDY * qCos(qDegreesToRadians(angle));
    setPos(x() + dx, y() + dy);
}
