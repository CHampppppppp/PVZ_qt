#include "repeater.h"
#include "button.h"

Repeater::Repeater()
{
    hp=150;
    state=1;
    time=100;
    counter=0;
    atk=20;
    setMovie(":/resources/rp.gif");
    movie->setSpeed(50);
}

void Repeater::advance(int phase)
{
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!phase) return;
    update();
    if(hp<=0)
    {
        delete this;
        return;
    }
    if(state==0)
    {
        if(++counter>=time)
        {
            if(counter>=75)
            {
                counter=0;
                time=100;
                state=1;
                return;
            }
            time=counter+5;
            QList<QGraphicsItem*> items=collidingItems();
            if(!items.isEmpty())
            {
                Pea* pea1=new Pea(atk,NO_SNOW);
                pea1->setX(x()+32);
                pea1->setY(y());
                scene()->addItem(pea1);
                return;
            }
        }
    }
    if(state==1&&++counter>=time)
    {
        counter=0;
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            Pea* pea1=new Pea(atk,NO_SNOW);
            pea1->setX(x()+32);
            pea1->setY(y());
            scene()->addItem(pea1);
            state=2;
            return;
        }
    }
    if(state==2&&++counter>=time/25)
    {
        counter=0;
        Pea* pea2=new Pea(atk,NO_SLOW);
        pea2->setX(x()+32);
        pea2->setY(y());
        scene()->addItem(pea2);
        state=1;
        return;
    }
}

bool Repeater::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->y()==y()&&other->type()==Zombie::Type&&other->x()>x();
}

void Repeater::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            time=5;
            counter=0;
        }
    }
}
