#ifndef OTHER_H
#define OTHER_H

#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QPainter>
#include <QMovie>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QSoundEffect>

#define WIDTH 1400
#define ROW1 130
#define GAP 100
#define PLANT_START 300
#define ZOMBIE_START 1028


class other:public QGraphicsItem
{
public:
    other();
    enum{Type=UserType+3};
    int type() const override;
protected:
    QMovie* movie;
};

#endif // OTHER_H
