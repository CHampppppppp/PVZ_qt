#include "map.h"

Map::Map(int t)
{
    state=1;//钱够了，state0->钱不够，鼠标变成arrow
    type=t;
}

void Map::advance(int phase)
{
    if(type==1)
    {
        if(!phase) return;
    update();
    if(Card::card_activate)
        setCursor(Qt::PointingHandCursor);
    else if(!Card::card_activate||!state) setCursor(Qt::ArrowCursor);
    }
    else return;
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
    //painter->setPen(Qt::green);
    //painter->drawRect(boundingRect());
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(type)
    {
        QGraphicsItem* it=scene()->itemAt(QPoint(230,0),transform());
    Shop *shop=qgraphicsitem_cast<Shop*>(it);
    int id=Card::card_id;
    int cost=Card::cost[Card::mapping[id]];
    //qDebug()<<"shop_sun:"<<shop->sun_val;
    //qDebug()<<"cost:"<<cost;
    if(event->button()==Qt::LeftButton&&Card::card_activate&&shop->sun_val>=cost)
    {

        if(shop->sun_val!=shop->sun_val-cost)
            shop->sun_val-=cost;
        QGraphicsItem* item=scene()->itemAt(QPoint(Card::pos[Card::card_id]),transform());
        Card* card=qgraphicsitem_cast<Card*>(item);
        card->state=0;
        card->counter=0;
        Card::card_activate=false;
        QPointF pos=mapToScene(event->pos());
        int x=((int(pos.x()) - 249) / (GAP_X-30) *(GAP_X-30) + PLANT_START);
        int y=((int(pos.y()) - 81) / GAP_Y * GAP_Y + ROW1);
        if(scene()->itemAt(QPoint(x,y),transform())->type()==Plants::Type) return;
        Plants* plant=nullptr;
        switch(id)
        {
        case 0:
            plant=new Sunflower;
            break;
        case 1:
            plant=new peashooter;
            break;
        case 2:
            plant=new snowpeashooter;
            break;
        case 3:
            plant=new Potatomine;
            break;
        case 4:
            plant=new Wallnut;
            break;
        case 5:
            plant=new Repeater;
            break;
        case 6:
            plant=new Cherrybomb;
            break;
        default:
            qDebug()<<"invalid_id";
            break;
        }
        plant->setPos(x,y);
        plant->setZValue(2);
        scene()->addItem(plant);
    }
    else if(shop->sun_val<cost||event->button()==Qt::RightButton)
    {
        state=0;
        Card::card_activate=false;
    }
    }
    else return;
}

QRectF Map::boundingRect() const
{
    return type?QRectF(-369, -235, 738, 470):QRectF(0,0,WIDTH,HEIGHT);
}



