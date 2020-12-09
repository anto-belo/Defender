#ifndef TILE_H
#define TILE_H

#include "Tower.h"
#include "Definitions.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Tile : public QGraphicsPixmapItem {
public:
    Tile(int xPos, int yPos, int tileType, QGraphicsItem * parent = NULL);
    Tower * getOccupier();
    void setOccupier(Tower * occupier);
private:
    Tower * occupiedBy;
};

#endif // TILE_H
