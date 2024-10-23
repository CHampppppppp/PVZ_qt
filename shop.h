#ifndef SHOP_H
#define SHOP_H

#include "sun.h"
#include "other.h"
#include "peashooter.h"
#include "snowpeashooter.h"
#include "sunflower.h"
#include "wallnut.h"
#include "cherrybomb.h"
#include "potatomine.h"
#include "repeater.h"

class Shop:public other
{
public:
    Shop();
    int sun_val;
    QRectF boundingRect() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget) override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    //void mousePressEvent(QGraphicsSceneMouseEvent* event) override;点击实现图层先后顺序置换
private:
    QImage image;
    int counter;
    int sun_generate_time;
    int pre_sunval;
};

#endif // SHOP_H
