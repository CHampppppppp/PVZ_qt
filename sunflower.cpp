#include "sunflower.h"
#include "button.h"

Sunflower::Sunflower()
{
    hp=100;
    state=1;
    time=500;
    counter=0;
    atk=0;
    setMovie(":/resources/sf.gif");
}

void Sunflower::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(hp<=0)
    {delete this;
        return;}
    if(state&&++counter>=time)
    {
        counter=0;
        Sun* sun=new Sun(50);
        if(rand()%2==1)
            sun->setX(x()+rand()%40);
        else sun->setX(x()-rand()%40);
        sun->setY(y()-20);
        sun->setZValue(4);
        sun->to_y=y()+20;
        scene()->addItem(sun);
        return;
    }
    else if(!state&&++counter>=time)
    {
        if(counter<10)
        {
            Sun* sun=new Sun(50);
            qDebug()<<"counter:"<<counter;
            if(rand()%2==1)
                sun->setX(x()+rand()%40);
            else sun->setX(x()-rand()%40);
            sun->setY(y()-20);
            sun->setZValue(4);
            sun->to_y=y()+20;
            scene()->addItem(sun);
            return;
        }
        else {
            state=1;
            counter=0;
            time=500;
        }
    }
}

void Sunflower::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            time=1;
            counter=0;
            button->counter=0;
            button->state=0;
            button->power_activate=false;

            state=0;
        }
    }
}
