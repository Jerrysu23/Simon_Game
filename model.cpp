/**
    Name: Jerry Su && Seth Boehm
    Date: October 28, 2022
    Assignment: A5: Qt Simon Game
*/

#include "model.h"
#include <QTimer>
#include <random>

/**
 * @brief Construct Model.
 */
Model::Model(QObject *parent) : QObject{parent}
{

}

/**
 * @brief emit startButtonClicked_signal and add starting value to buttonSequence.
 * Call newLevel_slot to begin the first level of the game.
 */
void Model::gameStart_slot(){
    // Add our first button (string - "red" or "blue") to the buttonSequence.
    buttonSequence.push_back(randomButton());

    // Get the game started.
    QTimer::singleShot(500, this, &Model::newLevel_slot);
    emit startButtonClicked_signal();
}

/**
 * @brief Runs an entire level, i.e. will flash every button in the sequence so far.
 * Ex: if we have four items in our sequence, it will create four flashes, reading from buttonSequence
 * for information on which buttons to flash.
 */
void Model::newLevel_slot()
{
    // Flash every button in the sequence.
    for (int i = 0; i < (int)buttonSequence.size(); i++)
    {
        if (buttonSequence[i] == "red")
        {
            // Keep in mind this first flash will happen immediatly, since i = 0.
            QTimer::singleShot(flashInterval*2.5*i, this, &Model::flashButtonRed_signal);
        }
        else if (buttonSequence[i] == "blue")
        {
            QTimer::singleShot(flashInterval*2.5*i, this, &Model::flashButtonBlue_signal);
        }
    }

    // Allow the user to interact with buttons once the pattern is done displaying.
    // size-1 because the for loop ends 1 before buttonSequence.size()
    // +flashInterval for the duration of the flash itself
    int timeUntilFlashingStops = (((int)buttonSequence.size()-1)*flashInterval*2.5) + flashInterval;
    QTimer::singleShot(timeUntilFlashingStops, this, &Model::allowButtonInteraction_slot);
}

/**
 * @brief Core game logic. Either fail the game, continue the sequence, or
 * start a new sequence upon completion of the prior sequence.
 */
void Model::redButtonPressed_slot()
{
    // If the pattern is being displayed to the user, don't allow button interaction.
    if (!allowButtonInteraction)
        return;

    emit clearHintText_signal();

    // If it doesn't match, it means the player pressed the wrong button and lost the game.
    if (buttonSequence[indexInSequence] != "red")
    {
        allowButtonInteraction = false;
        score = 0;
        progressPercent = 0;
        indexInSequence = 0;
        flashInterval = 250;
        buttonSequence.clear();
        emit gameFailed_signal();
        return;
    }

    // Keep track of where we are in the sequence.
    indexInSequence++;
    progressPercent = ((double)indexInSequence / (double)buttonSequence.size()) * 100;
    emit updateProgressBar_signal();

    // Check if this was the last button we had to press. If so, we can start a new sequence with
    // an additional button and adjust some values.
    if (indexInSequence == (int)buttonSequence.size())
    {
        buttonSequence.push_back(randomButton());
        allowButtonInteraction = false;
        indexInSequence = 0;
        progressPercent = 0;
        score++;
        flashInterval *= 0.95;
        QTimer::singleShot(800, this, &Model::newLevel_slot);
        QTimer::singleShot(800, this, &Model::updateProgressBar_signal);
        emit updateScore_signal();
        emit enableHintButton_signal();
    }
}

/**
 * @brief Core game logic. Either fail the game, continue the sequence, or
 * start a new sequence upon completion of the prior sequence.
 */
void Model::blueButtonPressed_slot()
{
    // If the pattern is being displayed to the user, don't allow button interaction.
    if (!allowButtonInteraction)
        return;

    emit clearHintText_signal();

    // If it doesn't match, it means the player pressed the wrong button and lost the game.
    if (buttonSequence[indexInSequence] != "blue")
    {
        allowButtonInteraction = false;
        score = 0;
        progressPercent = 0;
        indexInSequence = 0;
        flashInterval = 250;
        buttonSequence.clear();
        emit gameFailed_signal();
        return;
    }

    // Keep track of where we are in the sequence.
    indexInSequence++;
    progressPercent = ((double)indexInSequence / (double)buttonSequence.size()) * 100;
    emit updateProgressBar_signal();

    // Check if this was the last button we had to press. If so, we can start a new sequence with
    // an additional button and adjust some values.
    if (indexInSequence == (int)buttonSequence.size())
    {
        buttonSequence.push_back(randomButton());
        allowButtonInteraction = false;
        indexInSequence = 0;
        progressPercent = 0;
        score++;
        flashInterval *= 0.95;
        QTimer::singleShot(800, this, &Model::newLevel_slot);
        QTimer::singleShot(800, this, &Model::updateProgressBar_signal);
        emit updateScore_signal();
        emit enableHintButton_signal();
    }
}

/**
 * @brief Return the next button the user must press, used for the hint message.
 */
std::string Model::getHintData()
{
    if (buttonSequence.size() > 0)
        return buttonSequence[indexInSequence];
    else
        return "NA";
}

/**
 * @brief Disable button interaction.
 */
void Model::stopButtonInteraction_slot()
{
    allowButtonInteraction = false;
}

/**
 * @brief Enable button interaction.
 */
void Model::allowButtonInteraction_slot()
{
    allowButtonInteraction = true;
}

/**
 * @brief Return either "red" or "blue" randomly
 */
std::string Model::randomButton()
{
    int zeroOrOne = rand() % 2;
    if (zeroOrOne == 0)
    {
        return "red";
    }
    else
    {
        return "blue";
    }
}

/**
 * @brief returns flashInterval.
 */
int Model::getFlashInterval()
{
    return flashInterval;
}

/**
 * @brief returns Score.
 */
int Model::getScore()
{
    return score;
}

/**
 * @brief returns progressPercent.
 */
int Model::getProgressPercent()
{
    return progressPercent;
}
