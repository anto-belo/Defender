#include "Buttoncard.h"

#include "Game.h"

extern Game * game;

ButtonCard::ButtonCard(QString path, int value, QGraphicsItem *parent) : Button(path, parent) {
    picPathBlocked = path.insert(picPath.size() - 4, "Blocked");
    blocked = false;
    this->value = value;
}

ButtonCard::ButtonCard(QGraphicsItem * parent) : Button(parent) {
    blocked = false;
}

void ButtonCard::setPicPaths(QString picPath) {
    this->picPath = picPath;
    picPathHovered = picPath.insert(picPath.size() - 4, "Hovered");
    picPathBlocked = picPath.insert(picPath.size() - 4, "Blocked");
}

void ButtonCard::block() {
    blocked = true;
    setPixmap(QPixmap(picPathBlocked));
}

void ButtonCard::unblock() {
    blocked = false;
    setPixmap(QPixmap(picPath));
}

void ButtonCard::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if (!blocked) {
        game->chosenValue = value;
        emit clicked();
    }
}

void ButtonCard::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    if (!blocked)
        setPixmap(QPixmap(picPathHovered));
}

void ButtonCard::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    if (!blocked)
        setPixmap(QPixmap(picPath));
}
