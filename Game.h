#ifndef GAME_H
#define GAME_H

#include "Definitions.h"
#include "Tile.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Button.h"
#include "Buttoncard.h"

#include <QGraphicsView>
#include <QTimer>

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget * parent = NULL);

    void setHealth(int health);
    void setWave(int wave);
    void setMoney(int money);

    QGraphicsScene * scene;

    Tile * chosenTile;
    int chosenValue;

    QList<ButtonCard *> shopItems;
    QList<QGraphicsItem *> towerCharacs;
    QList<ButtonCard *> upgradeCards;
    QList<QGraphicsTextItem *> paramUpdCosts;

    /* Wave timer */
    QTimer * waveTimer;
    QGraphicsTextItem * timeLeftText;
    QGraphicsPixmapItem * timeLeftCircle;
    int waveEnemyType;
    int timeLeft;
    int levelTime;
    ButtonCard * nextWaveButton;

    /* Enemy timer */
    QTimer * enemyTimer;
    int enemiesSpawned;
    int enemiesNeeded;

    /* Player characteristics */
    int health;
    int wave;
    int money;

    /* Player characteristic's texts */
    QGraphicsTextItem * healthText;
    QGraphicsTextItem * waveText;
    QGraphicsTextItem * moneyText;

public slots:
    void showMainMenu();
    void start();
    void resetTimer();
    void showTileInfo();
    void setTower();
    void upgradeParam();
    void updateTime();
    void spawnEnemy();

private:
    void showSplashScreen();

    void initPlayerCharacs();
    void drawGUI();
    void drawPanel();
    void drawPlayerCharacs();

    void initWaveMechanism();

    void initTowerShop();
    void showTowerShop();
    void hideTowerShop();

    void initUpgradeCards();
    void showTowerCharacs();
    void hideTowerCharacs();
    void showUpgradeCards();
    void hideUpgradeCards();

    void initMap(int xStart, int yStart, const int width, const int height, const int mapGenCoords[]);

    void startCountdown();
    void changeTimerColor(int curTime);
    void createEnemies();

    void showEndScreen();
    void checkPurchaseAbility();
    void checkUpgradeAbility();

};

#endif // GAME_H
