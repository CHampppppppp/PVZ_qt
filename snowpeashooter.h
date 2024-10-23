#ifndef SNOWPEASHOOTER_H
#define SNOWPEASHOOTER_H


#include "plants.h"
#include "zombie.h"
#include "pea.h"
#include "button.h"

class snowpeashooter:public Plants
{
public:
    snowpeashooter();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other,Qt::ItemSelectionMode mode) const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // SNOWPEASHOOTER_H
