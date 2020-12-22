#include "Tile.h"

Tile::Tile(int xPos, int yPos, int tileType, QGraphicsItem *parent) : Button(parent) {
    QString path = ":/img/img/";
    towerTile = false;
    switch (tileType) {
        case TileType::Trail:
            path += "TrailTile.png";
        break;
        case TileType::TowerTile:
            path += "TowerTile.png";
            towerTile = true;
        break;
        case TileType::Enter:
            path += "EnterTile.png";
        break;
        case TileType::Exit:
            path += "ExitTile.png";
        break;
    }
    setPicPaths(path);
    setPixmap(QPixmap(path));
    setTransformOriginPoint(TOWER_CENTER);
    setPos(xPos, yPos);
    occupiedBy = nullptr;
}

Tower * Tile::getOccupier() {
    return occupiedBy;
}

void Tile::setOccupier(Tower *occupier) {
    occupiedBy = occupier;
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    if (towerTile) {
        setPixmap(QPixmap(getPicPathHovered()));
    }
}

void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    if (towerTile) {
        setPixmap(QPixmap(getPicPath()));
    }
}
