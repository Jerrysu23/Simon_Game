/**
    Name: Jerry Su && Seth Boehm
    Date: October 28, 2022
    Assignment: A5: Qt Simon Game
*/

#include "view.h"
#include "ui_view.h"
#include "model.h"
#include "QTimer"

Model* modelPtr;

/**
 * @brief Construct View. Create connections and set modelRef.
 */
View::View(Model& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);

    modelPtr = &model;

    // UI to Model
    connect(ui -> startButton,
            &QPushButton::clicked,
            &model,
            &Model::gameStart_slot
            );
    connect(ui -> redButton,
            &QPushButton::clicked,
            &model,
            &Model::redButtonPressed_slot
            );
    connect(ui -> blueButton,
            &QPushButton::clicked,
            &model,
            &Model::blueButtonPressed_slot
            );

    // Model to UI
    connect(&model,
            &Model::startButtonClicked_signal,
            this,
            &View::startButtonClicked_slot
            );
    connect(&model,
            &Model::flashButtonBlue_signal,
            this,
            &View::flashButtonBlue_slot
            );
    connect(&model,
            &Model::flashButtonRed_signal,
            this,
            &View::flashButtonRed_slot
            );
    connect(&model,
            &Model::gameFailed_signal,
            this,
            &View::resetGame_slot
            );
    connect(&model,
            &Model::updateScore_signal,
            this,
            &View::updateScore_slot
            );
    connect(&model,
            &Model::updateProgressBar_signal,
            this,
            &View::updateProgressBar_slot
            );
    connect(&model,
            &Model::enableHintButton_signal,
            this,
            &View::enableHintButton_slot
            );
    connect(&model,
            &Model::clearHintText_signal,
            this,
            &View::clearHintText_slot
            );

    // UI to UI
    connect(ui -> hintButton,
            &QPushButton::clicked,
            this,
            &View::displayHint_slot
            );
}

/**
 * @brief Destruct View.
 */
View::~View()
{
    delete ui;
}

/**
 * @brief Toggle buttons and set score to display default 0.
 */
void View::startButtonClicked_slot()
{
    ui -> startButton -> setDisabled(true);
    ui -> redButton -> setEnabled(true);
    ui -> blueButton -> setEnabled(true);
    ui -> hintButton -> setEnabled(true);
    ui -> messageLabel -> setText("Match the pattern displayed.");
    ui -> scoreLabel -> setText("Score: " + QString::number(modelPtr->getScore()));
}

/**
 * @brief Toggle buttons, set score to display default 0, and display failure message.
 */
void View::resetGame_slot()
{
    ui -> startButton -> setEnabled(true);
    ui -> redButton -> setDisabled(true);
    ui -> blueButton -> setDisabled(true);
    ui -> hintButton -> setDisabled(true);
    ui -> hintText -> setText("");
    ui -> messageLabel -> setText("You failed. Try again.");
    updateScore_slot();
    updateProgressBar_slot();
}

/**
 * @brief Display hint for the user.
 */
void View::displayHint_slot()
{
    std::string nextButton = modelPtr->getHintData();
    ui -> hintText -> setText("The next button is " + QString::fromStdString(nextButton) + ".");
    ui -> hintButton -> setDisabled(true);
}

void View::enableHintButton_slot()
{
    ui -> hintButton -> setEnabled(true);
}

void View::clearHintText_slot()
{
    ui -> hintText -> setText("");
}

/**
 * @brief Update the score.
 */
void View::updateScore_slot()
{
    ui -> scoreLabel -> setText("Score: " + QString::number(modelPtr->getScore()));
}

/**
 * @brief Update progress bar.
 */
void View::updateProgressBar_slot()
{
    ui -> progressBar -> setValue(modelPtr->getProgressPercent());
}

/**
 * @brief Change the color of the red button to a lighter color for a short time,
 * then use singleShot to change it back, creating a flash effect.
 */
void View::flashButtonRed_slot()
{
    ui -> redButton -> setStyleSheet("background-color: rgb(250,120,120)");

    QTimer::singleShot(modelPtr->getFlashInterval(), this, &View::setDefaultButtonColors_slot);
}

/**
 * @brief Change the color of the blue button to a lighter color for a short time,
 * then use singleShot to change it back, creating a flash effect.
 */
void View::flashButtonBlue_slot()
{
    ui -> blueButton -> setStyleSheet("background-color: rgb(168,209,223)");

    QTimer::singleShot(modelPtr->getFlashInterval(), this, &View::setDefaultButtonColors_slot);
}

/**
 * @brief Sets all buttons back to their default colors.
 */
void View::setDefaultButtonColors_slot()
{
    ui -> redButton -> setStyleSheet("background-color: rgb(250,0,0)");
    ui -> blueButton -> setStyleSheet("background-color: rgb(26,163,232)");
}
