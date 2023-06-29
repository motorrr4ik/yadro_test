#include"../include/command.hpp"

Command::Command(std::string const& time, std::string const& userName, Ids id, int tableId = 0):time(time), userName(userName),id(id),tableId(tableId){}

std::string Command::getTime(){
    return time;
}

std::string Command::getUserName(){
    return userName;
}

Ids Command::getOperationId(){
    return id;
}

int Command::getTableId(){
    return tableId;
}