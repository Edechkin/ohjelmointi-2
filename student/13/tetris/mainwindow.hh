/* This program is a modified version of a tetris game. Further instructions in
 * the "instructions"-folder.
* Name: Eetu Jokinen
* Student number: 273281
* UserID: teekkart ( Necessary due to gitlab folder naming. )
* eetu.jokinen@tuni.fi
* */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event) override;


private slots:

    // Begins the game, is disabled during a game.
    void on_startPushButton_clicked();

    void hold_disable();

    void seconds_gone();
private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

    QGraphicsRectItem* rect_;

    std::vector<std::vector<int>> grid_;

    QTimer* hold_timer_;
    QTimer* timer_;
    QTimer* clock_;
    int minutes_;
    int seconds_;

    std::vector<QGraphicsRectItem*> cur_tetro_;

    void game_over();

    bool can_create(int i);

    void reset_grid();

    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};

    enum Tetro_directions {DOWN,
                          LEFT,
                          RIGHT};


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;



    void tetro_move();

    void create_tetro(int i);

    bool is_free_space(qreal x, qreal y);
    bool can_move(int i);

    // When tetromino can't move/is placed grid vector itmes that are equivalent
    // to the tetromino's coordinates, their values are changed from 0 to 1.
    void update_grid();

    void build_horizontal();
    void build_left();
    void build_right();
    void build_square();
    void build_pyramid();
    void build_step_left();
    void build_step_right();

    bool been_held_ = false;


};

#endif // MAINWINDOW_HH
