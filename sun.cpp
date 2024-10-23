#include "sun.h"
#include "shop.h"
#include "button.h"

Sun::Sun(int val_)//植物生成的阳光
{
    val=val_;
    to_x=to_y=0;
    movie= new QMovie(":/resources/sun.gif");
    movie->start();
    speed=1;
    counter=0;
    disapper_time=200;
    collect_time=200;
    state=1;
    Auto=false;
    sound=new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile(":/resources/deng.wav"));
    sound->setVolume(0.3f);
}

Sun::Sun(qreal x,qreal y)//自然掉落的阳光
{
    state=1;
    to_x=x;
    to_y=y;
    val=50;
    movie= new QMovie(":/resources/sun.gif");
    movie->start();
    speed=1;
    counter=0;
    disapper_time=200;
    collect_time=200;
    this->setX(to_x);
    this->setY(90);
    Auto=false;
    sound=new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile(":/resources/deng.wav"));
    sound->setLoopCount(1);
    sound->setVolume(0.3f);
}

Sun::~Sun()
{
    if(movie)
        delete movie;
}

QRectF Sun::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}


void Sun::paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();
    painter->drawImage(QRectF(-35,-35,70,70),image);
}

void Sun::advance(int phase)
{
    if(!phase) return ;
    update();
    if(state==1&&y()!=to_y) setY(y()+speed);
    if(state==2||state==3)
    {
        qreal dx=qAbs(250-to_x);
        qreal dy=qAbs(80-to_y);
        if(x()>250||y()>80)
        {
            if((dx/dy)>12)
            {
                dy=qAbs(70-to_y);
                dx=qAbs(350-to_x);
                speed=(dx/dy)*10;
                setX(x()-(dx/dy)*10);
                setY(y()-10);
                //qDebug()<<"sun1";
                state=3;
            }
            else
            {
                speed=(dx/dy)*50;
                setX(x()-(dx/dy)*50);
                setY(y()-1*50);
                //qDebug()<<"sun2";
            }
            return;
        }
    }
    if((state==2||state==3)&&(x()<250||y()<80)) {
        QList<QGraphicsItem*> items=scene()->items(QPointF(270,0));
        Shop* shop=qgraphicsitem_cast<Shop*>(items[0]);
        shop->sun_val+=val;
        //qDebug()<<"sun_x:"<<x()<<" sun_y:"<<y();
        //qDebug()<<"sunAdded"<<" val: "<<shop->sun_val;
        delete this;
        return;
    }
    //if(state==3&&x()<250&&y()<80) {
            //QList<QGraphicsItem*> items=scene()->items(QPointF(270,0));
            //Shop* shop=qgraphicsitem_cast<Shop*>(items[0]);
            //shop->sun_val+=val;
            //qDebug()<<"sun_x:"<<x()<<" sun_y:"<<y();
            //qDebug()<<"sunAdded"<<" val: "<<shop->sun_val;
            //delete this;
            //return;
        //}

    if(Auto&&++counter>=collect_time)//按下按键，Auto=1
    {
        auto_collect();
        return;
    }
    if(!Auto&&++counter>= disapper_time)
    {
        counter=0;
        delete this;
        return;
    }
}


void Sun::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(!Button::power_activate&&!Button::shovel_activate&&event->button()==Qt::LeftButton)
    {
        sound->play();
        //qDebug()<<"sun_clicked";
        //Shop* shop=qgraphicsitem_cast<Shop*>(scene()->items(QPointF(300,15))[0]);
        //shop->sun_val+=val;
        state=2;
        to_x=x();
        to_y=y();
    }
    else if(Button::power_activate&&event->button()==Qt::LeftButton)
    {
        Button::power_activate=false;
    }
    else if(Button::shovel_activate&&event->button()==Qt::LeftButton) Button::shovel_activate=false;
}

void Sun::auto_collect()
{
    sound->setVolume(0);
    QList<QGraphicsItem*> items=scene()->items();
    if(!items.isEmpty())
    {
        foreach(QGraphicsItem* item,items)
        {
            if(item->type()==other::Type)
            {
                Sun* sun=qgraphicsitem_cast<Sun*>(item);
                if(sun) sun->state=2;
            }
        }
    }
}


