#include "Button.h"

Button::Button(QString path, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    picPath = path;
    picPathHovered = path.insert(path.size() - 4, "Hovered");
    setPixmap(QPixmap(picPath));
    setAcceptHoverEvents(true);
}

Button::Button(QGraphicsItem *parent) {
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setPixmap(QPixmap(picPathHovered));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setPixmap(QPixmap(picPath));
}

void Button::setPicPaths(QString picPath) {
    this->picPath = picPath;
    this->picPathHovered = picPath.insert(picPath.size() - 4, "Hovered");
}

QString Button::getPicPath() {
    return picPath;
}

QString Button::getPicPathHovered() {
    return picPathHovered;
}
