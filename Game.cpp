#include "Game.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Definitions.h"

Game::Game(QWidget * parent) : QGraphicsView() {
    /* View (window) setup */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920, 1080);

    /* Scene setup */
    scene = new QGraphicsScene(0, 0, 1920, 1080, this);
    setScene(scene);
}

void Game::start() {
    // Testcode TODO remove
    Tower * tower = new Tower(TowerType::AirTower);
    scene->addItem(tower);

    Enemy * enemy = new Enemy(EnemyType::BossEnemy);
    scene->addItem(enemy);
}

void Game::mousePressEvent(QMouseEvent * event) {
    Bullet * b = new Bullet(TowerType::SimpleTower);
    b->setPos(event->pos());
    scene->addItem(b);
}

//TODO tower turning to aim before attacking
