cmake_minimum_required(VERSION 3.10)
project(BigNumber)

SET(SOURCES src/BigNumber.cpp src/main.cpp)
SET(HEADERS src/BigNumber.h)
SET(OGRE_SDK_PATH "Packages/Ogre" CACHE FILEPATH "Path to ogre sdk root.")

include_directories(${OGRE_SDK_PATH}/include)
link_directories(${OGRE_SDK_PATH}/bin)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})