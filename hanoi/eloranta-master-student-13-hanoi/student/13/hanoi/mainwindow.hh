/* Module: Mainwindow
 *
 * Includes Tower of Hanoi game with graphical user interface with lots of
 * different funtionalities.
 *
 * TIE-0220x S2019
 * Name: Kasper Eloranta
 * E-mail: kasper.eloranta@tuni.fi
 * Student id: 274212
 *
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include <rod.hh>
#include <memory>
#include <string>
#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QScrollBar>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor of the Mainwindow.
    explicit MainWindow(QWidget *parent = 0);
    // Destructor of the Mainwindow.
    ~MainWindow();
    // Function which makes moving disks with keyboard commands possible.
    void keyPressEvent(QKeyEvent* event) override;

private slots:

    // Next six functions does all the same thing but for different
    // disks. For example on_push_button_A_to_B_clicked() moves
    // disk from A rod to B rod if movement is legal. Since B is
    // the target rod functions which move disks to B rod also
    // checks if the game has ended and player has won.
    void on_push_button_A_to_B_clicked();
    void on_push_button_B_to_A_clicked();
    void on_push_button_A_to_C_clicked();
    void on_push_button_C_to_A_clicked();
    void on_push_button_B_to_C_clicked();
    void on_push_button_C_to_B_clicked();
    // Starts the game.
    void on_push_button_start_game_clicked();
    // Checks whether the best recorderd time has been beaten or not
    // after the game is finsihed.
    void check_best_time();
    // Runs the timer of the game and updates the numbers in
    // lcd_numbers which represents the time spent on a game.
    void timer_function();
    // Scrolls down text_browser_movement_history always after
    // player has done the move. Player may see recent moves made.
    void scroll_down();
    // Changes movement buttons to be enabled or disabled depending on
    // is the parameter given true or false.
    void change_buttons_status(bool value);
    // Resets the game board. This button is enabled after player
    // wins the game so player can start new game without restarting
    // the program.
    void on_push_button_reset_board_clicked();

private:

    Ui::MainWindow *ui_;
    QGraphicsScene* scene_;
    QGraphicsRectItem* rectangle_;
    QTimer timer_;
    unsigned const int AMOUNT_OF_DISKS = 6;
    const int HEIGHT_OF_THE_RODS = 100;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 200;
    const int BORDER_LEFT = 25;
    const int BORDER_RIGHT = 460;
    bool is_game_running = false;
    // seconds_ and minutes_ represents the time passed
    // on a single game.
    int seconds_ = 0;
    int minutes_ = 0;
    // best_seconds_ and best_minutes_ represents the best time
    // recorded to win the game.
    int best_seconds_ = 0;
    int best_minutes_ = 0;
    // Vector structure three_rods which will include three Rod objects.
    // First one represents the Rod A, second Rod B and third Rod C.
    std::vector<std::shared_ptr<Rod>> three_rods;
    // Original_order will include the original order of the graphic disk
    // items in which they were at the beginning of the game on the Rod A.
    // Saving that order makes it easier to reset the game board
    // after the game has ended.
    std::vector<QGraphicsRectItem*> Original_order;
    // Next three vector structures will include graphic disk items of the game.
    // At the beginning of the game A_graphic_items_ will include all of them.
    // When player makes move that specific graphic disk item will be tranported
    // to new structure. The goal of the game is to get all of the items to
    // B_graphic_items_ in legal order.
    std::vector<QGraphicsRectItem*> A_graphic_items_;
    std::vector<QGraphicsRectItem*> B_graphic_items_;
    std::vector<QGraphicsRectItem*> C_graphic_items_;

};



#endif // MAINWINDOW_HH
