#ifndef BUTTON_H
#define BUTTON_H

#include "other.h"
#include "zombie.h"//一键冷冻zombie
#include "plants.h"//给植物打鸡血
#include <QCursor>
#define FREEZE 1
#define POWER 2
#define SHOVEL 3

class Button:public other
{
public:
    Button(int t);
    void advance(int phase) override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect() const override;
    static bool shovel_activate;
    static bool power_activate;
    int counter;
    int state;//0->cooling 1->activating
protected:
    int cool_time;
    int type;

};

#endif // BUTTON_H
