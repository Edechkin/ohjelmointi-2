#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)



{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.

    /*QBrush redBrush(Qt::red);
    QPen redPen(Qt::black);
    redPen.setWidth(2);
    rect_ = scene_->addRect(110, 0, SQUARE_SIDE, SQUARE_SIDE, redPen, redBrush);
//    QRectF rect = scene_->sceneRect();
    QTimer timer_ = new QTimer;
    */
    //creating the grid.
    timer_ = new QTimer;
    timer_->setSingleShot(false);
    connect(timer_, &QTimer::timeout, this, &MainWindow::tetro_move);



    std::vector<std::vector<int>> grid;
    std::vector<int> vec(12, 0);

    for (int i = 0 ; i <= 23 ; i++){
        grid.push_back(vec);
    }
    grid_ = grid;
    rect_ = nullptr;
    cur_tetro_ = {nullptr, nullptr, nullptr, nullptr};

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if(event->key() = Qt::Key_S) {

    }
}


void MainWindow::on_startPushButton_clicked()
{
    //timer_.setSingleShot(false);
    //connect(&timer_, &QTimer::timeout, this, &MainWindow::tetro_move);
    // Luo/pudota tetromino ja käynnistkä kello
//    build_horo();
    int i = distr(randomEng);
    create_tetro(i);
    ui->startPushButton->setDisabled(true);
    timer_->start(250);

}

void MainWindow::tetro_move()
{
    for (QGraphicsRectItem* rect : cur_tetro_){
        qDebug() << rect->x();

        if (!is_free_space(rect->x(), rect->y() + 20)){
            qDebug() << rect->y();
            update_grid();
            int i = distr(randomEng);
            create_tetro(i);
            break;
        }
    }
    for (auto rect : cur_tetro_){

        rect->moveBy(0, SQUARE_SIDE);
    }

}

void MainWindow::create_tetro(int i)
{
    QBrush redBrush(Qt::red);
    QPen redPen(Qt::black);
    cur_tetro_.at(0) = scene_->addRect(0, 0, SQUARE_SIDE,
                                       SQUARE_SIDE, redPen, redBrush);
    cur_tetro_.at(1) = scene_->addRect(0, 0, SQUARE_SIDE,
                                       SQUARE_SIDE, redPen, redBrush);
    cur_tetro_.at(2) = scene_->addRect(0, 0, SQUARE_SIDE,
                                       SQUARE_SIDE, redPen, redBrush);
    cur_tetro_.at(3) = scene_->addRect(0, 0, SQUARE_SIDE,
                                       SQUARE_SIDE, redPen, redBrush);
    switch (i) {
        case HORIZONTAL:
            build_horo();
        break;
        case LEFT_CORNER:
            build_left();
            break;
        case RIGHT_CORNER:
            build_right();
            break;
        case SQUARE:
            build_square();
            break;
        case STEP_UP_RIGHT:
            build_step_right();
            break;
        case STEP_UP_LEFT:
            build_step_left();
            break;
        case PYRAMID:
            build_pyramid();
            break;
        break;
    }
}

bool MainWindow::is_free_space(qreal x, qreal y)
{
    int a = static_cast<int>(x) / 20;
    int b = static_cast<int>(y) / 20;

    QRectF rect = scene_->sceneRect();

    if (!rect.contains(x, y)) { //a >= 12 || b >= 24)
        return false;
    }

    else if (grid_.at(b).at(a) == 0){
        return true;

    }
    else{
        return false;
    }
}

bool MainWindow::can_move(int i)
{
    qreal deltax = 0;
    qreal deltay = 0;
    switch (i) {
        case DOWN:
            deltay = 20;
            break;
        case LEFT:
            deltax = -20;
            break;
        case RIGHT:
            deltax = 20;
            break;
        break;
    }
}

void MainWindow::update_grid()
{
    int a = 0;
    int b = 0;
    for (auto rect : cur_tetro_){
        a = static_cast<int>(rect->x()) / 20;
        b = static_cast<int>(rect->y()) / 20;
        grid_.at(b).at(a) = 1;
    }
}

void MainWindow::build_horo()
{
    QBrush redBrush(Qt::red);
    QPen redPen(Qt::black);
    redPen.setWidth(2);
    for (int i = 0; i < 4; i++) {
        cur_tetro_.at(i)->setX(80 + (i*20));
        cur_tetro_.at(i)->setY(0);
        cur_tetro_.at(i)->setBrush(redBrush);
        cur_tetro_.at(i)->setPen(redPen);
    }
}

