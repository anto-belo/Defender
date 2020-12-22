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
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QString>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include <QFont>

class TileMap;

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget * parent = NULL);
    void showSplashScreen();
    //void mousePressEvent(QMouseEvent * event);

    QGraphicsScene * scene;
    TileMap * map;

    /* Wave timer */
    QTimer * waveTimer;
    QGraphicsTextItem * timeLeftText;
    QGraphicsPixmapItem * timeLeftCircle;
    int timeLeft;

    /* Player characteristics */
    QGraphicsTextItem * healthText;
    QGraphicsTextItem * waveText;
    QGraphicsTextItem * moneyText;
    int health;
    int wave;
    int money;
public slots:
    void showMainMenu();
    void start();

    void drawPlayerCharacs();
    void updateTime();
    void initWaveTimer();

private:
    void startCountdown(int seconds);
    void changeTimerColor(int curTime);
    void startLevel();
    void drawPanel();
        void drawGUI();
};

#endif // GAME_H
