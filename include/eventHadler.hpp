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

class eventHadler{
    private:
    Club club;
    Command command;
    std::ifstream fromFileStream;
    void startHandling();

    public:
        eventHadler(std::string const& path);
        std::thread start();
        std::vector<std::string> splitIncomingString(std::string const& str);
        Command parseStringToCommand(std::vector<std::string>& vec);
        void handleClubCommandResponse(GeneratedEvent& eventFromClub);
};
#endif