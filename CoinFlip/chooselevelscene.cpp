#include "chooselevelscene.h"
#include<QMenuBar>
#include<QAction>
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡的场景
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });

    //选择关卡的音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);


    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        //qDebug()<<"点击了返回按钮";

        //告诉主场景，我返回了，主场景监听ChooseLevelScene的 返回按钮

        //延时返回
        QTimer::singleShot(100,this,[=](){

            emit this->chooseSceneBack();
        });

    });

    //创建选择关卡的按钮
    for (int i = 0;i<20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4 * 70,130+i/4 * 70);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //播放选择关卡的音效
            chooseSound->play();

            QString str = QString("您选择的是第 %1 关").arg(i+1);
            qDebug()<<str;

            this->hide();//将选关场景隐藏
            //进入到游戏场景
            play = new PlayScene(i+1);
            play->setGeometry(this->geometry());
            play->show();

            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });

        });

        //按钮上显示文字
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        //设置居中
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        label->move(25+i%4 * 70,130+i/4 * 70);
        //鼠标事件穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    }
}


//背景设置
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap(0.5*this->width()-0.5*pix.width(),30,pix.width(),pix.height(),pix);
}















