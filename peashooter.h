#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plants.h"
#include "zombie.h"
#include "pea.h"
#include "button.h"



class peashooter:public Plants
{
public:
    peashooter();//用父类指针来析构
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};


#endif // PEASHOOTER_H
