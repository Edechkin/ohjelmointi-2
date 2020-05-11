/* This program is a modified version of a tetris game. Further instructions in
 * the "instructions"-folder.
* Name: Eetu Jokinen
* Student number: 273281
* UserID: teekkart ( Necessary due to gitlab folder naming. )
* eetu.jokinen@tuni.fi
* */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <utility>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    minutes_(0),
    seconds_(0)




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

    // Creating a timer to count the time that a tetromino is stopped after
    // pressing H-key.


    hold_timer_ = new QTimer;
    connect(hold_timer_, SIGNAL(timeout()), this, SLOT(hold_disable()));

    // Creating a timer to show the time og the game to the player.

    clock_ = new QTimer;
    connect(clock_, SIGNAL(timeout()), this, SLOT(seconds_gone()));
    ui->lcdNumberMin->setStyleSheet("Background-color: black");
    ui->lcdNumberSec->setStyleSheet("Background-color: cyan");

    // Creating a timer that determines the time how frequently a
    // tetromino is moved downwards automatically.

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
    delete timer_;
    delete hold_timer_;
    delete clock_;
}

void MainWindow::seconds_gone(){

    ++seconds_;
    if (seconds_>=60){
        ++minutes_;
        seconds_ = 0;
    }
    ui->lcdNumberSec->display(seconds_);
    ui->lcdNumberMin->display(minutes_);
}

void MainWindow::game_over()
{
    ui->timerLabel->setText("Game Over");
    clock_->stop();
    timer_->stop();
    ui->startPushButton->setEnabled(true);
    scene_->clear();
    ui->startPushButton->setText("Restart");
    reset_grid();

}

bool MainWindow::can_create(int i)
{
    std::vector<std::pair<int, int>> grid_points = {};
    switch (i){
        case HORIZONTAL:
            grid_points = {{4,0}, {5,0},
                           {6,0}, {7,0}};
            break;
        case LEFT_CORNER:
            grid_points = {{4,0}, {5,0},
                           {6,0}, {4,1}};
            break;
        case RIGHT_CORNER:
            grid_points = {{4,0}, {5,0},
                            {6,0}, {6,1}};
            break;
        case SQUARE:
            grid_points = {{4,0}, {5,0},
                           {4,1}, {5,1}};
            break;
        case PYRAMID:
            grid_points = {{4,1}, {5,1},
                           {6,1}, {5,0}};
            break;
        case STEP_UP_LEFT:
            grid_points = {{4,0}, {5,0},
                           {5,1}, {6,1}};
            break;
        case STEP_UP_RIGHT:
            grid_points = {{4,1}, {5,0},
                           {5,1}, {6,0}};
            break;
    }
    for(std::pair<int,int> point: grid_points) {
        if (grid_.at(point.second).at(point.first) == 1) {
            game_over();
            return false;

        }
    }
    return true;
}

void MainWindow::reset_grid()
{

    for(int i = 0; i < 24; i++) {
        for (int j = 0; j < 12; j++) {
            grid_.at(i).at(j) = 0;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if(timer_->isActive()) {
        if(event->key() == Qt::Key_S) {
            tetro_move();
        }
        if(event->key() == Qt::Key_A) {
            if (can_move(LEFT)){
                for (auto rect : cur_tetro_){

                    rect->moveBy( -SQUARE_SIDE, 0);
                }
            }
        }
        if(event->key() == Qt::Key_D) {
            if (can_move(RIGHT)){
                for (auto rect : cur_tetro_){

                    rect->moveBy( SQUARE_SIDE, 0);
                }
            }
        }
        if (!been_held_){
            if(event->key() == Qt::Key_H){
                timer_->stop();
                hold_timer_->start(3000);
            }
        }

    }
}



void MainWindow::on_startPushButton_clicked()
{
    ui->timerLabel->setText("Good luck!");
    seconds_ = 0;
    minutes_ = 0;
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
    clock_->start(1000);


    int i = distr(randomEng);
    create_tetro(i);
    ui->startPushButton->setDisabled(true);
    timer_->start(250);

}

void MainWindow::hold_disable()
{
    if( been_held_){
        hold_timer_->stop();
        been_held_ = false;
    } else{
        timer_->start();
        been_held_ = true;
    }
}

void MainWindow::tetro_move()
{

    if (can_move(DOWN)){
        for (auto rect : cur_tetro_){

            rect->moveBy(0, SQUARE_SIDE);
        }
    }
    else{
        update_grid();

        int i = distr(randomEng);
        if(can_create(i)) {
            create_tetro(i);
        } else {
            game_over();
        }

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
            build_horizontal();
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

    if (!rect.contains(x, y)) {
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
    qreal delta_x = 0;
    qreal delta_y = 0;
    switch (i) {
        case DOWN:
            delta_y = 20;
            break;
        case LEFT:
            delta_x = -20;
            break;
        case RIGHT:
            delta_x = 20;
            break;
        break;
    }

    for (auto rect : cur_tetro_){
        if (!is_free_space(rect->x() + delta_x, rect->y() + delta_y))
            return false;
    }
    return true;
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

void MainWindow::build_horizontal()
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
