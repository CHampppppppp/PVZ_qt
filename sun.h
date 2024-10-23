#ifndef SUN_H
#define SUN_H

#include "other.h"

class Sun:public other//待实现：点击阳光后直线移动到shop处
{
public:
    Sun(int val_);
    Sun(qreal x,qreal y);
    ~Sun() override;
    void advance(int phase) override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect() const override;
    void auto_collect();
    int val;
    qreal to_x;
    qreal to_y;
protected:
    QMovie* movie;
    QSoundEffect* sound;
    qreal speed;
    int disapper_time;
    int collect_time;
    int counter;
    int state;
    bool Auto;
};

#endif // SUN_H
