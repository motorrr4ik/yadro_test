#include"../include/club.hpp"

Club::Club(int tablePrice, int numberOfTables, std::string startTime, std::string endTime):
            tablePrice(tablePrice), numberOfTables(numberOfTables), startTime(startTime), endTime(endTime),startTimeDivided(2), endTimeDivided(2){
                startTimeDivided = splitTimeToVector(startTime);
                endTimeDivided = splitTimeToVector(endTime);
                initTables();
}


std::vector<std::string>& Club::splitTimeToVector(std::string const& time){
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

bool Club::isClubWorking(std::string const& time){
    std::vector<std::string> currentTime = splitTimeToVector(time);
    int currentTimeHours = stoi(currentTime[0]);
    int currentTimeMinutes = stoi(currentTime[1]);

    int startTimeHours = stoi(startTimeDivided[0]);
    int startTimeMinutes = stoi(startTimeDivided[1]);
    int endTimeHours = stoi(endTimeDivided[0]);
    int endTimeMinutes = stoi(endTimeDivided[1]);

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
