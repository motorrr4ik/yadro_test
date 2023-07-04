#include"../include/table.hpp"

Table::Table(int tableId, int costPerHour, bool ifBusy):tableId(tableId), costPerHour(costPerHour), ifBusy(ifBusy), workingHours(0), allWorkHours(0), allWorkMinutes(0){};

// Установка текущего статуса стола занят/не занят. При установке статуса не занят
// просиходит подсчет отработанного времени
void Table::setStatus(bool status, std::string const& time){
    ifBusy = status;
    if(ifBusy){
        startSession = time;
    }else{
        endSession = time;
        countWorkingHours();
    }
}

// Геттер для получения текущего статуса стола
bool Table::isBusy(){
    return ifBusy;
}

// Подсчет прибыли
int Table::countProfit(){
    return workingHours * costPerHour;
}

// Подсчет времени работы
void Table::countWorkingHours(){
    std::vector<std::string> startTimeDivided;
    std::vector<std::string> endTimeDivided;
    std::stringstream ssStart(startSession);
    std::stringstream ssEnd(endSession);
    std::string buffer;
    int startHour = 0;
    int startMinute = 0;
    int endHour = 0;
    int endMinute = 0;
    int differenceH = 0;
    int differenceM = 0;

    while(std::getline(ssStart, buffer, ':')){
        startTimeDivided.push_back(buffer);
    }

    while(std::getline(ssEnd, buffer, ':')){
        endTimeDivided.push_back(buffer);
    }

    startHour = std::stoi(startTimeDivided[0]);
    endHour = std::stoi(endTimeDivided[0]);
    startMinute = std::stoi(startTimeDivided[1]);
    endMinute = std::stoi(endTimeDivided[1]);

    differenceH = endHour - startHour;
    differenceM = endMinute - startMinute;
    allWorkHours += differenceH;
    workingHours += differenceH;

    if(differenceM < 0){
        --allWorkHours;
        allWorkMinutes = 60 + differenceM;
    }
    if(differenceM > 0){
        allWorkMinutes += differenceM;
        ++workingHours;
    }

}

// Геттер для id стола
int Table::getTableId(){
    return tableId;
}

// Сеттер для имени клиента
void Table::setUserName(std::string const& name){
    currentUserName = name;
}

// Геттер для имени клиента
std::string Table::getUserName(){
    return currentUserName;
}

// Вывод строки с прибылью и временем
std::string Table::toString(){
    std::string res = std::to_string(tableId) + " " + std::to_string(countProfit())
                 + " " +  std::to_string(allWorkHours) + ":";
    if(allWorkMinutes < 10 ){
        res = res + "0" + std::to_string(allWorkMinutes);
    }else{
        res = res + std::to_string(allWorkMinutes);
    }
    return res;
}
