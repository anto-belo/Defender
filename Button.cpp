#include "Button.h"

Button::Button(QString path, QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent) {
    picPath = path;
    QString temp = path;
    picPathHovered = temp.insert(path.size() - 4, "Hovered");
    setPixmap(QPixmap(picPath));
    setAcceptHoverEvents(true);
}

Button::Button(QGraphicsItem * parent) {
    setAcceptHoverEvents(true);
}

void Button::setPicPaths(QString picPath) {
    this->picPath = picPath;
    picPathHovered = picPath.insert(picPath.size() - 4, "Hovered");
}

QString Button::getPicPath() {
    return picPath;
}

QString Button::getPicPathHovered() {
    return picPathHovered;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    setPixmap(QPixmap(picPathHovered));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    setPixmap(QPixmap(picPath));
}


