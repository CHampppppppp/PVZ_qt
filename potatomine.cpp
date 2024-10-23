#include "potatomine.h"
#include "button.h"
#include "card.h"

Potatomine::Potatomine()
{
    hp=80;
    atk=300;
    state=1;//地里 state2->地上 state3->爆炸
    setMovie(":/resources/pttm1.gif");
    movie->setSpeed(50);
    counter=0;
    time=350;
}

void Potatomine::advance(int phase)
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
    if(state==1&&++counter>=time)
    {
        counter=0;
        state=2;
        setMovie(":/resources/pttm2.gif");
    }
    if(state==2)
    {  
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            bool iszombie;
            foreach(QGraphicsItem* item,items)
            {
                iszombie=false;
                Zombie* zombie=qgraphicsitem_cast<Zombie*>(item);
                if(zombie)
                {
                    iszombie=true;
                    zombie->hp-=atk;
                }
            }
            if(iszombie)
            {
                state=3;
                setMovie(":/resources/pttm3.gif");
            }
        }
    }
    if(state==3&&movie->currentFrameNumber()==movie->frameCount()-1) delete this;
}

bool Potatomine::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode)const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type&&qAbs(other->x()-x())<=30&&other->y()==y();
}


void Potatomine::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            QGraphicsItem* item2=scene()->itemAt(QPoint(533,45),transform());
            Card* card=qgraphicsitem_cast<Card*>(item2);
            card->counter=Card::cool[card->name];
            button->counter=0;
            button->power_activate=false;

            button->state=0;
            counter=time;
        }
    }
}

QRectF Potatomine::boundingRect() const
{
    return state==3 ? QRectF(-60, -70, 120, 140) : Plants::boundingRect();
}
