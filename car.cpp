#include "car.h"
#include "zombie.h"
#include "plants.h"
#include "button.h"

Car::Car()
{
    atk=10000;
    speed=15.0;
    state=1;
    sound1=new QSoundEffect;
    sound1->setSource(QUrl::fromLocalFile(":/resources/qifei1.wav"));
    sound1->setVolume(0.1f);
    sound1->setLoopCount(1);
    sound2=new QSoundEffect;
    sound2->setSource(QUrl::fromLocalFile(":/resources/car_hit.wav"));
    sound2->setVolume(0.1f);
    sound2->setLoopCount(1);
    sound_played=false;
    setCursor(Qt::PointingHandCursor);
}

void Car::advance(int phase)
{
    if(!phase) return;
    update();
    if(state==1)
    {
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            foreach(QGraphicsItem* item,items)
            {
                 Zombie* zombie=qgraphicsitem_cast<Zombie*>(item);
                if(!sound_played&&zombie->x()-x()<80&&zombie->x()-x()>=20) {
                     qDebug()<<"car_ready";
                    sound1->play();
                    sound_played=true;
                }
                else if(item->x()-x()<20) {
                    state=2;
                    qDebug()<<"car_go";
                    sound2->play();
                }
            }
        }
    }
    else if(state==2)
    {
        setX(x()+speed);
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            foreach(QGraphicsItem* item,items)
            {
                Zombie* zombie=qgraphicsitem_cast<Zombie*>(item);
                //Plants* plant=qgraphicsitem_cast<Plants*>(item);
                //if(plant)
                    //plant->hp-=atk;
                if(zombie&&zombie->x()-x()<=20)
                {
                    zombie->hp-=atk;
                }
            }
        }
    }
    if(x()>WIDTH-160) delete this;
}


void Car::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-30, -30, 60, 60),QPixmap(":/resources/car.png"));
}

bool Car::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    //int randnum=rand()%100;
    //if(randnum<90)
    return other->type()==Zombie::Type&&other->y()==y();
    //else return other->type()==Plants::Type&&qAbs(other->x()-x())<=20&&other->y()==y();//随机撞死植物
}

QRectF Car::boundingRect() const
{
    return QRectF(-30, -30, 60, 60);
}


void Car::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(!Button::power_activate&&!Button::shovel_activate&&event->button()==Qt::LeftButton)
    {
        state=2;
        sound2->play();
    }
}




