#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define IMG_PATH ":/img/img/"

/* Tower */
enum TowerType {SimpleTower, AirTower};
const int TOWER_RADIUS = 20;
#define TOWER_CENTER QPointF(x() + 20, y() + 20)
#define TOWER_CENTER_X x() + 20
#define TOWER_CENTER_Y y() + 20

/* Bullet */
const int BULLET_WIDTH = 22;
const int BULLET_HEIGHT = 8;

/* Enemy*/
enum EnemyType {SimpleEnemy, AirEnemy, BossEnemy};

/* Tile */
enum TileType {Trail = 1, TowerTile, Enter, Exit};
const int TILE_SIZE = 70;

/* Level 1*/
const int L1_MAP_WIDTH = 10;
const int L1_MAP_HEIGHT = 7;
const int L1_MAP_GEN_CORDS[70] = { 0, 3, 0, 0, 0, 0, 0, 2, 2, 0,
                                   0, 1, 2, 0, 0, 1, 1, 1, 1, 2,
                                   0, 1, 2, 0, 0, 1, 2, 2, 1, 2,
                                   2, 1, 2, 0, 0, 1, 2, 2, 1, 0,
                                   2, 1, 2, 2, 2, 1, 2, 0, 1, 0,
                                   2, 1, 1, 1, 1, 1, 2, 0, 4, 0,
                                   0, 2, 2, 2, 2, 2, 0, 0, 0, 0 };

#endif // DEFINITIONS_H
