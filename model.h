/**
    Name: Jerry Su && Seth Boehm
    Date: October 28, 2022
    Assignment: A5: Qt Simon Game
*/

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <vector>


class Model : public QObject
{
    Q_OBJECT
    bool allowButtonInteraction = false;
    int score = 0;
    int progressPercent = 0;
    int indexInSequence = 0;
    int flashInterval = 250;
    std::vector<std::string> buttonSequence;

public:
    explicit Model(QObject *parent = nullptr);
    int getFlashInterval();
    int getScore();
    int getProgressPercent();
    std::string getHintData();

public slots:
    void gameStart_slot();
    void newLevel_slot();
    void redButtonPressed_slot();
    void blueButtonPressed_slot();
    void stopButtonInteraction_slot();
    void allowButtonInteraction_slot();

private:
    std::string randomButton();

signals:
    void flashButtonRed_signal();
    void flashButtonBlue_signal();
    void startButtonClicked_signal();
    void gameFailed_signal();
    void updateScore_signal();
    void updateProgressBar_signal();
    void clearHintText_signal();
    void enableHintButton_signal();
};

#endif // MODEL_H
