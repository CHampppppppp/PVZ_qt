#include "peashooter.h"
#include "button.h"


peashooter::peashooter()
{
    hp=100;
    state=1;
    time=100;
    counter=0;
    atk=20;
    setMovie(":/resources/ps.gif");
    movie->setSpeed(50);
}

void peashooter::advance(int phase)
{
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!phase) return;
    update();
    if(hp<=0)
    {
        delete this;
    }
    else if(++counter%time==0)
    {
        if(counter>80){
            counter=0;
            time=100;
        }
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())// 当前行有僵尸
        {
            Pea* pea=new Pea(atk,NO_SNOW);
            pea->setX(x()+32);
            pea->setY(y());
            scene()->addItem(pea);//scene()返回该item当前所在的scene指针
            return;
        }
    }
}

bool peashooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->y()==y()&&other->type()==Zombie::Type&&other->x()>x();
}


void peashooter::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            time=5;//射击冷却时间
            counter=0;//射击计时器
            button->counter=0;
            button->state=0;
            state=0;
        }
    }
}






