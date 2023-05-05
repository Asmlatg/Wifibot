#include <QCoreApplication>
#include "myrobot.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    MyRobot robot;
    robot.doConnect();

    return a.exec();
}

