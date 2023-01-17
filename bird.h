#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QTimer>
#include <cmath>

class Bird : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bird(QObject *parent = 0);
    ~Bird();
    void advance(int phase);

signals:
private slots:
    void ballistic();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QTimer* ballisticTimer;
    QTimer* deliteTimer;
    float xspeed = 0, yspeed = 0;
};


class MovingTarget : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    explicit MovingTarget(QObject *parent = 0);
    ~MovingTarget();

    enum {Type = UserType +1};
    MovingTarget(int yspread);

    void advance(int phase){
        if (phase){
            moveBy(0, yspeed);
            if (data(0).toBool())
                delete this;
        }
    }

    int type() const;

private:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float yspeed = -0.5;

    QPointF lastPoint;

};
#endif // BIRD_H
