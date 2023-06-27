#ifndef TABlE
#define TABLE

class Table{
    private:
        int costPerHour;
        int workingHours;
        bool ifBusy;

    public:
        Table();
        void setStatus();
        bool isBusy();
        void countWorkingHours();
        void countProfit();
};

#endif