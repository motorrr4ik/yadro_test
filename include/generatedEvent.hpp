#ifndef GENERATED_EVENT
#define GENERATED_EVENT

#include<string>

/* Класс генерируемых событий. Используется клубом в качестве ответа обработчику на выполненную команду.
Имеется 2 конструктора:
            - Первый отвечается за событие с индексами 11, 12, 13, то есть предполагает какое-то действие
            - Второй только с булевой переменной (по умолчанию false), который используется в качестве сигнала 
            о том, что операция выполнена успешно
*/
class GeneratedEvent{
    private:
        std::string time;
        std::string operationId;
        std::string errorMessage;
        std::string clientName;
        int tableId;
        bool ifOperationOk;
    public:
        GeneratedEvent(std::string const& time, std::string const& operationId, std::string const& errorMessage, std::string const& clientName, int tableId);
        GeneratedEvent(bool operationStatus);
        std::string toString();
        bool isOperationOk();
};

#endif