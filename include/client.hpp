#ifndef CLIENT
#define CLIENT

#include<string>
#include"clientStatus.hpp"

class Client{
    private:
        std::string clientName;
        clientStatus status;
    public:
        Client(std::string const& name);
        void setStatus(int num);
        int getStatus();
        std::string getName();
};
#endif