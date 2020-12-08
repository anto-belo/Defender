#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define TOWER_CENTER QPointF(x() + 50, y() + 50)
#define TOWER_CENTER_X x() + 50
#define TOWER_CENTER_Y y() + 50

const int TOWER_RADIUS = 50;
const int BULLET_WIDTH = 56;
const int BULLET_HEIGHT = 20;
enum TowerType {SimpleTower, AirTower};
enum EnemyType {SimpleEnemy, AirEnemy, BossEnemy};


#endif // DEFINITIONS_H
