cmake_minimum_required(VERSION 3.5)
project(Peasants)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.h)

add_subdirectory(Packages)
set(IRRLICHT_MODULE_DIR ${IRRLICHT_SOURCE_DIR}/CMake)
LIST(APPEND CMAKE_MODULE_PATH ${IRRLICHT_MODULE_DIR}) 
find_package(Irrlicht REQUIRED)

include_directories(src ${IRRLICHT_INCLUDE_DIR})
link_directories(${IRRLICHT_SOURCE_DIR_LIBS})
add_executable(${PROJECT_NAME} ${HEADER_FILES}  ${SOURCE_FILES})
target_link_libraries( ${PROJECT_NAME} ${IRRLICHT_LIBRARY})