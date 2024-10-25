#include "other.h"
#include "plants.h"
#include "shop.h"


class Card:public other
{
public:
    const static QMap<QString,int>cool;
    const static QMap<QString,int>id;
    const static QMap<int,QPoint>pos;
    const static QMap<QString,int>cost;
    const static QMap<int,QString>mapping;//序号配对
    Card(const QString& name_);
    void advance(int phase)override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    static bool card_activate;
    static int card_id;
    int state;
    int counter;
    QString name;
private:
};
