#include "zombie.h"
#include "plants.h"
#include <QDebug>

Zombie::Zombie()
{
    movie = head = nullptr;
    hp = atk=0;
    state=WALK;
    slow= NO_SLOW;
    speed = 0.0;
    time=0;
    counter=0;
    super=false;
}

Zombie::~Zombie()
{
    delete head;
    delete movie;
}

QRectF Zombie::boundingRect() const
{
    return QRectF(-30,-100,100,140);
}

void Zombie::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();

    if (slow) {
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QColor color = image.pixelColor(x, y);
                color.setRed(0);
                color.setGreen(0);
                color.setBlue(250);                // 保持蓝色
                //color.setAlphaF(0.5);
                image.setPixelColor(x, y, color);
            }
        }
    }
    if(head)
    {
        QImage head_image=head->currentImage();
        if(slow)
        {
            for (int y = 0; y < head_image.height(); ++y) {
                for (int x = 0; x < head_image.width(); ++x) {
                    QColor color = head_image.pixelColor(x, y);
                    color.setRed(0);
                    color.setGreen(0);
                    color.setBlue(250);                // 保持蓝色
                    //color.setAlphaF(0.5);
                    head_image.setPixelColor(x, y, color);
                }
            }
        }
        painter->drawImage(QRectF(-70,-100,140,140),head_image);
    }
    painter->drawImage(QRectF(-70,-100,140,140),image);
    //painter->drawRect(boundingRect());

}


bool Zombie::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(qAbs(other->x()-x())<=30&&other->y()==y()&&other->type()==Plants::Type)
    {
        return true;
    }
    return false;
}


int Zombie::type() const
{
    return Type;
}


void Zombie::SetMovie(const QString &path)
{
    if(movie)
        delete movie;
    movie=new QMovie(path);
    if (!movie->isValid()) {
        qDebug() << "Movie loading failed: Invalid file" << path;
    } else {
        if(super)
        {
            movie->setSpeed(300);
            speed=3.0;
        }
        movie->start();
    }
}

void Zombie::Sethead(const QString &path)
{
    if(head)
        delete head;
    head=new QMovie(path);
    if (!head->isValid()) {
        qDebug() << "Movie loading failed: Invalid file" << path;
    } else {
        if(super)
            head->setSpeed(300);
        head->start(); // 开始播放动画
    }
}


















