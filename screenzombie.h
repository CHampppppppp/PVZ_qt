#ifndef SCREENZOMBIE_H
#define SCREENZOMBIE_H
#include "zombie.h"
#include "plants.h"
#include "button.h"

class screenzombie:public Zombie
{
public:
    screenzombie();
    void advance(int phase) override;
    void snowfree() override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // SCREENZOMBIE_H
