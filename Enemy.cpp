#include "Enemy.h"

#include "Definitions.h"
#include "Game.h"

#include <QTimer>
#include <qmath.h>

extern Game * game;

Enemy::Enemy(int enemyType, QGraphicsItem * parent) {
    QString path = "";
    switch (enemyType) {
        case EnemyType::SimpleEnemy:
            path = ":/img/img/SimpleEnemy.png";
        break;
        case EnemyType::StrongEnemy:
            path = ":/img/img/StrongEnemy.png";
        break;
        case EnemyType::AirEnemy:
            path = ":/img/img/AirEnemy.png";
        break;
        case EnemyType::BossEnemy:
            path = ":/img/img/BossEnemy.png";
        break;
    }
    setPixmap(QPixmap(path));
    setTransformOriginPoint(ENEMY_CENTER);

    type = enemyType;
    cost = ENEMY_COST[type] + ENEMY_WAVE_DCOST[type] * (game->wave / COEFF_UPDATE_COST);

    PATH_LIST
    this->pathList = pathList;

    setPos(pathList[0].x() + MAP_START_X, pathList[0].y() + MAP_START_Y);
    curPointIndex = 1;
    curDest = QPointF(pathList[1].x() + MAP_START_X, pathList[1].y() + MAP_START_Y);
    changeDirection(curDest);

    QTimer * move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(ENEMY_SPEED[type]);

    healthLine = nullptr;
    int coeff = (type != EnemyType::BossEnemy) ? COEFF_UPDATE_ALL : COEFF_UPDATE_BOSS;
    setHealth(ENEMY_HEALTH[type] + ENEMY_WAVE_DHEALTH[type] * (game->wave / coeff));
}

void Enemy::setHealth(int health) {
    if (health <= 0) {
        game->setMoney(game->money + cost);
        delete this;
        return;
    }

    QGraphicsRectItem * healthLineBg = new QGraphicsRectItem(HEALTH_LINE_X_POS,
                                                             HEALTH_LINE_Y_POS,
                                                             HEALTH_LINE_LENGTH,
                                                             HEALTH_LINE_HEIGHT,
                                                             this);
    healthLineBg->setBrush(QBrush(Qt::red));

    this->health = health;

    if (healthLine != nullptr) {
        delete healthLine;
    }
    int coeff = (type != EnemyType::BossEnemy) ? COEFF_UPDATE_ALL : COEFF_UPDATE_BOSS;
    int healthLineLength = ((double)health / (ENEMY_HEALTH[type] + ENEMY_WAVE_DHEALTH[type] * (game->wave / coeff))) * 40;
    healthLine = new QGraphicsRectItem(HEALTH_LINE_X_POS,
                                       HEALTH_LINE_Y_POS,
                                       healthLineLength,
                                       HEALTH_LINE_HEIGHT,
                                       this);
    healthLine->setBrush(QBrush(Qt::green));
}

int Enemy::getHealth() {
    return health;
}

int Enemy::getType() {
    return type;
}

void Enemy::changeDirection(QPointF to) {
    QLineF path(pos(), to);
    setRotation(-1 * path.angle());
}

void Enemy::move() {
    QLineF r(pos(), curDest);
    if (r.length() < 5) {
        curPointIndex++;
        if (curPointIndex >= pathList.size()) {
            game->setHealth(game->health - ENEMY_DMG[type]);
            delete this;
            return;
        } else {
            curDest = QPointF(pathList[curPointIndex].x() + MAP_START_X,
                              pathList[curPointIndex].y() + MAP_START_Y);
            changeDirection(curDest);
        }
    }
    double angle = rotation();
    double dy = ENEMY_DXDY * qSin(qDegreesToRadians(angle));
    double dx = ENEMY_DXDY * qCos(qDegreesToRadians(angle));
    setPos(x() + dx, y() + dy);
}
