cmake_minimum_required(VERSION 3.5)
project(Peasants)

add_subdirectory(Packages)

set(SOURCES src/Types/BigNumber.cpp 
	src/demo.cpp)
set(HEADERS src/Types/BigNumber.h)

set(OGRE_DIR ${OGRE_SDK_PATH}/CMake CACHE FILEPATH "Path to ogre")

LIST(APPEND CMAKE_MODULE_PATH ${OGRE_DIR}) 
SET(SDL2_PATH ${OGRE_SDK_PATH} CACHE FILEPATH "Path to SDL2")
find_package(OGRE 1.10 REQUIRED) 


include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OGRE_SDK_PATH}}/include)
include_directories(${OGRE_INCLUDE_DIRS})

message(${OGRE_INCLUDE_DIRS})
message(${OGRE_LIBRARY_DIRS})
message(${OGRE_LIBRARIES})

link_directories(${OGRE_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} ${OGRE_PLUGIN_LIBRARIES} ${SDL2_LIBRARY} OgreBites)