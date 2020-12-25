#ifndef TILE_H
#define TILE_H

#include "Button.h"
#include "Tower.h"

class Tile : public Button {
public:
    Tile(int xPos, int yPos, int tileType, QGraphicsItem * parent = NULL);
    void setTilePic(int type);

    Tower * getOccupier();
    void setOccupier(Tower * occupier);

    bool isFocused();
    void setFocused(bool focus);

    void setPicPathsOf(int type);
    void setDefaultPicPaths();
    QString getTileNameOf(int type);
    void setPicPaths(QString path) override;
    QString getPicPathChosen();

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;
private:
    Tower * occupiedBy;
    bool focused;
    bool towerTile;
    QString picPathChosen;
};

#endif // TILE_H
