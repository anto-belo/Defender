#include "Game.h"

Game::Game(QWidget * parent) : QGraphicsView() {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920, 1080);
    showFullScreen();

    scene = new QGraphicsScene(0, 0, 1920, 1080, this);
    setScene(scene);
}

void Game::showSplashScreen() {
    setBackgroundBrush(QBrush(QImage(":/img/img/SplashScreen.jpg")));
    QTimer::singleShot(1000, this, SLOT(showMainMenu()));
}

void Game::showMainMenu() {
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/img/img/MainMenu.jpg")));

    Button * playButton = new Button(":/img/img/PlayButton.png");
    int buttonX = this->width() / 2 - QPixmap(":/img/img/PlayButton.png").width() / 2;
    int buttonY = 565;
    playButton->setPos(buttonX, buttonY);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button * quitButton = new Button(":/img/img/QuitButton.png");
    buttonY = 805;
    quitButton->setPos(buttonX, buttonY);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::start() {
    initPlayerCharacs();
    drawGUI();
    initWaveMechanism();
    initTowerShop();
    initUpgradeCards();
    initMap(MAP_START_X, MAP_START_Y, MAP_TILE_WIDTH, MAP_TILE_HEIGHT, MAP_GEN_CORDS);
    startCountdown();
}

void Game::initPlayerCharacs() {
    health = INIT_HEALTH;
    wave = INIT_WAVE;
    money = INIT_MONEY;
}

void Game::drawGUI() {
    scene->clear();
    setBackgroundBrush(QBrush(QColor(53, 53, 53), Qt::SolidPattern));
    drawPanel();
    drawPlayerCharacs();
}

void Game::drawPanel() {
    QGraphicsRectItem * panel = new QGraphicsRectItem(0, 2 * height() / 3, 1920, height() / 3);
    QBrush brush;
    brush.setColor(QColor(27, 27, 27));
    brush.setStyle(Qt::SolidPattern);
    panel->setBrush(brush);
    scene->addItem(panel);
}

void Game::drawPlayerCharacs() {
    QGraphicsPixmapItem * healthIco = new QGraphicsPixmapItem(QPixmap(":/img/img/heart.png"));
    healthIco->setPos(30, 30);
    scene->addItem(healthIco);

    QGraphicsPixmapItem * waveIco = new QGraphicsPixmapItem(QPixmap(":/img/img/wave.png"));
    waveIco->setPos(50, 170);
    scene->addItem(waveIco);

    QGraphicsPixmapItem * moneyIco = new QGraphicsPixmapItem(QPixmap(":/img/img/money.png"));
    moneyIco->setPos(55, 275);
    scene->addItem(moneyIco);

    healthText = new QGraphicsTextItem(QString::number(health));
    healthText->setDefaultTextColor(Qt::white);
    healthText->setFont(QFont("Humnst777 Blk BT", 30));
    healthText->setPos(170, 50);
    scene->addItem(healthText);

    waveText = new QGraphicsTextItem(QString::number(wave));
    waveText->setDefaultTextColor(Qt::white);
    waveText->setFont(QFont("Humnst777 Blk BT", 30));
    waveText->setPos(170, 165);
    scene->addItem(waveText);

    moneyText = new QGraphicsTextItem(QString::number(money));
    moneyText->setDefaultTextColor(Qt::white);
    moneyText->setFont(QFont("Humnst777 Blk BT", 30));
    moneyText->setPos(170, 280);
    scene->addItem(moneyText);
}

void Game::initWaveMechanism() {
    enemyTimer = new QTimer(this);
    waveTimer = new QTimer(this);

    levelTime = START_GAME_TIMER_LENGTH;

    timeLeftCircle = new QGraphicsPixmapItem(QPixmap(":/img/img/TimerB.png"));
    timeLeftCircle->setPos(10, 730);
    scene->addItem(timeLeftCircle);

    timeLeftText = new QGraphicsTextItem();
    timeLeftText->setDefaultTextColor(Qt::white);
    timeLeftText->setFont(QFont("Humnst777 Blk BT", 50));
    timeLeftText->setPos(127, 843);
    scene->addItem(timeLeftText);

    nextWaveButton = new ButtonCard(":/img/img/NextWaveButton.png", 9);
    nextWaveButton->setPos(330, 1000);
    scene->addItem(nextWaveButton);
    connect(nextWaveButton, SIGNAL(clicked()), this, SLOT(resetTimer()));
}

void Game::resetTimer() {
    timeLeft = 1;
}

void Game::showTileInfo() {
    hideTowerCharacs();
    hideUpgradeCards();
    hideTowerShop();
    if (chosenTile->getOccupier() == nullptr) {
        showTowerShop();
    } else {
        showTowerCharacs();
        showUpgradeCards();
    }
}

void Game::initTowerShop() {
    size_t size = sizeof(ALL_TOWERS) / sizeof(ALL_TOWERS[0]);
    for (size_t i = 0; i < size; i++) {
        ButtonCard * card = new ButtonCard(":/img/img/" + ALL_TOWERS[i] + "Ico.png", i);
        card->setPos(700 + 210 * i, 750);
        connect(card, SIGNAL(clicked()), this, SLOT(setTower()));
        scene->addItem(card);
        shopItems.append(card);
        card->hide();
    }
}

void Game::showTowerShop() {
    for (int i = 0; i < shopItems.size(); i++) {
        shopItems.at(i)->show();
    }
}

void Game::hideTowerShop() {
    for (int i = 0; i < shopItems.size(); i++) {
        shopItems.at(i)->hide();
    }
}

void Game::setTower() {
    Tower * tower = new Tower(chosenValue);
    int dxdy = (TILE_SIZE - 3 - 2 * TOWER_RADIUS) / 2;
    tower->setPos(chosenTile->x() + dxdy, chosenTile->y() + dxdy);
    setMoney(money - SHOP_PRICE[chosenValue]);
    scene->addItem(tower);
    chosenTile->setOccupier(tower);
    chosenTile->setPicPathsOf(chosenValue);
    chosenTile->setPixmap(chosenTile->getPicPathChosen());
    hideTowerShop();
    showTowerCharacs();
    showUpgradeCards();
}

void Game::initUpgradeCards() {
    size_t size = sizeof(ALL_TOWER_UPGRADES) / sizeof(ALL_TOWER_UPGRADES[0]);
    for (size_t i = 0; i < size; i++) {
        ButtonCard * upgradeCard = new ButtonCard(":/img/img/Upgrade" + ALL_TOWER_UPGRADES[i] + ".png", i);
        upgradeCard->setPos(1550, 730 + 110 * i);
        connect(upgradeCard, SIGNAL(clicked()), this, SLOT(upgradeParam()));
        scene->addItem(upgradeCard);
        upgradeCards.append(upgradeCard);
        upgradeCard->hide();

        QGraphicsTextItem * upgradeCost = new QGraphicsTextItem();
        upgradeCost->setPos(1805, 795 + 110 * i);
        upgradeCost->setFont(QFont("Humnst777 Blk BT", 10));
        upgradeCost->setDefaultTextColor(Qt::white);
        scene->addItem(upgradeCost);
        paramUpdCosts.append(upgradeCost);
        upgradeCost->hide();

    }
    upgradeCards.last()->setPos(1220, 945);
    paramUpdCosts.last()->setPos(1480, 1015);
}

void Game::showTowerCharacs() {
    QString towerCharacsIcoPath = chosenTile->getOccupier()->getPicPath();
    towerCharacsIcoPath = towerCharacsIcoPath.insert(towerCharacsIcoPath.size() - 4, "CharacsIco");
    QGraphicsPixmapItem * towerCharacsIco = new QGraphicsPixmapItem(towerCharacsIcoPath);
    towerCharacsIco->setPos(700, 750);
    scene->addItem(towerCharacsIco);
    towerCharacs.append(towerCharacsIco);

    int type = chosenTile->getOccupier()->getType();
    QGraphicsTextItem * towerName = new QGraphicsTextItem(ALL_TOWERS_NAMES[type]);
    towerName->setDefaultTextColor(Qt::white);
    towerName->setFont(QFont("Humnst777 Blk BT", 50));
    towerName->setPos(900, 730);
    scene->addItem(towerName);
    towerCharacs.append(towerName);

    QString curDmg = QString::number(chosenTile->getOccupier()->getParam(Param::Dmg));
    QGraphicsTextItem * dmgLabel = new QGraphicsTextItem("Damage: " + curDmg);
    dmgLabel->setDefaultTextColor(Qt::white);
    dmgLabel->setFont(QFont("Humnst777 Blk BT", 15));
    dmgLabel->setPos(900, 830);
    scene->addItem(dmgLabel);
    towerCharacs.append(dmgLabel);

    QString curFireRate = QString::number(chosenTile->getOccupier()->getParam(Param::FireRate));
    QGraphicsTextItem * fireRateLabel = new QGraphicsTextItem("Fire Rate: " + curFireRate);
    fireRateLabel->setDefaultTextColor(Qt::white);
    fireRateLabel->setFont(QFont("Humnst777 Blk BT", 15));
    fireRateLabel->setPos(900, 860);
    scene->addItem(fireRateLabel);
    towerCharacs.append(fireRateLabel);

    QString curRange = QString::number(chosenTile->getOccupier()->getParam(Param::RangeRadius) / 100.0);
    QGraphicsTextItem * rangeRadiusLabel = new QGraphicsTextItem("Range Radius: " + curRange);
    rangeRadiusLabel->setDefaultTextColor(Qt::white);
    rangeRadiusLabel->setFont(QFont("Humnst777 Blk BT", 15));
    rangeRadiusLabel->setPos(900, 890);
    scene->addItem(rangeRadiusLabel);
    towerCharacs.append(rangeRadiusLabel);
}

void Game::hideTowerCharacs() {
    for (int i = 0; i < towerCharacs.size(); i++) {
        scene->removeItem(towerCharacs[i]);
        delete towerCharacs[i];
    }
    towerCharacs.clear();
}

void Game::showUpgradeCards() {
    Tower * thisTower = chosenTile->getOccupier();
    int curParamsPrices[] = {thisTower->getParamUpdCost(Param::Dmg),
                             thisTower->getParamUpdCost(Param::FireRate),
                             thisTower->getParamUpdCost(Param::RangeRadius),
                             thisTower->getCost()};
    for (int i = 0; i < upgradeCards.size(); i++) {
        paramUpdCosts[i]->setPlainText(QString::number(curParamsPrices[i]));
        paramUpdCosts[i]->show();
        upgradeCards[i]->show();
    }
    checkUpgradeAbility();
}

void Game::hideUpgradeCards() {
    for (int i = 0; i < upgradeCards.size(); i++) {
        upgradeCards[i]->hide();
        paramUpdCosts[i]->hide();
    }
}

void Game::upgradeParam() {
    Tower * thisTower = chosenTile->getOccupier();
    int curParam = thisTower->getParam(chosenValue);
    int curParamUpdCost = thisTower->getParamUpdCost(chosenValue);
    int towerType = thisTower->getType();
    int cost = thisTower->getCost();
    if (chosenValue == Param::Delete) {
        delete thisTower;
        chosenTile->setOccupier(nullptr);
        chosenTile->setDefaultPicPaths();
        chosenTile->setPixmap(chosenTile->getPicPathChosen());
        hideTowerCharacs();
        hideUpgradeCards();
        showTowerShop();
        setMoney(money + cost);
    } else {
        switch(chosenValue) {
            case Param::Dmg:
                thisTower->setParam(Param::Dmg, curParam + DDMG[towerType]);
                thisTower->setParamUpdCost(Param::Dmg, curParamUpdCost + DMG_DCOST[towerType]);
                break;
            case Param::FireRate:
                thisTower->setParam(Param::FireRate, curParam + DFIRE_RATE[towerType]);
                thisTower->setParamUpdCost(Param::FireRate, curParamUpdCost + FIRE_RATE_DCOST[towerType]);
                break;
            case Param::RangeRadius:
                thisTower->setParam(Param::RangeRadius, curParam + DRANGE_RADIUS[towerType]);
                thisTower->setParamUpdCost(Param::RangeRadius, curParamUpdCost + RANGE_RADIUS_DCOST[towerType]);
                thisTower->initRange();
        }
        thisTower->setCost(thisTower->getCost() + curParamUpdCost / 2);
        setMoney(money - curParamUpdCost);
        moneyText->setPlainText(QString::number(money));
        hideTowerCharacs();
        showTowerCharacs();
        showUpgradeCards();
    }
}

void Game::initMap(int xStart, int yStart, const int width, const int height, const int mapGenCoords[]) {
    chosenTile = nullptr;
    chosenValue = -1;

    int curX = xStart;
    int curY = yStart;
    for (int i = 0; i < width * height; i++) {
        curX = xStart + TILE_SIZE * (i % width);
        curY = yStart + TILE_SIZE * (i / width);
        Tile * tile = new Tile(curX, curY, mapGenCoords[i]);
        scene->addItem(tile);
    }
}

void Game::startCountdown() {
    timeLeft = levelTime;
    timeLeftText->setPlainText(QString::number(timeLeft));
    connect(waveTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    waveTimer->start(1000);
}

void Game::updateTime() {
    timeLeft--;
    if (timeLeft >= 0) {
        changeTimerColor(timeLeft);
        timeLeftText->setPlainText(QString::number(timeLeft));
        if (timeLeft > 9) {
            timeLeftText->setX(127);
        } else {
            timeLeftText->setX(155);
        }
        timeLeftText->show();
    } else {
        wave++;
        setWave(wave);
        if (wave % 3 == 0 && levelTime > END_GAME_TIMER_LENGTH) {
            levelTime -= TIMER_DLENGTH;
        }
        timeLeft = levelTime;
        createEnemies();//AUTO gener
    }
}

void Game::changeTimerColor(int curTime) {
    if (curTime == 0) {
        timeLeftCircle->setPixmap(QPixmap(":/img/img/TimerG.png"));
    } else if (curTime <= 3) {
        timeLeftCircle->setPixmap(QPixmap(":/img/img/TimerR.png"));
    } else {
        timeLeftCircle->setPixmap(QPixmap(":/img/img/TimerB.png"));
    }
}

void Game::createEnemies() {
    nextWaveButton->block();
    enemiesSpawned = 0;
    enemiesNeeded = SPAWN_GEN_QUANTITY[wave % 10];
    waveEnemyType = SPAWN_GEN_SEQUENCE[wave % 10];
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    enemyTimer->start(1000);
}

void Game::spawnEnemy() {
    Enemy * enemy = new Enemy(waveEnemyType);
    scene->addItem(enemy);
    enemiesSpawned++;
    if (enemiesSpawned >= enemiesNeeded) {
        enemyTimer->disconnect();
        nextWaveButton->unblock();
    }
}

void Game::setHealth(int health) {
    this->health = health;
    healthText->setPlainText(QString::number(health));
    if (health <= 0) {
        enemyTimer->disconnect();
        waveTimer->disconnect();
        QList<QGraphicsItem *> allItems = scene->items();
        for (int i = 0; i < allItems.size(); i++) {
            delete allItems[i];
        }
        showEndScreen();
    }
}

void Game::showEndScreen() {
    QGraphicsTextItem * gameOverText = new QGraphicsTextItem("Game Over");
    gameOverText->setFont(QFont("Humnst777 Blk BT", 100));
    gameOverText->setDefaultTextColor(Qt::white);
    gameOverText->setPos(470, 200);
    scene->addItem(gameOverText);

    QGraphicsTextItem * waveText = new QGraphicsTextItem("You've reached " + QString::number(wave) + " wave");
    waveText->setFont(QFont("Humnst777 Blk BT", 40));
    waveText->setDefaultTextColor(Qt::white);
    waveText->setPos(500, 450);
    scene->addItem(waveText);

    Button * endButton = new Button(":/img/img/MenuButton.png");
    int buttonX = this->width() / 2 - QPixmap(":/img/img/MenuButton.png").width() / 2;
    int buttonY = 600;
    endButton->setPos(buttonX, buttonY);
    connect(endButton, SIGNAL(clicked()), this, SLOT(showMainMenu()));
    scene->addItem(endButton);
}

void Game::setWave(int wave) {
    this->wave = wave;
    waveText->setPlainText(QString::number(wave));
}

void Game::setMoney(int money) {
    this->money = money;
    moneyText->setPlainText(QString::number(money));
    checkPurchaseAbility();
    checkUpgradeAbility();
}

void Game::checkPurchaseAbility() {
    size_t size = sizeof(SHOP_PRICE) / sizeof(SHOP_PRICE[0]);
    for (size_t i = 0; i < size; i++) {
        if (SHOP_PRICE[i] > money) {
            shopItems[i]->block();
        } else {
            shopItems[i]->unblock();
        }
    }
}

void Game::checkUpgradeAbility() {
    if (chosenTile != nullptr && chosenTile->getOccupier() != nullptr) {
        Tower * thisTower = chosenTile->getOccupier();
        int curParamsPrices[] = {thisTower->getParamUpdCost(Param::Dmg),
                                 thisTower->getParamUpdCost(Param::FireRate),
                                 thisTower->getParamUpdCost(Param::RangeRadius)};
        for (int i = 0; i < 3; i++) {
            if (curParamsPrices[i] > money) {
                upgradeCards[i]->block();
            } else {
                upgradeCards[i]->unblock();
            }
        }
    }
}
