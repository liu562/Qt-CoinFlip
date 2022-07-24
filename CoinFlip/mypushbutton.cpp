#include "mypushbutton.h"
#include<QDebug>
#include<QString>
#include<QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    //成员变量normalImgPath保存正常显示图片路径
    normalImgPath = normalImg;
    //成员变量pressedImgPath保存按下后显示的图片
    pressedImgPath = pressImg;
    //创建QPixmap对象
    QPixmap pixmap;
    //判断是否能够加载正常显示的图片，若不能 提示加载失败
    bool ret = pixmap.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<normalImg<<"加载图片失败！";
    }

    //设置图片的固定尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:opx;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

}

//向上跳跃
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔 单位毫秒
    animation1->setDuration(200);

    //起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation1->start();
}


//向下跳跃
void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔 单位毫秒
    animation1->setDuration(200);

    //起始位置
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation1->start();
}


//重新按钮 按下 和释放事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressedImgPath != "")//传入图片不为空，显示选中图片
    {
        //创建QPixmap对象
        QPixmap pixmap;
        //判断是否能够加载正常显示的图片，若不能 提示加载失败
        bool ret = pixmap.load(this->pressedImgPath);
        if(!ret)
        {
            qDebug()<< pressedImgPath <<"加载图片失败！";
            return;
        }

        //设置图片的固定尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());
        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:opx;}");
        //设置图标
        this->setIcon(pixmap);
        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath != "")
    {
        QPixmap pixmap;
        //判断是否能够加载正常显示的图片，若不能 提示加载失败
        bool ret = pixmap.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<< normalImgPath <<"加载图片失败！";
            return;
        }

        //设置图片的固定尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());
        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:opx;}");
        //设置图标
        this->setIcon(pixmap);
        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    }
    return QPushButton::mouseReleaseEvent(e);
}

