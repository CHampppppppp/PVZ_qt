#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <QGraphicsPixmapItem>
#include "normalzombie.h"
#include "peashooter.h"
#include "snowpeashooter.h"
#include "screenzombie.h"
#include "conezombie.h"
#include "footballzombie.h"
#include "bucketzombie.h"
#include "sunflower.h"
#include "wallnut.h"
#include "cherrybomb.h"
#include "potatomine.h"
#include "shop.h"
#include "sun.h"
#include "car.h"
#include "button.h"
#include "map.h"



#define ROW1 130
#define GAP 100
#define WIDTH 1020
#define HEIGHT 602
#define ZOMBIE_START 1028
#define PLANT_START 300



using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void addZombies();
    void addPlants();
    void check();
    void playmusic();
    void keyPressEvent(QKeyEvent *event);


private:
    QSoundEffect* sound_wabiwabu;
    Map* map_pause;
    bool paused;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer* timer;
    QGraphicsPixmapItem *bk;
    QSoundEffect* sound_bk;
    bool bk_played;
};
#endif // MAINWINDOW_H
