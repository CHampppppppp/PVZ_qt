
#ifndef PLANTS_H
#define PLANTS_H


#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QDebug>
#include <QSoundEffect>
#define NO_SNOW false
#define SNOW true
#define WIDTH 1400
#define HEIGHT 602

class Plants :public QGraphicsItem
{
public:
    qreal hp;
    int state;//1->正常 0->打激素？
    Plants();
    ~Plants() override;
    QRectF boundingRect() const override;
    enum {Type = UserType+1};
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    void setMovie(QString path);
    int type() const override;//在QGraphicsItem中有 virtual int type() const;
protected:
    QMovie* movie;
    int atk;
    int counter;//发射间隔
    int time;//发射频率
};








#endif // PLANTS_H
