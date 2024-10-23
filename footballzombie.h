#ifndef FOOTBALLZOMBIE_H
#define FOOTBALLZOMBIE_H

#include "zombie.h"
#include "plants.h"
#include "button.h"

class Footballzombie:public Zombie
{
public:
    Footballzombie();
    void advance(int phase) override;
    void snowfree()override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // FOOTBALLZOMBIE_H
