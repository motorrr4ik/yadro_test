#include"../include/eventHadler.hpp"



int main(int argc, char** argv){
    std::string pathToFile;
    if (argc > 1){
        pathToFile = argv[1];
        std::cout << pathToFile << std::endl;
    }
    if(std::fstream(pathToFile).good()){
        eventHadler handler(pathToFile);
        std::thread t = handler.start();
        t.join();
    }else {
        std::cout << "Invalid filepath!" << std::endl;
    }
    return 0;
}