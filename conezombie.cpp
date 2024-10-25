#include "conezombie.h"
#include "button.h"

Conezombie::Conezombie()
{
    hp=350;
    atk=0.5;
    state=WALK;
    speed=0.7;
    slow=NO_SLOW;
    time=120;
    //QString filePath = "C:\\Users\\champ\\Documents\\pvzfresh\\zw1.gif";
    //qDebug() << "File path:" << filePath;
    //if (QFile::exists(filePath)) {
    //qDebug() << "File exists!";
    //SetMovie(filePath); // 如果文件存在，则设置动画
    //} else {
    //qDebug() << "File does not exist!";
    // 可以设置一个备用动画或处理文件不存在的情况
    //}
    SetMovie(":/resources/czbw.gif");
}

void Conezombie::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(hp<=0)
    {
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
                SetMovie(":/resources/czba.gif");
                state=ATTACK;
            }
            return;
        }
    }

    if(state==ATTACK)//吃完后继续walk
    {
        state=WALK;
        SetMovie(":/resources/czbw.gif");
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

void Conezombie::snowfree()
{
        slow=NO_SLOW;
        speed=0.7;
        movie->setSpeed(100);
        return ;
}

void Conezombie::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            qDebug()<<"powerconezombie";
        }
    }
}
