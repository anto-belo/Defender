#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tower.h"
#include "Tile.h"
#include "Definitions.h"

#include <QList>

class TileMap {
public:
    TileMap(int xStart, int yStart, const int width, const int height, const int mapGenCoords[]);
    QList<Tile*> getMap();
private:
    QList<Tile*> map;
};


#endif // TILEMAP_H
