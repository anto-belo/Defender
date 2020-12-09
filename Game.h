#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "Tilemap.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Definitions.h"
#include "Button.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QTimer>

class TileMap;

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget * parent = NULL);
    void showSplashScreen();
    //void mousePressEvent(QMouseEvent * event);

    QGraphicsScene * scene;
    TileMap * map;
    int health;
    int wave;
    int money;

public slots:
    void showMainMenu();
    void chooseLevelMenu();
    void start();
};

#endif // GAME_H
