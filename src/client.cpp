#include"../include/client.hpp"

Client::Client(std::string const& name):clientName(name){}

void Client::setStatus(int num){
    switch (num)
    {
    case 1:
        status = clientStatus::IN_CLUB;
        break;
    case 2:
        status = clientStatus::AT_TABLE;
        break;
    case 3:
        status = clientStatus::IN_QUEUE;
        break;
    default:
        break;
    }
}

int Client::getStatus(){
    return static_cast<int>(status);
}

std::string Client::getName(){
    return clientName;
}
