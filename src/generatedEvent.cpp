#include"../include/generatedEvent.hpp"

GeneratedEvent::GeneratedEvent(std::string time, std::string  operationId, std::string errorMessage, std::string clientName, int tableId)
            :time(time), operationId(operationId),errorMessage(errorMessage),clientName(clientName), tableId(tableId), ifOperationOk(false){}

GeneratedEvent::GeneratedEvent(bool operationStatus):ifOperationOk(operationStatus),
                    time(""), operationId(""),errorMessage(""),clientName(""), tableId(0){}

std::string GeneratedEvent::toString(){
    if(tableId){
        return time + " " + operationId + " " + clientName + " " + std::to_string(tableId);
    }else{
        return time + " " + operationId + " " + errorMessage;
    }
}

bool GeneratedEvent::isOperationOk(){
    return ifOperationOk;
}