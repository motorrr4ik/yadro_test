#include"../include/club.hpp"

Club::Club():tablePrice(0), numberOfTables(0), numberOfClients(0), tables(1), startTime(""), endTime(""){};

std::vector<std::string> Club::splitTimeToVector(std::string const& time){
    std::vector<std::string> timeVector(2);
    std::stringstream ssTime(time);
    std::string buffer;

    while(std::getline(ssTime, buffer, ':')){
        timeVector.push_back(buffer);
    }
    return timeVector;
}

void Club::initTables(){
    for(int i = 0; i < numberOfTables; ++i){
        tables.push_back(Table(i+1,tablePrice,false));
    }
}

void Club::setTablePrice(int price){
    tablePrice = price;
}

void Club::setNumberOfTables(int number){
    numberOfTables = number;
}

void Club::setStartTime(std::string const& time){
    startTime = time;
}

void Club::setEndTime(std::string const& time){
    endTime = time;
}

void Club::initClub(int price, int number, std::string const& startTime, std::string const& endTime){
    setTablePrice(price);
    setNumberOfTables(number);
    setStartTime(startTime);
    setEndTime(endTime);
    initTables();
    startTimeDivided = splitTimeToVector(startTime);
    endTimeDivided = splitTimeToVector(endTime);
}

bool Club::isClubWorking(std::string const& time){
    std::vector<std::string> currentTime = splitTimeToVector(time);
    int currentTimeHours = std::stoi(currentTime[0]);
    int currentTimeMinutes = std::stoi(currentTime[1]);

    int startTimeHours = std::stoi(startTimeDivided[0]);
    int startTimeMinutes = std::stoi(startTimeDivided[1]);
    int endTimeHours = std::stoi(endTimeDivided[0]);
    int endTimeMinutes = std::stoi(endTimeDivided[1]);

    if(currentTimeHours < startTimeHours) return false;
    if(currentTimeMinutes < startTimeMinutes) return false;
    if(currentTimeHours > endTimeHours) return false;
    if(currentTimeMinutes > endTimeMinutes) return false;

    return true;
}

bool Club::ifAvailableTables(){
    int counter = 0;
    for(int i = 0; i < numberOfTables; ++i){
        if(tables[i].isBusy()){
            ++counter;
        }
    }
    return !counter == numberOfTables;
}

bool Club::ifTableIsFree(int idNum){
    for(int i = 0; i < numberOfTables; ++i){
        if((tables[i].getTableId() == idNum) && !tables[i].isBusy()){
            return true;
        }
    }
    return false;
}

bool Club::isClientInClub(std::string const& clientName){
    for(int i = 0; i < numberOfTables; ++i){
        if((tables[i].getUserName() == clientName) || 
                        (clientNamesInQueue[i] == clientName)) return true;
    }
    return false;
}

GeneratedEvent Club::putClientToQueue(std::string const& clientName, std::string const& time){
    if(clientNamesInQueue.size() == 3){
        return GeneratedEvent(time, "11","PlaceIsBusy", "",0);
    }else{
        clientNamesInQueue.push_back(clientName);
        return GeneratedEvent(true);
    }
}

GeneratedEvent Club::serveClient(std::string const& clientName, std::string const& time){
    if(!isClientInClub) return GeneratedEvent(time, "13", "ClientUnknown","",0);
    if(!isClubWorking(time)) return GeneratedEvent(time, "13", "NotOpenYet","",0);
    if(!ifAvailableTables) return GeneratedEvent(time, "13", "PlaceIsBusy","",0);

    for(int i = 0; i < numberOfTables; ++i){
        if(!tables[i].isBusy()){
            tables[i].setStatus(true, time);
            tables[i].setUserName(clientName);
            ++numberOfClients;
            return GeneratedEvent(true);
        }
    }
}

GeneratedEvent Club::clientLeaves(std::string const& clientName, std::string const& time){
    if(!isClientInClub) return GeneratedEvent(time, "13", "ClientUnknown","",0);
    for(int i = 0; i < numberOfTables; ++i){
        if(clientName == tables[i].getUserName()){
            tables[i].setStatus(false, time);
            --numberOfClients;
        }
    }

    if(!clientNamesInQueue.empty()){
        std::string queueClient = clientNamesInQueue.front();
        serveClient(queueClient, time);
        clientNamesInQueue.pop_front();
        return GeneratedEvent(time, "12", "", clientName, 0);
    }
    return GeneratedEvent(true);
}

GeneratedEvent Club::handleIncomingCommand(Command& command){

    switch (command.getOperationId())
    {
    case Ids::COME:
        if(!isClubWorking) return GeneratedEvent(command.getTime(), "13", "NotOpenYet","",0);
        if(isClientInClub) return GeneratedEvent(command.getTime(), "13", "YouShallNotPass","",0);\
        break;
    case Ids::SIT:
        return serveClient(command.getUserName(), command.getTime());
        break;
    case Ids::WAIT:
        return putClientToQueue(command.getUserName(), command.getTime());
        break;
    case Ids::LEAVE:
        return clientLeaves(command.getUserName(), command.getTime());
        break; 
    default:
        break;
    }
}
