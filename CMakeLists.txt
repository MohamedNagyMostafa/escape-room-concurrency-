cmake_minimum_required(VERSION 3.26)
project(testing)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(testing
        all_in_one.cpp
        classes/Room.cpp
        classes/Person.cpp
)
target_link_libraries(testing Threads::Threads)
target_link_libraries(testing
        ${CMAKE_THREAD_LIBS_INIT}
)