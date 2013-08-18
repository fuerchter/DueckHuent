cmake_minimum_required(VERSION 2.8)

project(DueckHuent)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SFML REQUIRED COMPONENTS system window graphics audio)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	set(LIBRARIES ${LIBRARIES} ${SFML_LIBRARIES})
endif()

find_package(SFRM REQUIRED)

if(SFRM_FOUND)
	include_directories(${SFRM_INCLUDE_DIR})
	set(LIBRARIES ${LIBRARIES} ${SFRM_LIBRARIES})
endif()

#Folders to be searched
set(FOLDERS "src")

#Adding source files in each of the FOLDERS to EXECUTABLES
foreach(FOLDER ${FOLDERS})
	file(GLOB GLOBFILES "${FOLDER}/*.cpp")
	set(EXECUTABLES ${EXECUTABLES} ${GLOBFILES})
endforeach(FOLDER)

add_executable(DueckHuent ${EXECUTABLES})
target_link_libraries(DueckHuent ${LIBRARIES})

install(TARGETS DueckHuent DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY "assets" DESTINATION ${CMAKE_INSTALL_PREFIX})