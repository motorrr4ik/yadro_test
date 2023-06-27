#ifndef CLUB
#define CLUB

#include"table.hpp"
#include<vector>
#include<string>

class Club{
    private:
        int tablePrice;
        int numberOfTables;
        int numberOfClients;
        std::vector<Table> tables;
        std::string startTime;
        std::string endTime;
    public:
        bool ifTableBusy(Table const& table);
        bool isClubWorking(std::string const& time);
        bool ifAvailableTables();



};

#endif