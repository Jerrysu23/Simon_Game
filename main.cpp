/**
    Name: Jerry Su && Seth Boehm
    Date: October 28, 2022
    Assignment: A5: Qt Simon Game
*/

#include "view.h"
#include "model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    View w(model);
    w.show();
    return a.exec();
}
