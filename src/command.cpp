#include"../include/command.hpp"

Command::Command(std::string const& time, std::string const& userName, Ids id, int tableId):time(time), userName(userName),id(id),tableId(tableId){}

Command::Command():time(""), userName(""), tableId(0){}

std::string Command::getTime(){
    return time;
}

void Command::setTime(std::string const& newTime){
    time = newTime;
}

std::string Command::getUserName(){
    return userName;
}

void Command::setUserName(std::string const& newName){
    userName = newName;
}

Ids Command::getOperationId(){
    return id;
}

void Command::setOperationId(int idNum){
    switch (idNum)
    {
    case 1:
        id = Ids::COME;
        break;
     case 2:
        id = Ids::SIT;
        break;
     case 3:
        id = Ids::WAIT;
        break;
    case 4:
        id = Ids::LEAVE;
        break;
     case 11:
        id = Ids::LEAVE_AT_THE_AND;
        break;
     case 12:
        id = Ids::SIT_AFTER_FREE;
        break;
     case 13:
        id = Ids::ERROR;
        break;            
    default:
        break;
    }
}

int Command::getTableId(){
    return tableId;
}

void Command::setTableId(int newTableId){
    tableId = newTableId;
}

