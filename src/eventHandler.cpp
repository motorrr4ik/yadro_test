#include"../include/eventHadler.hpp"

eventHadler::eventHadler(std::string const& str, bool flag):fromFileStream(str), flag(flag){};

std::vector<std::string> eventHadler::splitIncomingString(std::string const& str){
    std::stringstream incomeStringStream(str);
    std::vector<std::string> resultVector;
    std::string buffer;

    while(std::getline(incomeStringStream, buffer, ' ')){
        resultVector.push_back(buffer);
    }
    return resultVector;
}

void eventHadler::startHandling(){
    std::string buffer;
    std::vector<std::string> initParams;
    if(fromFileStream.is_open()){
        for(int i = 0; i < 3; ++i){
            std::getline(fromFileStream, buffer);
            if(!stringMatchesPattern(buffer)){
                flag = stringMatchesPattern(buffer);
                break;
            }
            initParams.push_back(buffer);
        }
    }
    if(!flag) return;

    std::vector<std::string> time;
    time = splitIncomingString(initParams[1]);
    club.initClub(std::stoi(initParams[2]), std::stoi(initParams[0]), time[0], time[1]);

    if(fromFileStream.is_open()){
        while(fromFileStream){
            std::getline(fromFileStream, buffer);
            std::cout << buffer << std::endl;
            if(!stringMatchesPattern(buffer)){
                flag = stringMatchesPattern(buffer);
                break;
            }
            std::vector<std::string> bufferVec = splitIncomingString(buffer);
            command = parseStringToCommand(bufferVec);
            GeneratedEvent event = club.handleIncomingCommand(command);
            handleClubCommandResponse(event);
        }
    }
    if(!flag) return;
}

std::thread eventHadler::start(){
    std::thread t1(&eventHadler::startHandling, this);
    return t1;
}

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

void eventHadler::handleClubCommandResponse(GeneratedEvent& eventFromClub){
    if(!eventFromClub.isOperationOk()){
        std::cout << eventFromClub.toString() << std::endl;
    }
}

bool eventHadler::stringMatchesPattern(std::string const& str){
    std::regex num("[0-9]+");
    std::regex time("[0-9]{2}:[0-9]{2} [0-9]{2}:[0-9]{2}");
    std::regex command("[0-9]{2}:[0-9]{2} [0-9]{1,2} [a-zA-Z0-9]+ ?[0-9]*");
    if(std::regex_match(str, num) || std::regex_match(str, time) || std::regex_match(str, command)) return true;
    return false;
}