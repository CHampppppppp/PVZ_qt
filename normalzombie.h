#ifndef NORMALZOMBIE_H
#define NORMALZOMBIE_H
#include "zombie.h"
#include "plants.h"
#include "button.h"

class normalzombie:public Zombie
{
public:
    normalzombie();
    void advance(int phase) override;
    void snowfree() override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // NORMALZOMBIE_H

