#ifndef CLUB
#define CLUB

#include"table.hpp"
#include"command.hpp"
#include"generatedEvent.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<queue>

class Club{
    private:
        int tablePrice;
        int numberOfTables;
        int numberOfClients;
        std::vector<Table> tables;
        std::deque<std::string> clientNamesInQueue;
        std::string startTime;
        std::string endTime;
        std::vector<std::string> startTimeDivided;
        std::vector<std::string> endTimeDivided;
        std::vector<std::string>  splitTimeToVector(std::string const& time);
        void initTables();
        void setTablePrice(int price);
        void setNumberOfTables(int number);
        void setStartTime(std::string const& time);
        void setEndTime(std::string const& time);

    public:
        Club();
        void initClub(int price, int number, std::string const& startTime, std::string const& endTime);
        bool isClubWorking(std::string const& time);
        bool ifAvailableTables();
        bool ifTableIsFree(int idNum);
        bool isClientInClub(std::string const& clientName);
        GeneratedEvent putClientToQueue(std::string const& clientName, std::string const& time);
        GeneratedEvent serveClient(std::string const& clientName, std::string const& time, int id);
        GeneratedEvent clientLeaves(std::string const& clientName, std::string const& time);
        GeneratedEvent handleIncomingCommand(Command& command);
};
#endif