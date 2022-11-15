cmake_minimum_required(VERSION 3.23)
project(chatroom_client)

set(CMAKE_CXX_STANDARD 23)

add_executable(chatroom_client

        main.cpp
        src/client/client.cpp
        src/utils/utils.cpp

        headers/client/client.h
        headers/utils/utils.h )
