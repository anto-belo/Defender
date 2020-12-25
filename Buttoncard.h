#ifndef BUTTONCARD_H
#define BUTTONCARD_H

#include "Button.h"

class ButtonCard : public Button {
public:
    ButtonCard(QString path, int value, QGraphicsItem * parent = NULL);
    ButtonCard(QGraphicsItem * parent = NULL);

    void setPicPaths(QString picPath) override;

    void block();
    void unblock();

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;
private:
    bool blocked;
    int value;
    QString picPathBlocked;
};

#endif // BUTTONCARD_H
