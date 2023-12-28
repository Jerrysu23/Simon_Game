/**
    Name: Jerry Su && Seth Boehm
    Date: October 28, 2022
    Assignment: A5: Qt Simon Game
*/

#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "model.h"


QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(Model& model, QWidget *parent = nullptr);
    ~View();

public slots:
    void startButtonClicked_slot();
    void resetGame_slot();
    void flashButtonBlue_slot();
    void flashButtonRed_slot();
    void setDefaultButtonColors_slot();
    void updateScore_slot();
    void updateProgressBar_slot();
    void displayHint_slot();
    void clearHintText_slot();
    void enableHintButton_slot();


signals:
    void gameStart_signal();
    void redButtonPressed_signal();
    void blueButtonPressed_signal();


private:
    Ui::View *ui;
};

#endif // VIEW_H
