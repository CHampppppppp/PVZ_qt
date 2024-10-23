#include "snowpeashooter.h"
#include "button.h"

snowpeashooter::snowpeashooter()
{
    hp=100;
    state=1;
    time=100;
    counter=0;
    atk=17;
    setMovie(":/resources/snowpea.gif");
    movie->setSpeed(50);
}

void snowpeashooter::advance(int phase)
{
    static int num=0;
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!phase) return;
    update();
    if(hp<=0)
        delete this;
    else if(++counter>=time)
    {
        counter=0;
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            int s;
            if(state)
                s=SNOW;
            else {
                s=2*SNOW;
                num++;
                if(num>3){
                    num=0;
                    state=1;
                }
            }
            Pea* pea=new Pea(atk,s);
            qDebug()<<"pea_snow:"<<s;
            pea->setX(x()+32);
            pea->setY(y());
            scene()->addItem(pea);
            return;
        }
    }
}


bool snowpeashooter::collidesWithItem(const QGraphicsItem* other,Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type&&other->x()>=x()&&other->y()==y();
}


void snowpeashooter::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            qDebug()<<"power_snowpea";
            QGraphicsItem* item=scene()->itemAt(QPoint(918,60),transform());
            Button* button=qgraphicsitem_cast<Button*>(item);
            button->counter=0;
            button->state=0;
            button->power_activate=false;
            state=0;
        }
    }
}


