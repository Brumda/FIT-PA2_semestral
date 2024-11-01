cmake_minimum_required(VERSION 3.12)
project(TowerAttack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wno-long-long")

# Lze za komentovat pomocí # a pak použít valgrind
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# Ruzné debug flagy
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _GLIBCXX_DEBUG")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS
        "src/*.h"
        "src/*.cpp"
        )

add_executable(TowerAttack ${source_files} src/attackerEffect.cpp src/mapLoading.h)