
#ifndef PEA_H
#define PEA_H


#include "other.h"

class Pea:public other
{
public:
    Pea(int atk_num,int snowor);
    ~Pea() override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem*other,Qt::ItemSelectionMode mode)const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget) override;
    QRectF boundingRect() const override;
private:
    qreal speed;
    int atk;
    int snow;
};

#endif // PEA_H
