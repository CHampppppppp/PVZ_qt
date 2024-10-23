#ifndef WALLNUT_H
#define WALLNUT_H

#include "plants.h"
#include "button.h"

class Wallnut:public Plants
{
public:
    Wallnut();
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // WALLNUT_H
