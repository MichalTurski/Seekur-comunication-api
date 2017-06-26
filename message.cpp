#include "clientlib.h"

#define RETRY_TIMES	200
#define TIMEOUT_REQUEST	500

bool Robot::Message::send(zmq::socket_t & socket){
    zmq::message_t mess1 (&command, sizeof(int));
    socket.send(mess1, ZMQ_SNDMORE);
    zmq::message_t mess2 (&int1, sizeof(int));
    socket.send(mess2, ZMQ_SNDMORE);
    zmq::message_t mess3 (&int2, sizeof(int));
    socket.send(mess3, ZMQ_SNDMORE);
    zmq::message_t mess4 (&double1, sizeof(double));
    socket.send(mess4, ZMQ_SNDMORE);
    zmq::message_t mess5 (&double2, sizeof(double));
    bool rc = socket.send(mess5);
    return rc;
}
bool Robot::Message::serverRecive(zmq::socket_t & socket){
     zmq::message_t mess1;
     socket.recv(&mess1);
     memcpy(&command, mess1.data(), sizeof(int));
     mess1.rebuild();
     socket.recv(&mess1);
     memcpy(&int1, mess1.data(), sizeof(int));
     mess1.rebuild();
     socket.recv(&mess1);
     memcpy(&int2, mess1.data(), sizeof(int));
     mess1.rebuild();
     socket.recv(&mess1);
     memcpy(&double1, mess1.data(), sizeof(double));
     mess1.rebuild();
     socket.recv(&mess1);
     memcpy(&double2, mess1.data(), sizeof(double));
     return true;
}
int Robot::Message::clientRecive(zmq::socket_t ** pointer, zmq::context_t & context){
    zmq::message_t mess;
    for(int i = 0; i<RETRY_TIMES; ++i){
            zmq::pollitem_t items[] = {{**pointer, 0, ZMQ_POLLIN, 0}};
            zmq::poll (&items[0], 1, TIMEOUT_REQUEST);
            if(items[0].revents & ZMQ_POLLIN){
                    (*pointer)->recv(&mess);
                    memcpy(&command, mess.data(), sizeof(int));
                    mess.rebuild();
                    (*pointer)->recv(&mess);
                    memcpy(&int1, mess.data(), sizeof(int));
                    mess.rebuild();
                    (*pointer)->recv(&mess);
                    memcpy(&int2, mess.data(), sizeof(int));
                    mess.rebuild();
                    (*pointer)->recv(&mess);
                    memcpy(&double1, mess.data(), sizeof(double));
                    mess.rebuild();
                    (*pointer)->recv(&mess);
                    memcpy(&double2, mess.data(), sizeof(double));
                    return 0;
            }
            std::cerr<< "No response, retrying..."<<std::endl;//Destroying socket, creating it once more and resending message
            delete *pointer;
            *pointer = client_socket(context);
            send(**pointer);
    }
    throw CommunicationError();
    return 0;
}
zmq::socket_t * Robot::Message::client_socket (zmq::context_t & context){
    zmq::socket_t * client = new zmq::socket_t (context, ZMQ_REQ);
    client->connect ("tcp://10.0.127.32:5556");
    //  Configure socket to not wait at close time
    int linger = 0;
    client->setsockopt (ZMQ_LINGER, &linger, sizeof (linger));
    return client;
}
