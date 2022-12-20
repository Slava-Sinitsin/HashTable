cmake_minimum_required(VERSION 3.24)
project(hash_table)

set(CMAKE_CXX_STANDARD 17)

add_executable(hash_table main.cpp lib/OAHashTable.h lib/OANode.h lib/CCHashTable.h lib/CCnode.h lib/OATest.h lib/CCTest.h lib/MainMenu.h lib/TestHashFunction.h lib/OAHashTableTest.h lib/CCHashTableTest.h lib/PerformanceTest.h)
