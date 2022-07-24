#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QString>
#include<mycoin.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelMum);

    int levelIndex;//内部成员属性记录所选关卡

    //重新paintEvent事件
    void paintEvent(QPaintEvent *);

    int gameArray[4][4]; //二维数组数据

    Mycoin * coinBtn[4][4];//金币按钮组数
    //是否胜利
    bool isWin = true;

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
