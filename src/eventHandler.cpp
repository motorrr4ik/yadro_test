#include"../include/eventHadler.hpp"

eventHadler::eventHadler(std::string const& str):fromFileStream(str), flag(true){};

// Метод для разбивки входящего сообщения на компоненты для последующего создания
// объекта команды с определенными параметрами
std::vector<std::string> eventHadler::splitIncomingString(std::string const& str){
    std::stringstream incomeStringStream(str);
    std::vector<std::string> resultVector;
    std::string buffer;

    while(std::getline(incomeStringStream, buffer, ' ')){
        resultVector.push_back(buffer);
    }
    return resultVector;
}

// Метод для запуска обработчика событий. Сначала считываются 3 первые строчки для
// инициализации клуба, затем считываются остальные команды. Во время считывания 
// происходит проверка входящих строк на соответствие шаблону, создание команды,
// проверка на открытость/закрытость клуба, отправка команды клубу, получение
// ответа от клуба и обработка этого ответа.
void eventHadler::startHandling(){
    std::string buffer;
    std::vector<std::string> initParams;
    std::vector<std::string> bufferVec;
    if(fromFileStream.good() && fromFileStream.is_open()){
        for(int i = 0; i < 3; ++i){
            std::getline(fromFileStream, buffer);
            if(!stringMatchesPattern(buffer)){
                flag = stringMatchesPattern(buffer);
                break;
            }
            initParams.push_back(buffer);
        }
    }
    if(!flag) return; // Данный флаг сигнализирует о неправильном формате строки

    std::vector<std::string> time;
    time = splitIncomingString(initParams[1]);
    club.initClub(std::stoi(initParams[2]), std::stoi(initParams[0]), time[0], time[1]);

    std::cout << club.getStartTime() << std::endl;
    if(fromFileStream.good() && fromFileStream.is_open()){
        while(!fromFileStream.eof()){
            std::getline(fromFileStream, buffer);
            std::cout << buffer << std::endl;
            if(!stringMatchesPattern(buffer)){
                flag = stringMatchesPattern(buffer);
                break;
            }
            bufferVec = splitIncomingString(buffer);
            workDayStatusFlag = club.endOfWorkDay(bufferVec[0]);
            command = parseStringToCommand(bufferVec);
            GeneratedEvent event = club.handleIncomingCommand(command);
            handleClubCommandResponse(event);
        }
    }
    if(!flag) return;
    if(!workDayStatusFlag) club.endOfWorkDay(club.getEndTime()); //Если клуб не завершает свою работу в процессе обработки файла, завершение просходит после
}

// Запуск потока обработчика
std::thread eventHadler::start(){
    std::thread t1(&eventHadler::startHandling, this);
    return t1;
}

// Парсинг полученной строки в команду для передачи в объект клуба
Command eventHadler::parseStringToCommand(std::vector<std::string>& vec){
    Command newCommand;
    newCommand.setTime(vec[0]);
    newCommand.setOperationId(std::stoi(vec[1]));
    newCommand.setUserName(vec[2]);
    if(vec.size() > 3){
        newCommand.setTableId(std::stoi(vec[3]));
    }else{
        newCommand.setTableId(0);
    }
    return newCommand;
}

// Обработчик сгенерированных событий - ответов на команды от клуба
void eventHadler::handleClubCommandResponse(GeneratedEvent& eventFromClub){
    if(!eventFromClub.isOperationOk()){
        std::cout << eventFromClub.toString() << std::endl;
    }
}

// Проверка входящих строк на правильность с помощью регулярных выражений
bool eventHadler::stringMatchesPattern(std::string const& str){
    std::regex num("[0-9]+");
    std::regex time("[0-9]{2}:[0-9]{2} [0-9]{2}:[0-9]{2}");
    std::regex command("[0-9]{2}:[0-9]{2} [0-9]{1,2} [a-zA-Z0-9_-]+ ?[0-9]*");
    if(std::regex_match(str, num) || std::regex_match(str, time) || std::regex_match(str, command)) return true;
    return false;
}