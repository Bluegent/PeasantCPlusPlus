cmake_minimum_required(VERSION 3.10)
project(BigNumber)

add_subdirectory(Packages)

set(SOURCES src/Types/BigNumber.cpp src/main.cpp)
set(HEADERS src/Types/BigNumber.h)


include_directories(${OGRE_SDK_PATH}/include)
link_directories(${OGRE_SDK_PATH}/bin)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})