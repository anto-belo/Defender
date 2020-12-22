#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Button : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Button(QString path, QGraphicsItem * parent = NULL);
    Button(QGraphicsItem * parent = NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void setPicPaths(QString picPath);
    QString getPicPath();
    QString getPicPathHovered();
signals:
    void clicked();
private:
    QString picPath;
    QString picPathHovered;
};

#endif // BUTTON_H
