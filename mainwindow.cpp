#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    bk_played=false;
    srand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    sound_wabiwabu=new QSoundEffect;
    sound_wabiwabu->setSource(QUrl::fromLocalFile(":/resources/wabiwabu.wav"));
    sound_wabiwabu->setVolume(0.4f);
    sound_wabiwabu->play();
    sound_bk=new QSoundEffect;
    sound_bk->setSource(QUrl::fromLocalFile(":/resources/crazyDave.wav"));
    sound_bk->setLoopCount(QSoundEffect::Infinite);
    sound_bk->setVolume(0.6f);
    //ui->setupUi(this);
    timer=new QTimer;
    scene=new QGraphicsScene(this);
    scene->setSceneRect(100, 0, WIDTH,HEIGHT);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    bk=new QGraphicsPixmapItem;
    bk->setZValue(0);
    bk->setPixmap(QPixmap(":/resources/Background.jpg"));
    scene->addItem(bk);
    Plants* ps=new Sunflower;
    Zombie* zb=new Conezombie;
    Shop* shop=new Shop;
    shop->setPos(230,0);
    shop->setZValue(3);
    scene->addItem(shop);
    ps->setPos(PLANT_START+160,ROW1+3*GAP);
    zb->setPos(PLANT_START+20,ROW1+3*GAP);
    //scene->addItem(zb);
    //scene->addItem(ps);
    Map* map=new Map(1);
    map->setZValue(2);
    map->setPos(618,326);
    scene->addItem(map);
    map_pause=new Map(0);
    Button* button1=new Button(FREEZE);
    Button* button2=new Button(POWER);
    Button* button3=new Button(SHOVEL);
    button1->setPos(918,20);
    button1->setZValue(3);
    button2->setPos(918,60);
    button2->setZValue(3);
    button3->setPos(798,40);
    button3->setZValue(3);
    scene->addItem(button1);
    scene->addItem(button2);
    scene->addItem(button3);
    for(int i=0;i<5;i++)
    {
        Car* car=new Car;
        car->setPos(PLANT_START-80,ROW1+i*GAP);
        car->setZValue(3);
        scene->addItem(car);
    }
    for(int i=0;i<7;i++)
    {
        Card* card=new Card(Card::mapping[i]);
        card->setPos( 350+61 * i, 45);
        card->setZValue(3);
        scene->addItem(card);
    }
    //view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer,&QTimer::timeout,this,&MainWindow::playmusic);
    connect(timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    connect(timer,&QTimer::timeout,this,&MainWindow::addZombies);//随机生成僵尸,今天加了音效和推车
    //connect(timer,&QTimer::timeout,this,&MainWindow::addPlants);//随机生成植物
    view=new QGraphicsView(scene,this);
    //ui->graphicsView->setScene(scene);
    view->resize(WIDTH+2,HEIGHT+2);
    timer->start(33);
    view->show();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete view;
}

void MainWindow::addZombies()
{
    static int low = 4;
    static int high = 8;
    static int maxtime = 20 * 1000 / 33;
    static int time = maxtime / 2;
    static int counter = 0;
    if(++counter>time)
    {
        if (++low > high)
        {
            maxtime /= 1.3;
            high *= 2;
        }
        counter=0;
        int type=rand()%100;
        Zombie* zombie=nullptr;
        if(type<70)
            zombie=new normalzombie;
        else if(type<75)
            zombie=new screenzombie;
        else if(type<85)
            zombie=new Conezombie;
        else if(type<94)
            zombie=new Bucketzombie;
        else if(type<100)
            zombie=new Footballzombie;
        int row=(rand()%5)*GAP+ROW1;
        zombie->setPos(ZOMBIE_START,row);
        zombie->setZValue(2);
        scene->addItem(zombie);
    }
}

void MainWindow::addPlants()
{
    static int count=0;
    static int k=0;
    static int maxt=6;
    if(count%maxt==0) {
        k++;
        maxt--;
    }
    int time=800-k*50;
    static int counter=0;
    if(++counter>time)
    {
        counter=0;
        count++;
        int type=rand()%100;
        Plants* plant=nullptr;
        if(type<20)
            plant=new Sunflower;
        else if(type<40)
            plant=new peashooter;
        else if(type<55)
            plant=new snowpeashooter;
        else if(type<65)
            plant=new Repeater;
        else if(type<80)
            plant=new Wallnut;
        else if(type<90)
            plant=new Potatomine;
        else if(type<100)
            plant= new Cherrybomb;
        QList<QGraphicsItem*> items=scene->items();
        int row=(rand()%5)*GAP+ROW1;
        int col=PLANT_START+(rand()%9)*80;
        if(!items.isEmpty())
        {
            while(true)
            {
                row=(rand()%5)*GAP+ROW1;
                col=PLANT_START+(rand()%9)*80;
                foreach(QGraphicsItem* item,items)
                {
                    if(item->type()==Plants::Type)
                    {
                        if(row==item->y()||col==item->x())
                            break;
                    }
                }break;
            }
        }
        plant->setZValue(2);
        plant->setPos(col,row);
        scene->addItem(plant);
    }
}


void MainWindow::playmusic()
{
    static int counter=0;
    if(!sound_bk->isPlaying()&&++counter>=150)
    {
        sound_bk->play();
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        if (paused) {
            timer->start(); // 恢复计时器
            sound_bk->setVolume(0.6f);
            scene->removeItem(map_pause);
            paused=false;
        } else {
            timer->stop();  // 暂停计时器
            sound_bk->setVolume(0.0f);
            map_pause->setZValue(10);
            map_pause->setPos(0,0);
            scene->addItem(map_pause);
            paused=true;
        }
    }

    // 调用父类的键盘事件处理函数（必要时保留其他按键功能）
    QWidget::keyPressEvent(event);
}
