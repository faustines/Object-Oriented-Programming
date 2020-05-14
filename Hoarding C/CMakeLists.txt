cmake_minimum_required(VERSION 3.8)
project(Hoarding)

set(CMAKE_C_STANDARD 11)
set(GCC_ENABLE_WARNINGS "-O0 -Wall -Werror -Wno-unused-result")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_ENABLE_WARNINGS}")
set(SOURCE_FILES main.c GameState.c GameState.h Player.c Player.h Board.c Board.h Rules.c Rules.h Utility.c Utility.h Property.c Property.h PropertySet.c PropertySet.h PropertyManager.c PropertyManager.h Space.c Space.h HoardingTypeDefs.h Move.c Move.h)
add_executable(Hoarding ${SOURCE_FILES})