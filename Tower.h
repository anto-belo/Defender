#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tower(int towerType, QGraphicsItem * parent = NULL);

    int getCost();
    void setCost(int cost);

    int getParam(int paramType);
    void setParam(int paramType, int value);

    int getParamUpdCost(int paramType);
    void setParamUpdCost(int paramType, int value);

    int getType();
    QString getPicPath();
    void initRange();
    void showRange();
    void hideRange();

    void attack();
public slots:
    void setAim();
private:
    int cost;

    int dmg;
    int fireRate;
    int rangeRadius;

    int dmgUpdCost;
    int fireRateUpdCost;
    int rangeRadiusUpdCost;

    int type;
    QString picPath;
    QGraphicsEllipseItem * range;

    QTimer * attack_timer;
    bool hasAim;
    QPointF aim;
};

#endif // TOWER_H
