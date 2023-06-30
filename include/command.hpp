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
        Command();
        Command(std::string const& time, std::string const& userName, Ids id, int tableId = 0);
        std::string getTime();
        void setTime(std::string const& newTime);
        std::string getUserName();
        void setUserName(std::string const& newName);
        Ids getOperationId();
        void setOperationId(int idNum);
        int getTableId();
        void setTableId(int newTableId);
};
#endif