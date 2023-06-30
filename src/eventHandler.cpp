#include"../include/eventHadler.hpp"

eventHadler::eventHadler(std::string const& str):fromFileStream(str){};

std::vector<std::string> eventHadler::splitIncomingString(std::string const& str){
    std::stringstream incomeStringStream(str);
    std::vector<std::string> resultVector(3);
    std::string buffer;

    while(std::getline(incomeStringStream, buffer, ' ')){
        resultVector.push_back(buffer);
    }
    return resultVector;
}

void eventHadler::startHandling(){
    std::string buffer;
    std::vector<std::string> initParams(3);
    if(fromFileStream.is_open()){
        for(int i = 0; i < 3; ++i){
            std::getline(fromFileStream, buffer);
            initParams.push_back(buffer);
        }
    }

    std::vector<std::string> time(2);
    time = splitIncomingString(initParams[1]);
    club.initClub(std::stoi(initParams[0]), std::stoi(initParams[2]), time[0], time[1]);

    if(fromFileStream.is_open()){
        while(fromFileStream){
            std::getline(fromFileStream, buffer);
            std::cout << buffer << std::endl;
            std::vector<std::string> bufferVec = splitIncomingString(buffer);
            parseStringToCommand(bufferVec);
            GeneratedEvent event = club.handleIncomingCommand(command);
            handleClubCommandResponse(event);
        }
    }
}

std::thread eventHadler::start(){
    std::thread t1(&eventHadler::startHandling, this);
    return t1;
}

void eventHadler::parseStringToCommand(std::vector<std::string>& vec){
    command.setTime(vec[0]);
    command.setOperationId(std::stoi(vec[1]));
    command.setUserName(vec[2]);
    if(vec.size() > 3){
        command.setTableId(std::stoi(vec[3]));
    }else{
        command.setTableId(0);
    }
}

void eventHadler::handleClubCommandResponse(GeneratedEvent& eventFromClub){
    if(!eventFromClub.isOperationOk()){
        std::cout << eventFromClub.toString() << std::endl;
    }
}