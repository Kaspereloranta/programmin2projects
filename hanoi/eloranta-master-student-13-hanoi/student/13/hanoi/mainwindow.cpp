#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    // We need a graphics scene in which to draw a rectangles.
    scene_ = new QGraphicsScene(this);
    // The graphicsView object is placed on the window
    // at the following coordinates:
    int left_margin = 10; // x coordinate
    int top_margin = 270; // y coordinate
    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphics_view->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphics_view->setScene(scene_);
    // Connecting timer to enable the stopwatch of the game.
    connect(&timer_, &QTimer::timeout, this, &MainWindow::timer_function);
    // Setting the height and width of the scene_.
    scene_->setSceneRect(0,0,BORDER_RIGHT-1,BORDER_DOWN-1);
    // Defining the colors and outline of the rectangles.
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);
    // Lets create three QGraphicRectItems which are used as a rods of the game.
    rectangle_ = scene_->addRect((BORDER_RIGHT-BORDER_LEFT)/4,
                                  BORDER_DOWN-HEIGHT_OF_THE_RODS,
                                  4,HEIGHT_OF_THE_RODS,blackPen,redBrush);
    rectangle_ = scene_->addRect((BORDER_RIGHT-BORDER_LEFT)/2,
                                  BORDER_DOWN-HEIGHT_OF_THE_RODS,
                                  4,HEIGHT_OF_THE_RODS,blackPen,greenBrush);
    rectangle_ = scene_->addRect((BORDER_RIGHT-BORDER_LEFT)/2+
                                 (BORDER_RIGHT-BORDER_LEFT)/4,
                                  BORDER_DOWN-HEIGHT_OF_THE_RODS               
                                 ,4,HEIGHT_OF_THE_RODS,blackPen,blueBrush);
    // Lets create three Rod -objects and save pointers to them.
    // The parameter given to rods is AMOUNT_OF_DISKS+1 because
    // using that we can make sure that the seed value for the top disk's size
    // is always greater than the largest disk size which are created later
    // on while loop. With that parameter we can add any size disk to be the
    // bottom disk of rod.
    std::shared_ptr<Rod> rod_A(new Rod(AMOUNT_OF_DISKS+1));
    std::shared_ptr<Rod> rod_B(new Rod(AMOUNT_OF_DISKS+1));
    std::shared_ptr<Rod> rod_C(new Rod(AMOUNT_OF_DISKS+1));
    three_rods.push_back(rod_A);
    three_rods.push_back(rod_B);
    three_rods.push_back(rod_C);
    unsigned int disks_added = 0;
    // The largest disk's size will be AMOUNT_OF_DISKS, the next largest's will be
    // AMOUNT_OF_DISK -1 etc.
    unsigned int disk_size = AMOUNT_OF_DISKS;
    while (disks_added < AMOUNT_OF_DISKS)
    {
        // Let's create graphic item to represent disk on the game and
        // save pointer to that item.
        QGraphicsRectItem* graphic_disc_item = scene_->addRect(
                                            (BORDER_RIGHT-BORDER_LEFT)/4
                                                 -3.75*AMOUNT_OF_DISKS
                                                 + 3.75*disks_added
                                                ,BORDER_DOWN-6-6*disks_added,
                                           7.5*AMOUNT_OF_DISKS-7*disks_added,6,
                                                 blackPen,redBrush);
        // Let's create new Disk -object to reprsent the disk and save pointer to that.
        std::shared_ptr<Disk> new_disk(new Disk(disk_size,disks_added));
        A_graphic_items_.push_back(graphic_disc_item);
        Original_order.push_back(graphic_disc_item);
        three_rods.at(0)->add_disk(new_disk);
        ++disks_added;
        --disk_size;
    }
    // Disabling the movement buttons until the game is started.
    change_buttons_status(false);
    // Disabling the reset button until the game is finished.
    ui_->push_button_reset_board->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // Checks if the game is running and if it is moves certain
    // disk given as a keyboard command if movement is legal.
    if(is_game_running)
    {
        if(event->key() == Qt::Key_1)
        {
            on_push_button_A_to_B_clicked();
            return;
        }
        if(event->key() == Qt::Key_Q)
        {
            on_push_button_B_to_A_clicked();
            return;
        }
        if(event->key() == Qt::Key_2)
        {
            on_push_button_A_to_C_clicked();
            return;
        }
        if(event->key() == Qt::Key_W)
        {
            on_push_button_C_to_A_clicked();
            return;
        }
        if(event->key() == Qt::Key_3)
        {
            on_push_button_B_to_C_clicked();
            return;
        }
        if(event->key() == Qt::Key_E)
        {
            on_push_button_C_to_B_clicked();
            return;
        }
    }
}

