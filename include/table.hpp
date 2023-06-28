#ifndef TABlE
#define TABLE

#include<string>
#include<sstream>
#include<vector>

class Table{
    private:
        int tableId;
        int costPerHour;
        int workingHours;
        bool ifBusy;
        std::string startSession;
        std::string endSession;
        void countWorkingHours();

    public:
        Table(int tableId, int costPerHour, bool ifBusy);
        void setStatus(bool status, std::string const& time);
        bool isBusy();
        int countProfit();
};

#endif