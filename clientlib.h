#ifndef CLIENT_LIB
#define CLIENT_LIB

#include <zmq.hpp>
#include <unistd.h>
#include <string>
#include <iostream>
#include <curses.h>
//#include "message.h"
#include "exceptions.h"

class Robot{
public:
    Robot();
    ~Robot();
    void moveForward(int mm);
    void moveToObstacle(int distance);
    double checkRangeDevices(double& angleOut, double angleIn1 = -45, double angleIn2 = 45);
    double getBatteryVoltage();
    void setTransVelMax(double vel);
    void setRotVelMax(double vel);
    double getStateOfCharge();
    void turn(double angle);
    void deltaTurn(double angle);
    void setSafetyMode(bool mode);
    bool getSatetyMode();
private:
    zmq::context_t context;
    zmq::socket_t * socket;
    class Message{
        //friend Robot;
    public:
        Message(){}
        bool send(zmq::socket_t & socket);
        bool serverRecive(zmq::socket_t & socket);
        int clientRecive(zmq::socket_t ** pointer, zmq::context_t & context);
        inline void setcommand(int a){command = a;}
        inline void setint1(int a){int1 = a;}
        inline void setint2(int a){int2 = a;}
        inline void setdouble1(double a){double1 = a;}
        inline void setdouble2(double a){double2 = a;}
        inline int getcommand(){return command;}
        inline int getint1(){return int1;}
        inline int getint2(){return int2;}
        inline double getdouble1(){return double1;}
        inline double getdouble2(){return double2;}
        static zmq::socket_t * client_socket (zmq::context_t & context);

    private:
        int command;
        double double1;
        double double2;
        int int1;
        int int2;

    };
};

#endif //CLIENT_LIB
