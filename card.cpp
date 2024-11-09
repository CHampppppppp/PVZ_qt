#include "card.h"

const QMap<QString, int> Card::id = {{"sunflower", 0}, {"peashooter", 1}, {"snowpeashooter", 2}, {"potatomine", 3},
{"wallnut", 4}, {"repeater", 5}, {"cherrybomb", 6}};
const QMap<int,QPoint> Card::pos={{0,QPoint(350,45)},{1,QPoint(411,45)},{2,QPoint(472,45)},{3,QPoint(533,45)},{4,QPoint(594,45)},
{5,QPoint(655,45)},{6,QPoint(716,45)}};
const QMap<int,QString> Card::mapping = {{0,"sunflower"}, { 1,"peashooter"}, {2,"snowpeashooter"}, {3,"potatomine"},
{4,"wallnut"}, {5,"repeater"}, {6,"cherrybomb"}};
const QMap<QString, int> Card::cool = {{"sunflower",150}, {"peashooter",250}, {"cherrybomb",400}, {"wallnut", 300},
{"snowpeashooter", 400}, {"potatomine", 450}, {"repeater", 400}};
const QMap<QString,int> Card::cost={{"sunflower",50}, {"peashooter",100}, {"cherrybomb",250}, {"wallnut", 50},
{"snowpeashooter", 200}, {"potatomine", 75}, {"repeater", 200}};

int Card::card_id=-1;
bool Card::card_activate=false;
Card::Card(const QString& name_)
{
    name=name_;
    counter=0;
    state=0;
}

void Card::advance(int phase)
{
    if(!phase) return;
    update();
    if(counter<cool[name])
    {
        ++counter;
        state=0;
        setCursor(Qt::ArrowCursor);
    }
    else {
        state=1;
        setCursor(Qt::PointingHandCursor);
    }
}

void Card::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->scale(0.6, 0.58);
    //painter->setPen(Qt::green);
    painter->drawPixmap(QRect(-50, -70, 100, 140),QPixmap(":/resources/card.png"));
    painter->drawPixmap(QRect(-35, -42, 70, 70),QPixmap(":/resources/"+name+".png"));
    //painter->drawRect(boundingRect());
    QFont font;
    font.setPointSizeF(18);
    painter->setFont(font);
    painter->drawText(QPoint(-30,62),QString::number(cost[name]));
    if(counter<cool[name])
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[name])));
    }
}

QRectF Card::boundingRect() const
{
    return QRectF(-20, -70, 40, 120);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((Button::power_activate||Button::shovel_activate)&&event->button()==Qt::LeftButton)
    {
        Button::power_activate=false;
        Button::shovel_activate=false;
    }
    else if(state&&!card_activate&&event->button()==Qt::LeftButton)
    {
        card_activate=true;
        Card::card_id=id[name];
        qDebug()<<"card_activate";
        qDebug()<<"card_id: "<<card_id;
    }
    else if(state&&card_activate&&event->button()==Qt::LeftButton)
    {
        card_activate=false;
        qDebug()<<"card_unactivate";
    }
}
