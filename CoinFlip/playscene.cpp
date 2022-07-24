#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<mycoin.h>
#include<QPropertyAnimation>
#include<dataconfig.h>
#include<QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}


PlayScene::PlayScene(int levelMum)
{
    this->levelIndex = levelMum;
    QString str = QString("进入了第 %1 关").arg(levelMum);
    qDebug()<<str;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);



    //返回按钮
    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();

        qDebug()<<"翻金币的场景中点击了返回按钮";

        //告诉主场景，我返回了，主场景监听ChooseLevelScene的 返回按钮
        //延时返回
        QTimer::singleShot(300,this,[=]()
        {

            emit this->chooseSceneBack();
        });

    });

    //显示当前关卡数
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    label->setText(str1);
    label->setGeometry(QRect(30, this->height() - 50,120, 50));

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i= 0;i<4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片的显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //显示金币的背景的图案
    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            //绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode(1).png");

            QLabel* label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                //显示金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            Mycoin *coin = new Mycoin(str);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);
            coin->PoxX = i;
            coin->poxY = j;
            coin->flag = gameArray[i][j];

            //将金币放入到金币的二维数组中 以便后期的维护
            coinBtn[i][j] = coin;

            //点击金币 进行翻转
            connect(coin,&Mycoin::clicked,[=](){
                flipSound->play();


                //点击按钮，将所有按钮先禁用
                for (int i=0;i<4;i++) {
                    for (int j=0;j<4;j++) {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
                coin->changFlag();
                //数组内部记录的标志同步修改
                gameArray[i][j] = gameArray[i][j] == 0? 1:0;

                //翻转周围金币，延时翻转
                QTimer::singleShot(150,this,[=](){
                    if(coin->PoxX+1 <=3 )//右侧翻转条件
                    {
                        coinBtn[coin->PoxX+1][coin->poxY]->changFlag();
                        gameArray[coin->PoxX+1][coin->poxY] = gameArray[coin->PoxX+1][coin->poxY] == 0? 1:0;
                    }
                    //左侧翻转条件
                    if(coin->PoxX-1 >= 0)
                    {
                        coinBtn[coin->PoxX-1][coin->poxY]->changFlag();
                        gameArray[coin->PoxX-1][coin->poxY] = gameArray[coin->PoxX-1][coin->poxY] == 0? 1:0;
                    }
                    //上侧翻转条件
                    if(coin->poxY-1 >= 0)
                    {
                        coinBtn[coin->PoxX][coin->poxY-1]->changFlag();
                        gameArray[coin->PoxX][coin->poxY-1] = gameArray[coin->PoxX][coin->poxY-1] == 0? 1:0;
                    }
                    if(coin->poxY+1 <=3 )//下侧翻转条件
                    {
                        coinBtn[coin->PoxX][coin->poxY+1]->changFlag();
                        gameArray[coin->PoxX][coin->poxY+1] = gameArray[coin->PoxX][coin->poxY+1] == 0? 1:0;
                    }

                    //翻完所有金币后将金币解开禁用
                    for (int i=0;i<4;i++) {
                        for (int j=0;j<4;j++) {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for (int i = 0;i<4;i++) {
                        for (int j=0;j<4;j++) {
                            //只要一个是反面，就就将该值改为false，视为未成功
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        //胜利了
                        qDebug()<<"游戏胜利了";
                        //将所有按钮的胜利标识为true，若再次点击按钮，直接return不再响应
                        for (int i = 0;i<4;i++) {
                            for (int j=0;j<4;j++) {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        winSound->play();

                        //将胜利图片移动下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();

                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}




