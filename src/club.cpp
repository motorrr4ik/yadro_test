#include"../include/club.hpp"

Club::Club():tablePrice(0), numberOfTables(0), startTime(""), endTime(""){};

// Данные метод разбиваем входящую строку со временем на вектор для доступа к часам и минутам
std::vector<std::string> Club::splitTimeToVector(std::string const& time){
    std::vector<std::string> timeVector;
    std::stringstream ssTime(time);
    std::string buffer;

    while(std::getline(ssTime, buffer, ':')){
        timeVector.push_back(buffer);
    }
    return timeVector;
}

// Инициализация столов при создании клуба
void Club::initTables(){
    for(int i = 0; i < numberOfTables; ++i){
        Table t(i+1,tablePrice,false);
        tables.push_back(t);
    }
}

// Установка цены за стол в час
void Club::setTablePrice(int price){
    tablePrice = price;
}

// Установка количества столов
void Club::setNumberOfTables(int number){
    numberOfTables = number;
}
// Установка времени открытия клуба
void Club::setStartTime(std::string const& time){
    startTime = time;
}
// Установка времени закрытия клуба
void Club::setEndTime(std::string const& time){
    endTime = time;
}

// Инициализация клуба
void Club::initClub(int price, int number, std::string const& startTime, std::string const& endTime){
    setTablePrice(price);
    setNumberOfTables(number);
    setStartTime(startTime);
    setEndTime(endTime);
    initTables();
    startTimeDivided = splitTimeToVector(startTime);
    endTimeDivided = splitTimeToVector(endTime);
}

// Проверка на работу клуба в данный момент времени
bool Club::isClubWorking(std::string const& time){
    std::vector<std::string> currentTimeVec = splitTimeToVector(time);
    int currentTimeHours = std::stoi(currentTimeVec[0]);
    int currentTimeMinutes = std::stoi(currentTimeVec[1]);

    int startTimeHours = std::stoi(startTimeDivided[0]);
    int startTimeMinutes = std::stoi(startTimeDivided[1]);
    int endTimeHours = std::stoi(endTimeDivided[0]);
    int endTimeMinutes = std::stoi(endTimeDivided[1]);

    int startTime = startTimeHours*60 + startTimeMinutes;
    int endTime = endTimeHours*60 + endTimeMinutes;
    int currentTime = currentTimeHours*60 + currentTimeMinutes;

    if ((startTime < currentTime) && (currentTime < endTime)){
        return true;
    }
    return false;
}
// Проверка на свободные столы, если они есть - возвращаемое значение true
bool Club::ifAvailableTables(){
    int counter = 0;
    for(int i = 0; i < numberOfTables; ++i){
        if(tables[i].isBusy()){
            ++counter;
        }
    }
    return !(counter == numberOfTables);
}

// Проверка определенного стола на свободное место, так как при инициализации
// столы были добавлены в порядке возрастания их id, то обращаться можно прямо 
// по идексу id-1
bool Club::ifTableIsFree(int idNum){
    if(!(idNum > numberOfTables) && !(tables[idNum - 1].isBusy())){
        return true;
    } 
    return false;
}

// Проверка, находится ли клиент с определнным именем в клубе
bool Club::isClientInClub(std::string const& clientName){
    for(int i = 0; i < numberOfTables; ++i){
        if((tables[i].getUserName() == clientName) || 
                        (clientNamesInQueue[i] == clientName)) return true;
    }
    return false;
}

//Постановка клиента в очередь
GeneratedEvent Club::putClientToQueue(std::string const& clientName, std::string const& time){
    if(clientNamesInQueue.size() == 3){
        return GeneratedEvent(time, "11","PlaceIsBusy", "",0);
    }else{
        clientNamesInQueue.push_back(clientName);
        return GeneratedEvent(true);
    }
}