void MainWindow::build_left()
{
    QBrush redBrush(Qt::cyan);
    QPen redPen(Qt::black);
    redPen.setWidth(2);
    cur_tetro_.at(0)->setX(80);
    cur_tetro_.at(0)->setY(0);
    cur_tetro_.at(1)->setX(100);
    cur_tetro_.at(1)->setY(0);
    cur_tetro_.at(2)->setX(120);
    cur_tetro_.at(2)->setY(0);

    cur_tetro_.at(3)->setX(80);
    cur_tetro_.at(3)->setY(20);

    for( auto rect: cur_tetro_) {
        rect->setBrush(redBrush);
        rect->setPen(redPen);
    }

}

void MainWindow::build_right()
{
    QBrush redBrush(Qt::green);
    QPen redPen(Qt::black);
    redPen.setWidth(2);

    cur_tetro_.at(0)->setX(80);
    cur_tetro_.at(0)->setY(0);
    cur_tetro_.at(1)->setX(100);
    cur_tetro_.at(1)->setY(0);
    cur_tetro_.at(2)->setX(120);
    cur_tetro_.at(2)->setY(0);

    cur_tetro_.at(3)->setX(120);
    cur_tetro_.at(3)->setY(20);

    for( auto rect: cur_tetro_) {
        rect->setBrush(redBrush);
        rect->setPen(redPen);
    }
}

void MainWindow::build_square()
{
    QBrush redBrush(Qt::blue);
    QPen redPen(Qt::black);
    redPen.setWidth(2);

    cur_tetro_.at(0)->setX(80);
    cur_tetro_.at(0)->setY(0);
    cur_tetro_.at(1)->setX(100);
    cur_tetro_.at(1)->setY(0);
    cur_tetro_.at(2)->setX(80);
    cur_tetro_.at(2)->setY(20);

    cur_tetro_.at(3)->setX(100);
    cur_tetro_.at(3)->setY(20);

    for( auto rect: cur_tetro_) {
        rect->setBrush(redBrush);
        rect->setPen(redPen);
    }
}

void MainWindow::build_pyramid()
{
    QBrush redBrush(Qt::yellow);
    QPen redPen(Qt::black);
    redPen.setWidth(2);

    cur_tetro_.at(0)->setX(80);
    cur_tetro_.at(0)->setY(20);
    cur_tetro_.at(1)->setX(100);
    cur_tetro_.at(1)->setY(20);
    cur_tetro_.at(2)->setX(120);
    cur_tetro_.at(2)->setY(20);

    cur_tetro_.at(3)->setX(100);
    cur_tetro_.at(3)->setY(0);

    for( auto rect: cur_tetro_) {
        rect->setBrush(redBrush);
        rect->setPen(redPen);
    }
}

void MainWindow::build_step_left()
{
    QBrush redBrush(Qt::darkCyan);
    QPen redPen(Qt::black);
    redPen.setWidth(2);

    cur_tetro_.at(0)->setX(80);
    cur_tetro_.at(0)->setY(0);
    cur_tetro_.at(1)->setX(100);
    cur_tetro_.at(1)->setY(0);
    cur_tetro_.at(2)->setX(100);
    cur_tetro_.at(2)->setY(20);

    cur_tetro_.at(3)->setX(120);
    cur_tetro_.at(3)->setY(20);

    for( auto rect: cur_tetro_) {
        rect->setBrush(redBrush);
        rect->setPen(redPen);
    }
}

void MainWindow::build_step_right()
{
    QBrush redBrush(Qt::magenta);
    QPen redPen(Qt::black);
    redPen.setWidth(2);
    cur_tetro_.at(0)->setX(80);
    cur_tetro_.at(0)->setY(20);
    cur_tetro_.at(1)->setX(100);
    cur_tetro_.at(1)->setY(0);
    cur_tetro_.at(2)->setX(100);
    cur_tetro_.at(2)->setY(20);

    cur_tetro_.at(3)->setX(120);
    cur_tetro_.at(3)->setY(0);

    for( auto rect: cur_tetro_) {
        rect->setBrush(redBrush);
        rect->setPen(redPen);
    }
}
