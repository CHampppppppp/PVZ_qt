#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H


#include "plants.h"
#include "zombie.h"
#include "button.h"
#define GAP_Y 100
#define GAP_X 110

class Cherrybomb:public Plants
{
public:
    Cherrybomb();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect()const override;
};

#endif // CHERRYBOMB_H
