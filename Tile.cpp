#include "Tile.h"

#include "Game.h"

extern Game * game;

Tile::Tile(int xPos, int yPos, int tileType, QGraphicsItem *parent) : Button(parent) {
    occupiedBy = nullptr;
    towerTile = false;
    focused = false;
    picPathChosen = "";

    setTilePic(tileType);
    setTransformOriginPoint(TOWER_CENTER);
    setPos(xPos, yPos);

    connect(this, SIGNAL(clicked()), game, SLOT(showTileInfo()));
}

void Tile::setTilePic(int type) {
    switch (type) {
        case TileType::Trail:
            picPath = ":/img/img/TrailTile.png";
        break;
        case TileType::TowerTile:
            picPath = ":/img/img/TowerTile.png";
            towerTile = true;
        break;
        case TileType::Enter:
            picPath = ":/img/img/EnterTile.png";
        break;
        case TileType::Exit:
            picPath = ":/img/img/ExitTile.png";
    }
    QString temp = picPath;
    picPathHovered = temp.insert(picPath.size() - 4, "Hovered");
    temp = picPath;
    picPathChosen = temp.insert(picPath.size() - 4, "Chosen");
    setPixmap(QPixmap(picPath));
}

Tower * Tile::getOccupier() {
    return occupiedBy;
}

void Tile::setOccupier(Tower * occupier) {
    occupiedBy = occupier;
}

bool Tile::isFocused() {
    return focused;
}

void Tile::setFocused(bool focus) {
    focused = focus;
}

void Tile::setPicPathsOf(int type) {
    setPicPaths(":/img/img/" + getTileNameOf(type) + ".png");
}

void Tile::setDefaultPicPaths() {
    setPicPaths(":/img/img/TowerTile.png");
}

QString Tile::getTileNameOf(int type) {
    QString res = "";
    switch (type) {
        case TowerType::SimpleTower:
            res = "SimpleTile";
            break;
        case TowerType::AirTower:
            res = "AirTile";
            break;
        case TowerType::UniTower:
            res = "UniTile";
    }
    return res;
}

void Tile::setPicPaths(QString path) {
    picPath = path;
    QString temp = path;
    picPathHovered = temp.insert(picPath.size() - 4, "Hovered");
    temp = path;
    picPathChosen = temp.insert(picPath.size() - 4, "Chosen");
}

QString Tile::getPicPathChosen() {
    return picPathChosen;

}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if (!towerTile) return;
    if (game->chosenTile != nullptr) {
        game->chosenTile->focused = false;
        game->chosenTile->setPixmap(game->chosenTile->picPath);
        if (game->chosenTile->getOccupier() != nullptr)
            game->chosenTile->getOccupier()->hideRange();
    }
    game->chosenTile = this;
    focused = true;
    setPixmap(picPathChosen);
    if (game->chosenTile->getOccupier() != nullptr)
        game->chosenTile->getOccupier()->showRange();
    emit clicked();
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    if (towerTile && !focused)
        setPixmap(QPixmap(picPathHovered));
}

void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    if (towerTile && !focused)
        setPixmap(QPixmap(picPath));
}
