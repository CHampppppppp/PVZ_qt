#include "shop.h"

Shop::Shop()
{
    sun_val=100;
    counter=0;
    sun_generate_time=700;
    pre_sunval=sun_val;
}

QRectF Shop::boundingRect() const
{
    return QRectF(0,0, 530,90);
}

void Shop::paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    //painter->drawRect(boundingRect());
    painter->drawPixmap(QRect(0,0,528,95),QPixmap(":/resources/shop.png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(QRectF(-255, 23, 600, 110), Qt::AlignCenter, QString::number(sun_val));
    painter->drawPoint(0,0);
}

void Shop::advance(int phase)
{
    if(!phase) return;
    update();
    if(++counter>=sun_generate_time)
    {
        counter=0;
        qreal x=rand()%700+PLANT_START;
        qreal y=rand()%(HEIGHT-ROW1)+ROW1;
        Sun* sun=new Sun(x,y);
        sun->setZValue(4);
        scene()->addItem(sun);
    }
    if(sun_val!=pre_sunval)
    {
        pre_sunval=sun_val;
        //qDebug()<<"sun_val_changed:"<<sun_val;
    }
}

bool Shop::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==other->Type&&other->x()==x()&&other->y()==y();
}
