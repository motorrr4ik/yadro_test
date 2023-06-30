#include"../include/command.hpp"

Command::Command(std::string const& time, std::string const& userName, Ids id, int tableId = 0):time(time), userName(userName),id(id),tableId(tableId){}

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

std::string Command::fromIdToString(Ids id){
    switch (id)
    {
    case Ids::COME:
        return "1";
    case Ids::SIT:
        return "2";
    case Ids::WAIT:
        return "3";
    case Ids::LEAVE:
        return "4";
    case Ids::LEAVE_AT_THE_AND:
        return "11";
    case Ids::SIT_AFTER_FREE:
        return "12";
    case Ids::ERROR:
        return "13";
    default:
        return "0";
    }
}

std::string Command::toString(){
    if(!tableId){
        return time + " " + fromIdToString(id) + " " + userName;
    }else{
        return time + " " + fromIdToString(id) + " " + userName + " " + std::to_string(tableId);
    }
}
