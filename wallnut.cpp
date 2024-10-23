#include "wallnut.h"
#include "button.h"

Wallnut::Wallnut()
{
    hp=450;
    atk=0;
    state=1;
    setMovie(":/resources/wallnut1.gif");
}

void Wallnut::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!state&&hp<=700) hp+=0.8;
    if(hp<=250&&state==1)
    {
        state=2;
        setMovie(":/resources/wallnut2.gif");
    }
    else if(hp<=100&&state==2)
    {
        state=3;
        setMovie(":/resources/wallnut3.gif");
    }else if(hp<=0&&state==3)
    {
        delete this;
        return;
    }
}

void Wallnut::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(Button::shovel_activate)
        {
            QGraphicsItem* item=scene()->itemAt(QPoint(798,40),transform());
            Button* button=qgraphicsitem_cast<Button*>(item);
            button->shovel_activate=false;
            button->counter=0;
            button->state=0;
            delete this;
        }
        else if(Button::power_activate)
        {
            QGraphicsItem* item=scene()->itemAt(QPoint(918,60),transform());
            Button* button=qgraphicsitem_cast<Button*>(item);
            button->counter=0;
            button->state=0;
            button->power_activate=false;

            state=0;
        }
    }
}
