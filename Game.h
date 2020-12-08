#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>


class Game : public QGraphicsView {
public:
    Game(QWidget * parent = NULL);

    void mousePressEvent(QMouseEvent * event);

    void start();

    QGraphicsScene * scene;
//    TileMap * map; TODO
    int health;
    int wave;
    int money;
};

#endif // GAME_H