void MainWindow::on_push_button_A_to_B_clicked()
{
    // Checks is there a disk to be moved.
    if(three_rods.at(0)->return_structure().size() != 0)
    {
        // The one to be moved.
        std::shared_ptr<Disk> transferable = three_rods.at(0)->pointer_to_top();
        // Checks is the movement legal.
        if(three_rods.at(1)->add_disk(transferable))
        {
            ui_->text_browser->setPlainText("");
            // Graphic item to be moved.
            QGraphicsRectItem* graphic_disc_item = A_graphic_items_.at
                    (A_graphic_items_.size()-1);
            // Remove the disk from the previous rod.
            three_rods.at(0)->remove_disk();
            // Calculates how much the graphic item's y-coordinate
            // must be changed.
            int height_difference = (B_graphic_items_.size()
                                     -transferable->original_y())*-6;
            // Transferring graphic item to right structure.
            B_graphic_items_.push_back(graphic_disc_item);
            A_graphic_items_.pop_back();
            // Set disk to right position on GUI.
            graphic_disc_item->setPos((BORDER_RIGHT-BORDER_LEFT)/4,
                         height_difference);
            // Changing disk's color.
            graphic_disc_item->setBrush(Qt::green);
            // Let player know what move has been made.
            ui_->text_browser_movement_history->insertPlainText("A -> B \n");
            scroll_down();
        }
        else
        {
            // Let player know the move he tried is illegal.
            ui_->text_browser->setPlainText("Illegal move.");
        }
        // Checking has game ended.
        if(B_graphic_items_.size()==AMOUNT_OF_DISKS)
        {
            // Let player know about his huge achievement.
            ui_->text_browser->setPlainText("Game ended. You won!");
            // Let's stop the game.
            timer_.stop();
            is_game_running = false;
            change_buttons_status(false);
            // Checking has new record been set.
            check_best_time();
            // Making reseting the board possible.
            ui_->push_button_reset_board->setEnabled(true);
        }
    }
}

void MainWindow::on_push_button_B_to_A_clicked()
{
    // Checks is there a disk to be moved.
    if(three_rods.at(1)->return_structure().size() != 0)
    {
        // The one to be moved.
        std::shared_ptr<Disk> transferable = three_rods.at(1)->pointer_to_top();
        // Checks is the movement legal.
        if(three_rods.at(0)->add_disk(transferable))
        {
            ui_->text_browser->setPlainText("");
            // Graphic item to be moved.
            QGraphicsRectItem* graphic_disc_item = B_graphic_items_.at
                    (B_graphic_items_.size()-1);
            // Remove the disk from the previous rod.
            three_rods.at(1)->remove_disk();
            // Calculates how much the graphic item's y-coordinate must be changed.
            int height_difference = (A_graphic_items_.size()
                                     -transferable->original_y())*-6;
            // Transferring graphic item to right structure.
            A_graphic_items_.push_back(graphic_disc_item);
            B_graphic_items_.pop_back();
            // Set disk to right position on GUI.
            graphic_disc_item->setPos(0,height_difference);
            // Changing disk's color.
            graphic_disc_item->setBrush(Qt::red);
            // Let player know what move has been made.
            ui_->text_browser_movement_history->insertPlainText("B -> A \n");
            scroll_down();
        }
        else
        {
            // Let player know the move he tried is illegal.
            ui_->text_browser->setPlainText("Illegal move.");
        }
    }
}

void MainWindow::on_push_button_A_to_C_clicked()
{
    // Checks is there a disk to be moved.
    if(three_rods.at(0)->return_structure().size() != 0)
    {
        // The one to be moved.
        std::shared_ptr<Disk> transferable = three_rods.at(0)->pointer_to_top();
        // Checks is the movement legal.
        if(three_rods.at(2)->add_disk(transferable))
        {
            ui_->text_browser->setPlainText("");
            // Graphic item to be moved.
            QGraphicsRectItem* graphic_disc_item = A_graphic_items_.at
                    (A_graphic_items_.size()-1);
            // Remove the disk from the previous rod.
            three_rods.at(0)->remove_disk();
            // Calculates how much the graphic item's y-coordinate must be changed.
            int height_difference = (C_graphic_items_.size()
                                     -transferable->original_y())*-6;
            // Transferring graphic item to right structure.
            C_graphic_items_.push_back(graphic_disc_item);
            A_graphic_items_.pop_back();
            // Set disk to right position on GUI.
            graphic_disc_item->setPos((BORDER_RIGHT-BORDER_LEFT)/2,
                         height_difference);
            // Changing disk's color.
            graphic_disc_item->setBrush(Qt::blue);
            // Let player know what move has been made.
            ui_->text_browser_movement_history->insertPlainText("A -> C \n");
            scroll_down();
        }
        else
        {
            // Let player know the move he tried is illegal.
            ui_->text_browser->setPlainText("Illegal move.");
        }
    }
}

