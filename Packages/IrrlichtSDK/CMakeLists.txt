set(IRRLICHT_PATH "Irrlicht")
set(IRRLICHT_VER "VS" CACHE STRING "IRRLICHT download version")
set(IRRLICHT_DOWNLOAD_DEST ${CMAKE_CURRENT_LIST_DIR}/IRRLICHT_${IRRLICHT_VER}.7z)
message(${IRRLICHT_VER})
if(NOT EXISTS  ${IRRLICHT_DOWNLOAD_DEST})
	if(${IRRLICHT_VER} STREQUAL "VS")
		file(DOWNLOAD 
		"http://serverfiles.hi2.ro/Peasants/Irrlicht_MSVC.7z" ${IRRLICHT_DOWNLOAD_DEST})
		
	else()
		message("You're shit out of luck, budddy.")
	endif()
endif()

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/${IRRLICHT_PATH})
    find_program(7Z_EXE 7z PATHS "$ENV{ProgramFiles}/7-Zip") 
	if(7Z_EXE)
		set(ZIP_ARGS x -o${IRRLICHT_PATH} -y ${IRRLICHT_DOWNLOAD_DEST})
		execute_process(COMMAND ${7Z_EXE} ${ZIP_ARGS} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
	endif(7Z_EXE)
endif()


set(IRRLICHT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/${IRRLICHT_PATH} CACHE FILEPATH "Path to IRRLICHT sdk root.")