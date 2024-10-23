#include "plants.h"
#include "zombie.h"


Plants::Plants()
{
    hp=state=0;
    movie=nullptr;
    atk=counter=time=0;
}

Plants::~Plants()
{
    delete movie;
}

QRectF Plants::boundingRect() const
{
    return QRectF(-35,-35,70,70);//y轴正方向向下
}

void Plants::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();
    painter->drawImage(boundingRect(),image);
    //painter->drawRect(boundingRect());
}


bool Plants::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(qAbs(other->x()-x())<=30&&other->y()==y()&&other->type()==Zombie::Type)
    {
        return true;
    }
    return false;
}


int Plants::type() const
{
    return Type;
}

void Plants::setMovie(QString path)
{
    if(movie) delete movie;
    movie=new QMovie(path);
    if(!movie->isValid()) qDebug()<<"植物动画error";
    movie->setSpeed(50);
    movie->start();
}




