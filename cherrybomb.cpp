#include "cherrybomb.h"
#include "button.h"


Cherrybomb::Cherrybomb()
{
    hp=50;
    atk=400;
    state=1;//准备爆炸
    setMovie(":/resources/cb.gif");
    movie->setSpeed(50);
    counter=0;
    time=50;//爆炸前摇
}

void Cherrybomb::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(hp<=0){
        delete this;
    }
    else if(state==1&&movie->currentFrameNumber()==movie->frameCount()-1)
    {
        state=2;
        setMovie(":/resources/boom.gif");
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            int count=0;
            foreach(QGraphicsItem* item,items)
            {
                Zombie* zombie=qgraphicsitem_cast<Zombie*>(item);
                zombie->state=BURN;
                zombie->hp=0;
                count++;
                qDebug()<<"zombie"<<count<<" state:"<<zombie->state;
            }
        }
    }else if(state==2&&movie->currentFrameNumber()==movie->frameCount()-1) {
        qDebug()<<"bomb_deleted";
        delete this;
    }
}

bool Cherrybomb::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type&&qAbs(other->y()-y())<=GAP_Y&&((other->x()-x()>=0&&other->x()-x()<=GAP_X)||(other->x()-x()>=-1.5*GAP_X&&other->x()-x()<=0));
}


void Cherrybomb::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            srand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
            int dx=rand()%3-1;
            int dy=rand()%3-1;
            Plants* plant=new Cherrybomb;
            plant->setPos(x()+dx*GAP_X,y()+dy*GAP_Y);
            scene()->addItem(plant);
        }
    }
}

QRectF Cherrybomb::boundingRect() const
{
    return state==2 ? QRectF(-100, -100, 200, 200) : Plants::boundingRect();
}
