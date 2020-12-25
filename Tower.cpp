#include "Tower.h"

#include "Definitions.h"
#include "Game.h"

#include <QTimer>

extern Game * game;

Tower::Tower(int towerType, QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent) {
    switch (towerType) {
        case TowerType::SimpleTower:
            picPath = ":/img/img/SimpleTower.png";
        break;
        case TowerType::AirTower:
            picPath = ":/img/img/AirTower.png";
        break;
        case TowerType::UniTower:
            picPath = ":/img/img/UniTower.png";
    }

    cost = INIT_COST[towerType];

    dmg = INIT_DMG[towerType];
    fireRate = INIT_FIRE_RATE[towerType];
    rangeRadius = INIT_RANGE_RADIUS[towerType];

    dmgUpdCost = INIT_DMG_COST[towerType];
    fireRateUpdCost = INIT_FIRE_RATE_COST[towerType];
    rangeRadiusUpdCost = INIT_RANGE_RADIUS_COST[towerType];

    type = towerType;
    setPixmap(QPixmap(picPath));
    setTransformOriginPoint(TOWER_CENTER);
    range = nullptr;
    initRange();

    attack_timer = new QTimer(this);
    connect(attack_timer, SIGNAL(timeout()), this, SLOT(setAim()));
    attack_timer->start(fireRate);
}

int Tower::getCost() {
    return cost;
}

void Tower::setCost(int cost) {
    this->cost = cost;
}

int Tower::getParam(int paramType) {
    int res = -1;
    switch(paramType) {
        case Param::Dmg:
            res = dmg;
            break;
        case Param::FireRate:
            res = fireRate;
            break;
        case Param::RangeRadius:
            res = rangeRadius;
    }
    return res;
}

void Tower::setParam(int paramType, int value) {
    switch(paramType) {
        case Param::Dmg:
            dmg = value;
            break;
        case Param::FireRate:
            fireRate = value;
            attack_timer->start(fireRate);
            break;
        case Param::RangeRadius:
            rangeRadius = value;
    }
}

int Tower::getParamUpdCost(int paramType) {
    int res = -1;
    switch(paramType) {
        case Param::Dmg:
            res = dmgUpdCost;
            break;
        case Param::FireRate:
            res = fireRateUpdCost;
            break;
        case Param::RangeRadius:
            res = rangeRadiusUpdCost;
    }
    return res;
}

void Tower::setParamUpdCost(int paramType, int value) {
    switch(paramType) {
        case Param::Dmg:
            dmgUpdCost = value;
            break;
        case Param::FireRate:
            fireRateUpdCost = value;
            break;
        case Param::RangeRadius:
            rangeRadiusUpdCost = value;
    }
}

int Tower::getType() {
    return type;
}

QString Tower::getPicPath() {
    return picPath;
}

void Tower::initRange() {
    if (range != nullptr) {
        delete range;
    }
    int angle = this->rotation();
    this->setRotation(0);
    range = new QGraphicsEllipseItem(QRectF(0, 0, 2 * rangeRadius, 2 * rangeRadius), this);
    range->setBrush(QBrush(Qt::cyan, Qt::Dense7Pattern));
    QPointF rangeCenter(rangeRadius, rangeRadius);
    rangeCenter = mapToScene(rangeCenter);
    QLineF vec(rangeCenter, TOWER_CENTER);
    range->setPos(range->x() + vec.dx(), range->y() + vec.dy());
    this->setRotation(angle);
}

void Tower::showRange() {
    range->show();
}

void Tower::hideRange() {
    range->hide();
}

void Tower::attack() {
    Bullet * b = new Bullet(type, dmg);
    b->setPos(TOWER_CENTER_X - BULLET_WIDTH / 2, TOWER_CENTER_Y - BULLET_HEIGHT / 2);
    b->setTransformOriginPoint(BULLET_WIDTH / 2, BULLET_HEIGHT / 2);
    int angle = -1 * QLineF(TOWER_CENTER, aim).angle();
    setRotation(angle);
    b->setRotation(angle);
    game->scene->addItem(b);
}

void Tower::setAim() {
    QList<QGraphicsItem *> collidingItems = range->collidingItems();
    hasAim = false;
    double minDist = 1000;
    QPointF attackPoint = QPointF(0, 0);
    for (size_t i = 0, n = collidingItems.size(); i < n; i++) {
        Enemy * enemy = dynamic_cast<Enemy *>(collidingItems[i]);
        if (enemy && ATTACK_ABILITY[getType()][enemy->getType()] == 1) {
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
