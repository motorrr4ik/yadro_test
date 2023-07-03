#ifndef HANDLER
#define HANDLER

#include"club.hpp"
#include"command.hpp"
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<regex>

class eventHadler{
    private:
    Club club;
    Command command;
    std::ifstream fromFileStream;
    bool flag;
    bool workDayStatusFlag;
    void startHandling();

    public:
        eventHadler(std::string const& path);
        std::thread start();
        std::vector<std::string> splitIncomingString(std::string const& str);
        Command parseStringToCommand(std::vector<std::string>& vec);
        void handleClubCommandResponse(GeneratedEvent& eventFromClub);
        bool stringMatchesPattern(std::string const& str);
};
#endif