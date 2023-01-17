#include "bird.h"

Bird::Bird(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    ballisticTimer = new QTimer(this);
    connect(ballisticTimer, SIGNAL(timeout()),
            this, SLOT(ballistic()));
}

Bird::~Bird()
{

}

MovingTarget::MovingTarget(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

MovingTarget::~MovingTarget()
{

}

QRectF Bird::boundingRect() const
{
    return QRectF (-20,-20,40,40);
}

void Bird::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(QRect(-20,-20,40,40),QImage(":/resourses/img/red-bird"));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF MovingTarget::boundingRect() const
{
    return QRectF (-20,-20,40,40);
}

void MovingTarget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(QRect(-20,-20,40,40),QImage(":/resourses/img/target"));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void Bird::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void Bird::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Bird::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF Point = event->scenePos();

    float dy = sqrt(pow(Point.x() - Point.x(), 2)+ pow(200 - Point.y(), 2))/75;
    float dx = sqrt(pow(90 - Point.x(), 2)+ pow(Point.y() - Point.y(), 2))/80;
    if(Point.x()> 90){
        dx = -dx;
    }
    if(Point.y()< 200){
        dy = -dy;
    }
    if(dx>1){
        dx=1;
    }
    if(dy<-1){
        dy=-1;
    }
    xspeed = 7*(dx);
    yspeed = -6*(dy);
    this->setCursor(QCursor(Qt::ArrowCursor));
    ballisticTimer->start(30);
}


void Bird::advance(int phase){
    if(phase){
        moveBy(xspeed,yspeed);
        if(data(0).toBool()){
            delete this;
        }
    }else{
        foreach(QGraphicsItem* item, collidingItems()){
            if(item->type()==MovingTarget::Type){
                item->setData(0, true);
                setData(0, true);
            }
        }
    }
}

int MovingTarget::type() const{
    return Type;
}

void Bird::ballistic()
{
    yspeed +=0.15;
}
