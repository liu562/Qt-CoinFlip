#include "mycoin.h"
#include<QDebug>
#include<QTimer>
//Mycoin::Mycoin(QWidget *parent) : QPushButton(parent)
//{

//}
Mycoin::Mycoin(QString butImg)
{
    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if(!ret)
    {
        QString str = QString("图片 %1 加载失败").arg(butImg);
        qDebug() << str;
        return;
    }

    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号，并且翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        //设置图片的固定尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());
        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:opx;}");
        //设置图标
        this->setIcon(pixmap);
        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min>this->max)//如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号，并且翻转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)-- );
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });


}

void Mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}


void Mycoin::changFlag()
{
    if(this->flag)//如果是正面，执行下面
    {
        timer1->start(30);
        isAnimation = true;//金币开始做动画了
        this->flag = false;

    }else
    {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}
