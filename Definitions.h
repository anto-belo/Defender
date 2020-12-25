#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QString>

/**** Player's characteristics initialization ****/
const int INIT_HEALTH = 100;
const int INIT_WAVE = 0;
const int INIT_MONEY = 200;

/**** Wave timer time parameters ****/
const int START_GAME_TIMER_LENGTH = 30;
const int END_GAME_TIMER_LENGTH = 15;
const double TIMER_DLENGTH = 1;

/**** Tower ****/
enum TowerType {SimpleTower, AirTower, UniTower};
enum Param {Dmg, FireRate, RangeRadius, Delete};

const int TOWER_RADIUS = 20;
#define TOWER_CENTER QPointF(x() + TOWER_RADIUS, y() + TOWER_RADIUS)
#define TOWER_CENTER_X x() + TOWER_RADIUS
#define TOWER_CENTER_Y y() + TOWER_RADIUS

const QString ALL_TOWERS[] = {"SimpleTower", "AirTower", "UniTower"};
const QString ALL_TOWERS_NAMES[] = {"Simple Tower", "Air Tower", "Uni Tower"};
const QString ALL_TOWER_UPGRADES[] = {"Dmg", "FireRate", "RangeRadius", "Delete"};

/**** Tower game characteristics ****/
const int SHOP_PRICE[] = {48, 42, 70};
const int INIT_COST[] = {24, 21, 35};

const int INIT_DMG[] = {10, 15, 9};
const int DDMG[] = {5, 5, 4};
const int INIT_DMG_COST[] = {60, 50, 70};
const int DMG_DCOST[] = {20, 18, 22};

const int INIT_FIRE_RATE[] = {800, 800, 900};
const int DFIRE_RATE[] = {-50, -30, -15};
const int INIT_FIRE_RATE_COST[] = {24, 21, 27};
const int FIRE_RATE_DCOST[] = {12, 10, 15};

const int INIT_RANGE_RADIUS[] = {150, 200, 120};
const int DRANGE_RADIUS[] = {10, 15, 8};
const int INIT_RANGE_RADIUS_COST[] = {25, 30, 45};
const int RANGE_RADIUS_DCOST[] = {22, 25, 30};

const int ATTACK_ABILITY[3][4] = {{1, 1, 0, 1},
                                  {0, 0, 1, 0},
                                  {1, 1, 1, 1}};

/**** Bullet ****/
const int BULLET_WIDTH = 22;
const int BULLET_HEIGHT = 8;

const int BULLET_DXDY = 20;
const int BULLET_SPEED = 15;
const int BULLET_PAST_THE_TARGET_DIST = 50;

/**** Enemy ****/
enum EnemyType {SimpleEnemy, StrongEnemy, AirEnemy, BossEnemy};

#define ENEMY_CENTER QPointF(x() + 20, y() + 20)
#define PATH_LIST QList<QPointF> pathList;\
                                 pathList << QPointF(TILE_SIZE + 15, 15)\
                                          << QPointF(TILE_SIZE + 15, TILE_SIZE * 5 + 15)\
                                          << QPointF(TILE_SIZE * 5 + 15, TILE_SIZE * 5 + 15)\
                                          << QPointF(TILE_SIZE * 5 + 15, TILE_SIZE + 15)\
                                          << QPointF(TILE_SIZE * 8 + 15, TILE_SIZE + 15)\
                                          << QPointF(TILE_SIZE * 8 + 15, TILE_SIZE * 5 + 15);
const int HEALTH_LINE_LENGTH = 40;
const int HEALTH_LINE_HEIGHT = 5;
const int HEALTH_LINE_X_POS = 0;
const int HEALTH_LINE_Y_POS = -10;

/**** Enemy game characteristics ****/
const int ENEMY_COUNT = 4;
const int ENEMY_DMG[] = {1, 3, 2, 10};
const int ENEMY_HEALTH[] = {11, 50, 40, 500};
const int ENEMY_WAVE_DHEALTH[] = {9, 12, 15, 150};
const int ENEMY_COST[] = {9, 12, 13, 20};
const int ENEMY_WAVE_DCOST[] = {1, 2, 2, 5};
const int ENEMY_SPEED[] = {50, 70, 40, 100};
const int ENEMY_DXDY = 3;
const int COEFF_UPDATE_ALL = 5;
const int COEFF_UPDATE_BOSS = 10;
const int COEFF_UPDATE_COST = 10;

const int SPAWN_GEN_SEQUENCE[] = {0, 0, 1, 0, 2, 0, 0, 1, 2, 3};
const int SPAWN_GEN_QUANTITY[] = {15, 15, 5, 15, 20, 20, 25, 7, 10, 1};

/**** Tile ****/
enum TileType {Trail = 1, TowerTile, Enter, Exit, SimpleTile, AirTile};
const int TILE_SIZE = 70;

/**** Map generator ****/
const int MAP_START_X = 610;
const int MAP_START_Y = 100;
const int MAP_TILE_WIDTH = 10;
const int MAP_TILE_HEIGHT = 7;
const int MAP_GEN_CORDS[70] = { 0, 3, 0, 0, 0, 0, 0, 2, 2, 0,
                                0, 1, 2, 0, 0, 1, 1, 1, 1, 2,
                                0, 1, 2, 0, 0, 1, 2, 2, 1, 2,
                                2, 1, 2, 0, 0, 1, 2, 2, 1, 0,
                                2, 1, 2, 2, 2, 1, 2, 0, 1, 0,
                                2, 1, 1, 1, 1, 1, 2, 0, 4, 0,
                                0, 2, 2, 2, 2, 2, 0, 0, 0, 0 };

#endif // DEFINITIONS_H
