#ifndef BUCKETZOMBIE_H
#define BUCKETZOMBIE_H
#include "zombie.h"
#include "plants.h"
#include "button.h"

class Bucketzombie:public Zombie
{
public:
    Bucketzombie();
    void advance(int phase) override;
    void snowfree() override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // BUCKETZOMBIE_H
