#ifndef CONEZOMBIE_H
#define CONEZOMBIE_H

#include "zombie.h"
#include "plants.h"
#include "button.h"

class Conezombie:public Zombie
{
public:
    Conezombie();
    void advance(int phase) override;
    void snowfree() override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CONEZOMBIE_H
