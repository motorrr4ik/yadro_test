#ifndef TABLE
#define TABLE

#include<string>
#include<sstream>
#include<vector>
/* Класс стола. Данный класс рассчитывает время работы стола и прибыль, которую он приносит,
   предоставляет доступ к своим полям для корректной обработки событий в клубе
*/
class Table{
    private:
        int tableId;
        int costPerHour;
        int workingHours; // Переменная для подсчета округленных часов работы
        bool ifBusy;
        std::string currentUserName;
        std::string startSession;
        std::string endSession;
        int allWorkHours;
        int allWorkMinutes;
        void countWorkingHours();
    public:
        Table(int tableId, int costPerHour, bool ifBusy);
        void setStatus(bool status, std::string const& time);
        bool isBusy();
        int countProfit();
        int getTableId();
        void setUserName(std::string const& name);
        std::string getUserName();
        std::string toString();
};

#endif