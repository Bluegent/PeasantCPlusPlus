cmake_minimum_required(VERSION 3.5)
project(Peasants)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.h)

set(OGRE_DIR ${OGRE_SDK_PATH}/CMake CACHE FILEPATH "Path to ogre")

LIST(APPEND CMAKE_MODULE_PATH ${OGRE_DIR}) 
SET(SDL2_PATH ${OGRE_SDK_PATH} CACHE FILEPATH "Path to SDL2")
find_package(OGRE 1.10 REQUIRED) 


include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OGRE_SDK_PATH}}/include)
include_directories(${OGRE_INCLUDE_DIRS})

link_directories(${OGRE_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} ${OGRE_PLUGIN_LIBRARIES} ${SDL2_LIBRARY} OgreBites)