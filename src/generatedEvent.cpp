#include"../include/generatedEvent.hpp"

GeneratedEvent::GeneratedEvent(std::string const& time, std::string const& operationId, std::string const& errorMessage, std::string const& clientName, int tableId)
            :time(time), operationId(operationId),errorMessage(errorMessage),clientName(clientName), tableId(tableId), ifOperationOk(false){}

GeneratedEvent::GeneratedEvent(bool operationStatus):ifOperationOk(operationStatus),
                    time(""), operationId(""),errorMessage(""),clientName(""), tableId(0){}

std::string GeneratedEvent::toString(){
    if(tableId){
        return time + " " + operationId + " " + clientName + " " + std::to_string(tableId);
    }else if(clientName.empty()){
        return time + " " + operationId + " " + errorMessage;
    }else{
        return time + " " + operationId + " " + clientName;
    }
}
bool GeneratedEvent::isOperationOk(){
    return ifOperationOk;
}