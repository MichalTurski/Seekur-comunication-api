#ifndef MT_EXCEPTIONS
#define MT_EXCEPTIONS

#include <exception>
#include <string>
class UnknownCommand: public std::runtime_error {
public:
    UnknownCommand():runtime_error("Unknown command"){
        msg = "Such a command doesn't exist";
    }
    virtual ~UnknownCommand() throw(){}
    virtual const char* what() const throw()
      {
        return msg.c_str();
      }
private:
    std::string msg;
};
class CommunicationError: public std::runtime_error{
public:
    CommunicationError():runtime_error("Problems with communication"){
        msg = "Didn't manage to comunicate with the server";
    }
    virtual ~CommunicationError() throw(){}
    virtual const char* what() const throw()
      {
        return msg.c_str();
      }
private:
    std::string msg;
};
#endif //MT_EXCEPTIONS
