#include"../include/table.hpp"

Table::Table(int tableId, int costPerHour, bool ifBusy):tableId(tableId), costPerHour(costPerHour), ifBusy(ifBusy), workingHours(0){};

void Table::setStatus(bool status, std::string const& time){
    ifBusy = status;
    if(ifBusy){
        startSession = time;
    }else{
        endSession = time;
        countWorkingHours();
    }
}

bool Table::isBusy(){
    return ifBusy;
}

int Table::countProfit(){
    return workingHours * costPerHour;
}

void Table::countWorkingHours(){
    std::vector<std::string> startTimeDivided(2);
    std::vector<std::string> endTimeDivided(2);
    std::stringstream ssStart(startSession);
    std::stringstream ssEnd(endSession);
    std::string buffer;
    int startHour = 0;
    int endHour = 0;

    while(std::getline(ssStart, buffer, ':')){
        startTimeDivided.push_back(buffer);
    }

    while(std::getline(ssEnd, buffer, ':')){
        endTimeDivided.push_back(buffer);
    }

    startHour = stoi(startTimeDivided[0]);
    endHour = stoi(endTimeDivided[0]);

    if(!startTimeDivided[1].empty()){
        ++startHour;
    }

    if(!endTimeDivided[1].empty()){
        ++endHour;
    }

    workingHours = workingHours + (startHour - endHour);

}

int Table::getTableId(){
    return tableId;
}

void Table::setUserName(std::string const& name){
    currentUserName = name;
}
