cmake_minimum_required(VERSION 3.22)
project(Ask_fm)

set(src_files
  src/main.cpp
  src/user.cpp
  src/question.cpp
  src/db.cpp
  src/login.cpp
  )
  
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "CPP STANDARD = ${CMAKE_CXX_STANDARD}")

add_executable(main ${src_files})

target_include_directories(main PUBLIC include/)
