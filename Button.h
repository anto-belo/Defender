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
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
signals:
    void clicked();
private:
    QString picPath;
    QString picHoveredPath;
};

#endif // BUTTON_H
