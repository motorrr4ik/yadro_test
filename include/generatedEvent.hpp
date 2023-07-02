#ifndef GENERATED_EVENT
#define GENERATED_EVENT

#include<string>

class GeneratedEvent{
    private:
        std::string time;
        std::string operationId;
        std::string errorMessage;
        std::string clientName;
        int tableId;
        bool ifOperationOk;
    public:
        GeneratedEvent(std::string time, std::string  operationId, std::string errorMessage, std::string clientName, int tableId);
        GeneratedEvent(bool operationStatus);
        std::string toString();
        bool isOperationOk();
};

#endif