void MainWindow::on_push_button_C_to_A_clicked()
{
    // Checks is there a disk to be moved.
    if(three_rods.at(2)->return_structure().size() != 0)
    {
        // The one to be moved.
        std::shared_ptr<Disk> transferable= three_rods.at(2)->pointer_to_top();
        // Checks is the movement legal.
        if(three_rods.at(0)->add_disk(transferable))
        {
            ui_->text_browser->setPlainText("");
            // Graphic item to be moved.
            QGraphicsRectItem* graphic_disc_item = C_graphic_items_.at
                    (C_graphic_items_.size()-1);
            // Remove the disk from the previous rod.
            three_rods.at(2)->remove_disk();
            // Calculates how much the graphic item's y-coordinate must be changed.
            int height_difference = (A_graphic_items_.size()
                                     -transferable->original_y())*-6;
            // Transferring graphic item to right structure.
            A_graphic_items_.push_back(graphic_disc_item);
            C_graphic_items_.pop_back();
            // Set disk to right position on GUI
            graphic_disc_item->setPos(0,height_difference);
            // Changing disk's color.
            graphic_disc_item->setBrush(Qt::red);
            // Let player know what move has been made.
            ui_->text_browser_movement_history->insertPlainText("C -> A \n");
            scroll_down();
        }
        else
        {
            // Let player know the move he tried is illegal.
            ui_->text_browser->setPlainText("Illegal move.");
        }
    }
}

void MainWindow::on_push_button_B_to_C_clicked()
{
    // Checks is there a disk to be moved.
    if(three_rods.at(1)->return_structure().size() != 0)
    {
        // The one to be moved.
        std::shared_ptr<Disk> transferable = three_rods.at(1)->pointer_to_top();
        if(three_rods.at(2)->add_disk(transferable))
        // Checks is the movement legal.
        {
            ui_->text_browser->setPlainText("");
            // Graphic item to be moved.
            QGraphicsRectItem* graphic_disc_item = B_graphic_items_.at
                    (B_graphic_items_.size()-1);
            // Remove the disk from the previous rod.
            three_rods.at(1)->remove_disk();
            // Calculates how much the graphic item's y-coordinate must be changed.
            int height_difference = (C_graphic_items_.size()
                                     -transferable->original_y())*-6;
            // Transferring graphic item to right structure.
            C_graphic_items_.push_back(graphic_disc_item);
            B_graphic_items_.pop_back();
            // Set disk to right position on GUI.
            graphic_disc_item->setPos((BORDER_RIGHT-BORDER_LEFT)/2
                         ,height_difference);
            // Changing disk's color.
            graphic_disc_item->setBrush(Qt::blue);

            // Let player know what move has been made.
            ui_->text_browser_movement_history->insertPlainText("B -> C \n");
            scroll_down();
        }
        else
        {
            // Let player know the move he tried is illegal.
            ui_->text_browser->setPlainText("Illegal move.");
        }
    }
}

void MainWindow::on_push_button_C_to_B_clicked()
{
    // Checks is there a disk to be moved.
    if(three_rods.at(2)->return_structure().size() != 0)
    {
        // The one to be moved.
        std::shared_ptr<Disk> transferable = three_rods.at(2)->pointer_to_top();
        // Checks is the movement legal.
        if(three_rods.at(1)->add_disk(transferable))
        {
            ui_->text_browser->setPlainText("");
            // Graphic item to be moved.
            QGraphicsRectItem* graphic_disc_item = C_graphic_items_.at
                    (C_graphic_items_.size()-1);
            // Remove the disk from the previous rod.
            three_rods.at(2)->remove_disk();
            // Calculates how much the graphic item's y-coordinate must be changed.
            int height_difference = (B_graphic_items_.size()
                                     -transferable->original_y())*-6;
            // Transferring graphic item to right structure.
            B_graphic_items_.push_back(graphic_disc_item);
            C_graphic_items_.pop_back();
            // Set disk to right position on GUI.
            graphic_disc_item->setPos((BORDER_RIGHT-BORDER_LEFT)/4
                         ,height_difference);
            // Changing disk's color.
            graphic_disc_item->setBrush(Qt::green);
            // Let player know what move has been made.
            ui_->text_browser_movement_history->insertPlainText("C -> B \n");
            scroll_down();
        }
        else
        {
            // Let player know the move he tried is illegal.
            ui_->text_browser->setPlainText("Illegal move.");
        }
        // Checking has game ended.
        if(B_graphic_items_.size()==AMOUNT_OF_DISKS)
        {
            // Let player know about his huge achievement.
            ui_->text_browser->setPlainText("Game ended. You won!");
            // Let's stop the game.
            timer_.stop();
            is_game_running = false;
            change_buttons_status(false);
            // Checking has new record been set.
            check_best_time();
            // Making reseting the board possible.
            ui_->push_button_reset_board->setEnabled(true);
        }
    }
}

