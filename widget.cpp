#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(720,340);
    this->setFixedSize(720,340);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->resize(740,360);
    ui->graphicsView->setScene(scene);
    QPixmap * pix2 = new QPixmap();
    pix2->load(":/resourses/img/background_warkplace.png");
    scene->addPixmap(*pix2);

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()),
            scene, SLOT(advance()));
    animationTimer->start(1000/60);

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0,0,720,340);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Bird *bird = new Bird();
    bird->setPos(90,200);
    scene->addItem(bird);

    MovingTarget *target = new MovingTarget();
    target->setPos(600,240);
    scene->addItem(target);
}

void Widget::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton exit = QMessageBox::question(this,"Выход","Закончить?", QMessageBox::Yes| QMessageBox::No);
    if (exit == QMessageBox::Yes){
        QApplication::quit();
    }
}

