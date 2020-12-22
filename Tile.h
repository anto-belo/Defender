#ifndef TILE_H
#define TILE_H

#include "Button.h"
#include "Tower.h"
#include "Definitions.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Tile : public Button {
public:
    Tile(int xPos, int yPos, int tileType, QGraphicsItem * parent = NULL);
    Tower * getOccupier();
    void setOccupier(Tower * occupier);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;
private:
    Tower * occupiedBy;
    bool towerTile;
};

#endif // TILE_H