void MainWindow::on_push_button_start_game_clicked()
{
    // Starts the game, activates the movement buttons and launches the timer.
    is_game_running = true;
    ui_->push_button_start_game->setEnabled(false);
    change_buttons_status(true);
    timer_.start(1000);
}

void MainWindow::check_best_time()
{
    // If the game finished was first new record will always been set.
    if(best_minutes_==0 and best_seconds_==0)
    {
        best_minutes_ = minutes_;
        best_seconds_ = seconds_;
    }
    else if(minutes_ == best_minutes_ and seconds_ < best_seconds_)
    {
        best_minutes_ = minutes_;
        best_seconds_ = seconds_;
    }
    else if(minutes_ < best_minutes_)
    {
        best_minutes_ = minutes_;
        best_seconds_ = seconds_;
    }
    // Reseting the stopwatch and updating the best time
    // if new record has been made.
    seconds_ = 0;
    minutes_ = 0;
    ui_->lcd_number_seconds->display(seconds_);
    ui_->lcd_number_minutes->display(minutes_);
    ui_->lcd_number_best_seconds->display(best_seconds_);
    ui_->lcd_number_best_minutes->display(best_minutes_);
}

void MainWindow::timer_function()
{
    // Executing the game's stopwatch with simple idea.
    // timer_ -object will call this function every second.
    ++seconds_;
    if(seconds_== 60)
    {
        seconds_ = 0;
        ++minutes_;
    }
    ui_->lcd_number_seconds->display(seconds_);
    ui_->lcd_number_minutes->display(minutes_);
}

void MainWindow::scroll_down()
{
    // Lets scroll text_browser_movement_history down in order to make it
    // possible for player to always see recent movements made without scrolling
    // manually down.
    QScrollBar *sb = ui_->text_browser_movement_history->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::change_buttons_status(bool value)
{
    // Changes every movemement button's status to
    // bool value which is given as a parameter..
    ui_->push_button_A_to_B->setEnabled(value);
    ui_->push_button_A_to_C->setEnabled(value);
    ui_->push_button_B_to_A->setEnabled(value);
    ui_->push_button_B_to_C->setEnabled(value);
    ui_->push_button_C_to_A->setEnabled(value);
    ui_->push_button_C_to_B->setEnabled(value);
}

void MainWindow::on_push_button_reset_board_clicked()
{
    ui_->text_browser->setPlainText("");
    // Return A_graphic_items_ to original order how it is suppoed to be
    // at the beginning of the game and clears other structures containing
    // graphical items.
    A_graphic_items_ = Original_order;
    B_graphic_items_.clear();
    C_graphic_items_.clear();
    // Let's set positions and colors of items to be what they were at the
    // beginning of the game.
    for(auto graphic_item : A_graphic_items_)
    {
        graphic_item->setPos(0,0);
        graphic_item->setBrush(Qt::red);
    }
    std::vector<std::shared_ptr<Disk>> orig_order = {};
    unsigned int searched_y = 0;
    // Let's search and save the original order of Disk -objects
    // to vector structure orig_order.
    while(searched_y < AMOUNT_OF_DISKS)
    {
        // Let's run through all the three rods and
        // their Disk -structures.
        for(std::shared_ptr<Rod> rod : three_rods)
        {
            for(std::shared_ptr<Disk> disk : rod->return_structure())
            {
                // original_y() returns the disk's original position
                // on the structure at the beginning of the game.
                if(disk->original_y()==searched_y)
                {
                   orig_order.push_back(disk);
                }
            }
         }
        ++searched_y;
    }
    // Let's set Rod A structure to be the original order
    // we just found using while and for loops.
    three_rods.at(0)->set_structure(orig_order);
    // Let's clear Rod B's and Rod C's structures
    // and reset their size_of_top_disk to be
    // the seed value.
    three_rods.at(1)->clear_structure();
    three_rods.at(1)->set_seed_value();
    three_rods.at(2)->clear_structure();
    three_rods.at(2)->set_seed_value();
    // Let's clear the movement history.
    ui_->text_browser_movement_history->clear();
    // Let's disable the reset button until game is finished.
    ui_->push_button_reset_board->setEnabled(false);
    // Let's make starting new game possible.
    ui_->push_button_start_game->setEnabled(true);
}
