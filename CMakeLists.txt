cmake_minimum_required(VERSION 3.23)
project(RTOS)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_library(LIBRT rt REQUIRED)

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )

foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    string( REPLACE ".cpp" "" name_exe ${filename} )
    add_executable( ${name_exe} ${sourcefile} )
    target_link_libraries( ${name_exe} PRIVATE Threads::Threads ${LIBRT})
endforeach( sourcefile ${APP_SOURCES} )