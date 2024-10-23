#ifndef POTATOMINE_H
#define POTATOMINE_H

#include "plants.h"
#include "zombie.h"
#include "button.h"

class Potatomine:public Plants
{
public:
    Potatomine();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode)const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect()const override;
};

#endif // POTATOMINE_H