// Обслуживание клиента - предоставление места за столом
GeneratedEvent Club::serveClient(std::string const& clientName, std::string const& time, int id){
    if(!isClubWorking(time)) return GeneratedEvent(time, "13", "NotOpenYet","",0);
    if(!isClientInClub(clientName)) return GeneratedEvent(time, "13", "ClientUnknown","",0);
    if(!ifAvailableTables()) return GeneratedEvent(time, "13", "PlaceIsBusy","",0);
    if(!ifTableIsFree(id)) return GeneratedEvent(time, "13", "PlaceIsBusy","",0);

    for (int i = 0 ; i < clientNamesInQueue.size(); ++i){
        if (clientNamesInQueue[i] == clientName) clientNamesInQueue.erase(
                            clientNamesInQueue.begin()+i, clientNamesInQueue.begin()+i+1);
    }

    if(!tables[id-1].isBusy()){
        tables[id-1].setStatus(true, time);
        tables[id-1].setUserName(clientName);
        return GeneratedEvent(true);
    }

}

// Обработка ухода клиента из-за стола. Если при этом очередь не пустая, то первый клиент из
// очереди сядет за только что освободившийся стол
GeneratedEvent Club::clientLeaves(std::string const& clientName, std::string const& time){
    if(!isClientInClub(clientName)) return GeneratedEvent(time, "13", "ClientUnknown","",0);
    int id = 1;
    for(int i = 0; i < numberOfTables; ++i){
        if(clientName == tables[i].getUserName()){
            id += i;
            tables[i].setStatus(false, time);
        }
    }
    if(!clientNamesInQueue.empty()){
        std::string queueClient = clientNamesInQueue.front();
        serveClient(queueClient, time, id);
        clientNamesInQueue.pop_front();
        return GeneratedEvent(time, "12", "", clientName, id);
    }
    return GeneratedEvent(true);
}

// Обработчик поступающих команд
GeneratedEvent Club::handleIncomingCommand(Command& command){
    switch (command.getOperationId())
    {
    case Ids::COME:
        if(!isClubWorking(command.getTime())) return GeneratedEvent(command.getTime(), "13", "NotOpenYet","",0);
        if(isClientInClub(command.getUserName())) return GeneratedEvent(command.getTime(), "13", "YouShallNotPass","",0);
        clientNamesInQueue.push_back(command.getUserName());
        return GeneratedEvent(true);
        break;
    case Ids::SIT:
        return serveClient(command.getUserName(), command.getTime(), command.getTableId());
        break;
    case Ids::WAIT:
        if(ifAvailableTables()) return GeneratedEvent(command.getTime(), "13", "ICanWaitNoLonger!","",0);
        return putClientToQueue(command.getUserName(), command.getTime());
        break;
    case Ids::LEAVE:
        return clientLeaves(command.getUserName(), command.getTime());
        break; 
    default:
        break;
    }
}
// Геттер для времени начала работы
std::string Club::getStartTime(){
    return startTime;
}
// Геттер для времени окончания работы
std::string Club::getEndTime(){
    return endTime;
}

//Метод обработки окончания рабочего дня
bool Club::endOfWorkDay(std::string const& time){
    std::vector<std::string> curTime = splitTimeToVector(time);
    int timeInMinutes = std::stoi(curTime[0])*60 + std::stoi(curTime[1]);
    int endTimeInMinutes = std::stoi(endTimeDivided[0])*60 + std::stoi(endTimeDivided[1]);

    if((timeInMinutes >= endTimeInMinutes) && (ifBusyTables() || !clientNamesInQueue.empty())){
        for(int i = 0; i < numberOfTables; ++i){
            if(tables[i].isBusy()){
                tables[i].setStatus(false, time);
                clientNamesInQueue.push_back(tables[i].getUserName());
            }
        }
        std::sort(clientNamesInQueue.begin(), clientNamesInQueue.end());
        for(int i = 0; i < clientNamesInQueue.size(); ++i){
            std::cout << GeneratedEvent(time, "11", "",clientNamesInQueue[i],0).toString() << std::endl;
        }
        std::cout << endTime << std::endl;
        for(int i = 0; i < numberOfTables; ++i){
            std::cout << tables[i].toString() << std::endl;
        }
        return true;
    }
    return false;
}