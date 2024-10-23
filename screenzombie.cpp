#include "screenzombie.h"
#include "button.h"

screenzombie::screenzombie()
{
    hp=250;
    speed=0.7;
    atk=0.3;
    state=WALK;
    slow=NO_SLOW;
    time=120;
    SetMovie(":/resources/szbw.gif");
}

void screenzombie::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(hp<=0)
    {
        if(Button::power_activate) setCursor(Qt::PointingHandCursor);
        else setCursor(Qt::ArrowCursor);
        if(state==ATTACK||state==WALK)
        {
            state=DEAD;
            Sethead(":/resources/zh.gif");
            SetMovie(":/resources/zd.gif");
            movie->setSpeed(50);
        }
        else if(state==BURN)
        {
            state=DEAD;
            speed=0;
            SetMovie(":/resources/burn.gif");
        }
        if(state==DEAD&&movie->frameCount()==movie->currentFrameNumber()+1)
        {
            delete this;//播放完gif顺带连head一起删除
        }
        return;
    }
    if(super)
    {
        movie->setSpeed(250);
        speed=2.5;
        atk=0.8;
    }
    QList<QGraphicsItem*> items=collidingItems();
    if(!items.isEmpty())//有碰撞
    {
        Plants *plant= qgraphicsitem_cast<Plants *>(items[0]);//安全起见
        if(plant)
        {
            plant->hp-=atk;
            if(state!=ATTACK)
            {
                if(hp>100)
                SetMovie(":/resources/szba.gif");
                else if(hp>0)
                    SetMovie(":/resources/za.gif");
                state=ATTACK;
            }
            return;
        }
    }

    if(state==ATTACK)//吃完后继续walk
    {
        state=WALK;
        if(hp>100)
        SetMovie(":/resources/szbw.gif");
        else if(hp<=100)
            SetMovie(":/resources/zw1.gif");
    }

    if(slow)
    {
        if(++counter>time)
        {
            snowfree();
            return;
        }
        if(slow==1)
        {
            movie->setSpeed(50);
            speed=0.35;
        }
        else if(slow==2)
        {
            movie->setSpeed(0);
            speed=0;
        }
    }

    if(x()<100) {
        delete this;
        return;
    }
    setX(x()-speed);
}

void screenzombie::snowfree()
{
        slow=NO_SLOW;
        speed=0.7;
        movie->setSpeed(100);
        return;
}


void screenzombie::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos(918,60);
    QGraphicsItem* item=scene()->itemAt(pos,QTransform());
    Button* button=qgraphicsitem_cast<Button*>(item);
    if(button)
    {
        if(event->button()==Qt::LeftButton&&button->power_activate)
        {
            setCursor(Qt::PointingHandCursor);
            button->power_activate=false;
            button->counter=0;
            button->state=0;
            snowfree();
            super=true;
            qDebug()<<"powerscreenzombie";
        }
    }
}
