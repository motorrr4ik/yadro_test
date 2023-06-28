#include"../include/table.hpp"

Table::Table(int tableId, int costPerHour, bool ifBusy):tableId(tableId), costPerHour(costPerHour), ifBusy(ifBusy), workingHours(0){};

void Table::setStatus(bool status){
    ifBusy = status;
}

bool Table::isBusy(){
    return ifBusy;
}

int Table::countProfit(){
    return workingHours * costPerHour;
}

