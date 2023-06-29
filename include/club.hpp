#ifndef CLUB
#define CLUB

#include"table.hpp"
#include<vector>
#include<string>
#include<sstream>

class Club{
    private:
        int tablePrice;
        int numberOfTables;
        int numberOfClients;
        std::vector<Table> tables;
        std::string startTime;
        std::string endTime;
        std::vector<std::string> startTimeDivided;
        std::vector<std::string> endTimeDivided;
        std::vector<std::string>&  splitTimeToVector(std::string const& time);
        void initTables();

    public:
        Club(int tablePrice, int numberOfTables, std::string startTime, std::string endTime);
        bool isClubWorking(std::string const& time);
        bool ifAvailableTables();
        void serveClient();
};
#endif