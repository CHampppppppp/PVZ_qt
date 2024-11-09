#ifndef CAR_H
#define CAR_H


#include "other.h"

class Car:public other
{
public:
    Car();
    void advance(int phase) override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect() const override;
protected:
    QSoundEffect* sound1;
    QSoundEffect* sound2;
    bool sound_played;
    qreal speed;
    int atk;
    int state;
};

#endif // CAR_H
