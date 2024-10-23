#include "pea.h"
#include "zombie.h"

Pea::Pea(int atk_num,int snowor)
{
    atk=atk_num;
    speed=7.0;
    snow=snowor;
}

Pea::~Pea()
{

}

QRectF Pea::boundingRect() const
{
    return QRectF(-12, -28, 24, 24);
}


void Pea::advance(int phase)
{
    if(!phase) return;
    update();
    QList<QGraphicsItem*> items=collidingItems();
    if(!items.empty())
    {
        Zombie* zombie=qgraphicsitem_cast<Zombie*>(items[0]);//第一个碰到的zombie
        if(zombie)
        {
            zombie->hp-=atk;
            if(snow==1)
                zombie->counter=0;
            else if(snow==2) zombie->counter=-100;
            zombie->slow=snow;
            delete this;
            return;
        }
    }
    setX(x()+speed);
    if(x()>WIDTH||x()<0)
    {
        delete this;
    }
}



bool Pea::collidesWithItem(const QGraphicsItem* other,Qt::ItemSelectionMode mode)const
{
    Q_UNUSED(mode)
    if(qAbs(other->x()-x())<30&&other->type()==Zombie::Type&&other->y()==y()) return true;
    return false;
}


void Pea::paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(!snow)
    painter->drawPixmap(QRect(-12, -28, 24, 24),QPixmap(":/resources/pea.png"));
    else
        painter->drawPixmap(boundingRect(),QPixmap(":/resources/peasnow.png"),QRectF());
}

