cmake_minimum_required(VERSION 3.3)

set(HADERS_DIR ./include)
set(SRC_DIR ./src)

set(HEADERS 
    ${HADERS_DIR}/club.hpp
    ${HADERS_DIR}/command.hpp
    ${HADERS_DIR}/eventHadler.hpp
    ${HADERS_DIR}/eventIds.hpp
    ${HADERS_DIR}/generatedEvent.hpp
    ${HADERS_DIR}/table.hpp
    ${HADERS_DIR}/client.hpp
    ${HADERS_DIR}/clientStatus.hpp)

set(SOURCES 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/club.cpp
    ${SRC_DIR}/command.cpp 
    ${SRC_DIR}/eventHandler.cpp 
    ${SRC_DIR}/generatedEvent.cpp 
    ${SRC_DIR}/table.cpp
    ${SRC_DIR}/client.cpp)

project(yadro_test_task LANGUAGES CXX)

add_executable(main ${SOURCES} ${HEADERS})