#ifndef TOWER_H
#define TOWER_H

#include "Definitions.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QPointF>

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tower(TowerType towerType, QGraphicsItem * parent = NULL);

    int getLevel();
    void setLevel(int level);
    int getCost();
    void setCost(int cost);
    int getDmg();
    void setDmg(int dmg);
    double getFireRate();
    void setFireRate(double fireRate);
    double getTurnRate();
    void setTurnRate(double turnRate);
    void attack();
    //double getRange(); TODO
    //void setRange(double range); TODO

    //bool turn(int angle);
public slots:
    void setAim();
private:
    int level;
    int cost;
    int dmg;
    double fireRate;
    double turnRate;
    bool hasAim;
    QGraphicsEllipseItem * range;
    QPointF aim;
};

#endif // TOWER_H
