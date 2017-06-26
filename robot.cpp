#include "clientlib.h"

Robot::Robot():context(1){
    socket = Message::client_socket(context);
}
Robot::~Robot(){
    delete socket;
}
void Robot::moveForward(int mm){
    Message message;
    message.setcommand(1);
    message.setint1(mm);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
    }
}
void Robot::turn(double angle){
    Message message;
    message.setcommand(8);
    message.setdouble1(angle);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
    }
}
void Robot::deltaTurn(double angle){
    Message message;
    message.setcommand(9);
    message.setdouble1(angle);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
    }
}

void Robot::moveToObstacle(int distance){
    Message message;
    message.setcommand(2);
    message.setint1(distance);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
    }
}
double Robot::checkRangeDevices(double& angleOut,double angleIn1, double angleIn2){
    Message message;
    message.setcommand(3);
    message.setdouble1(angleIn1);
    message.setdouble2(angleIn2);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
        double distance = message.getdouble1();
        angleOut = message.getdouble2();
        return distance;
    }
}
double Robot::getBatteryVoltage(){
    Message message;
    message.setcommand(4);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
        double voltage = message.getdouble1();
        return voltage;
    }
}
void Robot::setTransVelMax(double vel){
    Message message;
    message.setcommand(5);
    message.setdouble1(vel);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
    }
}
void Robot::setRotVelMax(double vel){
    Message message;
    message.setcommand(6);
    message.setdouble1(vel);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
    }
}
double Robot::getStateOfCharge(){
    Message message;
    message.setcommand(7);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
        double stateOfCharge = message.getdouble1();
        return stateOfCharge;
    }
}
void Robot::setSafetyMode(bool mode){
    Message message;
    message.setcommand(10);
    message.setint1(mode);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
    }
}

bool Robot::getSatetyMode(){
    Message message;
    message.setcommand(11);
    message.send(*socket);
    message.clientRecive(&socket, context);
    if (message.getcommand() == -1){
        throw UnknownCommand();
    }
    else{
        message.setcommand(0);
        message.send(*socket);
        message.clientRecive(&socket, context);
        bool mode = (bool) message.getint1();
        return mode;
    }
}
