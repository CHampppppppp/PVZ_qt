#include "button.h"

bool Button::power_activate=false;
bool Button::shovel_activate=false;

Button::Button(int t)
{
    counter=0;
    cool_time=100;
    state=0;
    type=t;

}

void Button::advance(int phase)
{
    if(!phase) return;
    update();
    if(state)
    {
        setCursor(Qt::PointingHandCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
        if(++counter>cool_time) state=1;
    }
}

void Button::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::green);
    QFont font("Calibri", 18, QFont::Bold, true);
    painter->setFont(font);
    //painter->drawRect(boundingRect());
    if(type==FREEZE)
    {
        painter->drawPixmap(QRect(-80, -20, 160, 40), QPixmap(":/resources/button.png"));
        painter->drawText(boundingRect(), Qt::AlignCenter, "FREEZE");
        painter->setPen(Qt::transparent);
        if(counter<cool_time)
        {
            QBrush brush(QColor(0, 0, 0, 200));
            painter->setBrush(brush);
            painter->drawRect(QRectF(-78, -19, 156, 38 * (1 - qreal(counter) / cool_time)));
        }
    }
    else if(type==POWER)
    {
        painter->drawPixmap(QRect(-80, -20, 160, 40), QPixmap(":/resources/button.png"));
        painter->drawText(boundingRect(), Qt::AlignCenter, "POWER");
        painter->setPen(Qt::transparent);
        if(counter<cool_time)
        {
            QBrush brush(QColor(0, 0, 0, 200));
            painter->setBrush(brush);
            painter->drawRect(QRectF(-78, -19, 156, 36 * (1 - qreal(counter) / cool_time)));
        }
    }
    else if(type==SHOVEL)
    {
        painter->drawPixmap(QRect(-40, -40, 80, 80), QPixmap(":/resources/shovelbank.png"));
        painter->drawPixmap(QRect(-35, -35, 70, 70), QPixmap(":/resources/Shovel.png"));
        painter->setPen(Qt::transparent);
        if(counter<cool_time)
        {
            QBrush brush(QColor(0, 0, 0, 200));
            painter->setBrush(brush);
            painter->drawRect(QRectF(-40, -38, 80, 76 * (1 - qreal(counter) / cool_time)));
        }
    }

}


void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(state)
    {
        if(type==FREEZE)//frozen
        {
            if((shovel_activate||power_activate)&&event->button()==Qt::LeftButton)
            {
                shovel_activate=false;
                power_activate=false;
            }
            if(!shovel_activate&&!power_activate&&event->button()==Qt::LeftButton)
            {
                counter=0;
                state=0;
                QList<QGraphicsItem*> items=scene()->items();
                if(!items.isEmpty())
                {
                    QGraphicsItem* item;
                    foreach(item,items)
                    {
                        Zombie* zombie=qgraphicsitem_cast<Zombie*>(item);
                        if(zombie)
                        {
                            zombie->slow=SLOW;
                            zombie->counter=0;
                        }
                    }
                }
            }
        }
        if(type==POWER)//POWER!!
        {
            if(shovel_activate&&event->button()==Qt::LeftButton)
                shovel_activate=false;
            if(power_activate==false&&event->button()==Qt::LeftButton)
            {
                power_activate=true;
                qDebug()<<"power";
            }
            else if(power_activate==true&&event->button()==Qt::LeftButton)
            {
                qDebug()<<"no_power";
                power_activate=false;
            }
        }
        if(type==SHOVEL)//铲子
        {
            if(power_activate&&event->button()==Qt::LeftButton) power_activate=false;
            if(shovel_activate==false&&event->button()==Qt::LeftButton)
            {
                shovel_activate=true;
                qDebug()<<"shovel_activate";
            }
            else if(shovel_activate==true&&event->button()==Qt::LeftButton) {
                qDebug()<<"shovel_not_activate";
                shovel_activate=false;
            }
        }
    }
}

QRectF Button::boundingRect() const
{
    if(type==SHOVEL) return QRectF(-42,-36,80,72);
    return QRectF(-80, -20, 160, 40);
}
