#ifndef REPEATER_H
#define REPEATER_H

#include "plants.h"
#include "pea.h"
#include "zombie.h"
#include "button.h"

class Repeater:public Plants
{
public:
    Repeater();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // REPEATER_H
