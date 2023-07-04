#include"../include/generatedEvent.hpp"

GeneratedEvent::GeneratedEvent(std::string const& time, std::string const& operationId, std::string const& errorMessage, std::string const& clientName, int tableId)
            :time(time), operationId(operationId),errorMessage(errorMessage),clientName(clientName), tableId(tableId), ifOperationOk(false){}

GeneratedEvent::GeneratedEvent(bool operationStatus):ifOperationOk(operationStatus),
                    time(""), operationId(""),errorMessage(""),clientName(""), tableId(0){}

// Метод для вывода события в консоль в зависимости от того, какие поля инициализированы 
std::string GeneratedEvent::toString(){
    if(tableId){
        return time + " " + operationId + " " + clientName + " " + std::to_string(tableId);
    }else if(clientName.empty()){
        return time + " " + operationId + " " + errorMessage;
    }else{
        return time + " " + operationId + " " + clientName;
    }
}

// Метод для определения типа операции. Если true, то выводится ничего не будет,
// если false, то будет выведено сообщение сгенерированного события
bool GeneratedEvent::isOperationOk(){
    return ifOperationOk;
}