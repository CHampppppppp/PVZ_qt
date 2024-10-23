#ifndef MAP_H
#define MAP_H


#include "card.h"
#include "other.h"
#include "plants.h"
#include "shop.h"

class Map:public other
{
public:
    Map(int t);
    void advance(int phase) override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect() const override;
protected:
    int state;
    int type;
};

#endif // MAP_H
