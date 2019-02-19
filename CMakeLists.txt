cmake_minimum_required(VERSION 3.10)
project(doomfire LANGUAGES CXX)


#set the C++ standard to be used
# set (CMAKE_CXX_STANDARD 11)

#set source files

#look for SFML and add it
# set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")
find_package (SFML REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})

#we add the executable of the program
add_executable (main main.cc)
target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})