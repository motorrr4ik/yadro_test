#ifndef TABlE
#define TABLE

class Table{
    private:
        int tableId;
        int costPerHour;
        int workingHours;
        bool ifBusy;

    public:
        Table(int tableId, int costPerHour, bool ifBusy);
        void setStatus(bool status);
        bool isBusy();
        void countWorkingHours();
        int countProfit();
};

#endif