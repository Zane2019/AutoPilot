cmake_minimum_required(VERSION 3.5)

project(Decision)

#set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
#add_compile_options(-std=c++11)

add_library(mdp SHARED
        MarkovDecisionProcess/DataStructures.cpp
        MarkovDecisionProcess/StateActionEncoder.cpp
        MarkovDecisionProcess/TransitionParse.cpp
        MarkovDecisionProcess/RewardParse.cpp
        MarkovDecisionProcess/PolicyParse.cpp
        MarkovDecisionProcess/MarkovDecisionProcess.cpp)

target_include_directories(mdp 
                        PUBLIC
                        MarkovDecisionProcess/)
