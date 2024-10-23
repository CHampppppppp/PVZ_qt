
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QDebug>
#include <QSoundEffect>

#define WALK 0
#define ATTACK 1
#define DEAD 2
#define BURN 3
#define SLOW 1
#define NO_SLOW 0
#define WIDTH 1400
#define HEIGHT 602


class Zombie :public QGraphicsItem
{
public:
    qreal hp;
    qreal atk;
    int state;
    int slow;
    qreal speed;
    int time;//解冻时间
    int counter;
    enum {Type = UserType +2 };//自定义Type
    Zombie();
    ~Zombie();
    QRectF boundingRect()const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void SetMovie(const QString &path);
    void Sethead(const QString &path);
    virtual void snowfree()=0;
    QMovie* movie;
    bool super;
protected:
    QMovie* head;
};
#endif //ZOMBIE_H
