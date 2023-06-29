#ifndef COMMAND
#define COMMAND

#include<eventIds.hpp>
#include<string>

class Command{
    private:
    std::string time;
    std::string userName;
    Ids id;
    int tableId;

    public:
        Command(std::string const& time, std::string const& userName, Ids id, int tableId = 0);
        std::string getTime();
        std::string getUserName();
        Ids getOperationId();
        int getTableId();



};
#endif