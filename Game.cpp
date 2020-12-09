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
    connect(playButton, SIGNAL(clicked()), this, SLOT(chooseLevelMenu()));
    scene->addItem(playButton);

    Button * quitButton = new Button(":/img/img/QuitButton.png");
    buttonY = 805;
    quitButton->setPos(buttonX, buttonY);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::chooseLevelMenu() {
    scene->clear();
}

void Game::start() {
    // Testcode TODO remove
//    Tower * tower = new Tower(TowerType::AirTower);
//    scene->addItem(tower);

//    Enemy * enemy = new Enemy(EnemyType::BossEnemy);
//    scene->addItem(enemy);
    map = new TileMap(100, 100, L1_MAP_WIDTH, L1_MAP_HEIGHT, L1_MAP_GEN_CORDS);
}



//void Game::mousePressEvent(QMouseEvent * event) {
//    Bullet * b = new Bullet(TowerType::SimpleTower);
//    b->setPos(event->pos());
//    scene->addItem(b);
//}

//TODO tower turning to aim before attacking
