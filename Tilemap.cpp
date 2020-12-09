#include "Tilemap.h"

extern Game * game;

TileMap::TileMap(int xStart, int yStart, const int width, const int height, const int mapGenCoords[]) {
    int curX = xStart;
    int curY = yStart;
    for (int i = 0; i < width * height; i++) {
//        if (i % width == 0) {
//            curX = xStart;
//            curY += TILE_SIZE;
//        }
        curX = xStart + TILE_SIZE * (i % width);
        curY = yStart + TILE_SIZE * (i / width);
        Tile * tile = new Tile(curX, curY, mapGenCoords[i]);
        map.append(tile);
        game->scene->addItem(tile);
    }
}
