#ifndef SUNFLOWER_H
#define SUNFLOWER_H


#include "plants.h"
#include "sun.h"
#include "button.h"

class Sunflower:public Plants
{
public:
    Sunflower();
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // SUNFLOWER_H
