#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QString>
class Mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit Mycoin(QWidget *parent = nullptr);

    Mycoin(QString butImg); //代表图片路径

    int PoxX;//x坐标
    int poxY;//y坐标
    bool flag;//正反标志

    void changFlag();//改变标志，执行翻转
    QTimer *timer1;//正面翻反面
    QTimer *timer2;//反面翻正面
    int min = 1;//最小图片
    int max = 8;//最大图片

    //执行动画 标志
    bool isAnimation = false;

    //重写按下
    void mousePressEvent(QMouseEvent *e);

    //是否胜利
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
