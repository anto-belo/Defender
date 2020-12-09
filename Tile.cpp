#include "Tile.h"

Tile::Tile(int xPos, int yPos, int tileType, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    QString path = ":/img/img/";
    switch (tileType) {
        case TileType::Trail:
            path += "TrailTile.png";
        break;
        case TileType::TowerTile:
            path += "TowerTile.png";
        break;
        case TileType::Enter:
            path += "EnterTile.png";
        break;
        case TileType::Exit:
            path += "ExitTile.png";
        break;
    }
    setPixmap(QPixmap(path));
    setTransformOriginPoint(TOWER_CENTER);
    setPos(xPos, yPos);
    occupiedBy = nullptr;
}

Tower *Tile::getOccupier() {
    return occupiedBy;
}

void Tile::setOccupier(Tower *occupier) {
    occupiedBy = occupier;
}
