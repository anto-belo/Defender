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
    scene->clear();
    QBrush brush;
    brush.setColor(QColor(53, 53, 53));
    brush.setStyle(Qt::SolidPattern);
    setBackgroundBrush(brush);

    drawGUI();
    initWaveTimer();
    startCountdown(20);
    map = new TileMap(610, 100, L1_MAP_WIDTH, L1_MAP_HEIGHT, L1_MAP_GEN_CORDS);
}

void Game::drawGUI() {
    drawPanel();
    drawPlayerCharacs();
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

    health = 100;
    healthText = new QGraphicsTextItem(QString::number(health));
    healthText->setDefaultTextColor(Qt::white);
    healthText->setFont(QFont("Humnst777 Blk BT", 30));
    healthText->setPos(170, 50);
    scene->addItem(healthText);

    wave = 0;
    waveText = new QGraphicsTextItem(QString::number(wave));
    waveText->setDefaultTextColor(Qt::white);
    waveText->setFont(QFont("Humnst777 Blk BT", 30));
    waveText->setPos(170, 165);
    scene->addItem(waveText);

    money = 200;
    moneyText = new QGraphicsTextItem(QString::number(money));
    moneyText->setDefaultTextColor(Qt::white);
    moneyText->setFont(QFont("Humnst777 Blk BT", 30));
    moneyText->setPos(170, 280);
    scene->addItem(moneyText);
}

void Game::startCountdown(int seconds) {
    timeLeft = seconds;
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
        timeLeft = 11;//AUTO change by level
        wave++;
        waveText->setPlainText(QString::number(wave));
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

void Game::initWaveTimer() {
    waveTimer = new QTimer(this);

    timeLeftCircle = new QGraphicsPixmapItem(QPixmap(":/img/img/TimerB.png"));
    timeLeftCircle->setPos(10, 730);
    scene->addItem(timeLeftCircle);

    timeLeftText = new QGraphicsTextItem();
    timeLeftText->setDefaultTextColor(Qt::white);
    timeLeftText->setFont(QFont("Humnst777 Blk BT", 50));
    timeLeftText->setPos(127, 843);
    scene->addItem(timeLeftText);

//    Button * nextWaveButton = new Button(":/img/img/NextWaveButton.png");
//    nextWaveButton->setPos(92, 845);
//    scene->addItem(nextWaveButton);
}

void Game::drawPanel() {
    QGraphicsRectItem * panel = new QGraphicsRectItem(0, 2 * height() / 3, 1920, height() / 3);
    QBrush brush;
    brush.setColor(QColor(27, 27, 27));
    brush.setStyle(Qt::SolidPattern);
    panel->setBrush(brush);
    scene->addItem(panel);
}



//void Game::mousePressEvent(QMouseEvent * event) {
//    Bullet * b = new Bullet(TowerType::SimpleTower);
//    b->setPos(event->pos());
//    scene->addItem(b);
//}

//TODO tower turning to aim before attacking
