#include"../include/club.hpp"

Club::Club(int tablePrice, int numberOfTables, std::string startTime, std::string endTime):
            tablePrice(tablePrice), numberOfTables(numberOfTables), startTime(startTime), endTime(endTime),startTimeDivided(2), endTimeDivided(2){
                startTimeDivided = splitTimeToVector(startTime);
                endTimeDivided = splitTimeToVector(endTime);
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

bool Club::isClubWorking(std::string const& time){

}