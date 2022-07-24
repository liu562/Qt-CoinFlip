#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
//#include"chooselevelscene.h"
#include<QSound> //多媒体模块下 的音效头文件
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设定固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("老帮主带你翻金币");

    //点击退出，退出程序
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);



    //创建开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();//重新显示主场景
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        //播放开始音效
        startSound->play();

        startBtn->zoom1();//向下跳跃
        startBtn->zoom2();//向上跳跃

        //延时0.5s，进入选择场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });

}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}

MainScene::~MainScene()
{
    delete ui;
}

