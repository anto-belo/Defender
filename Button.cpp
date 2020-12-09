#include "Button.h"

Button::Button(QString path, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    picPath = path;
    picHoveredPath = path.insert(path.size() - 4, "Hovered");
    setPixmap(QPixmap(path));
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setPixmap(QPixmap(picHoveredPath));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setPixmap(QPixmap(picPath));
}
