#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>

class Button : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Button(QString path, QGraphicsItem * parent = NULL);
    Button(QGraphicsItem * parent = NULL);

    virtual void setPicPaths(QString picPath);
    QString getPicPath();
    QString getPicPathHovered();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
signals:
    void clicked();
protected:
    QString picPath;
    QString picPathHovered;
};

#endif // BUTTON_H
