cmake_minimum_required (VERSION 2.8.11)
project(SIM)

add_executable (sim main.cpp subsystem.cpp system.cpp sim_instructions.cpp utils.cpp subsystem.hpp system.hpp sim_instructions.hpp utils.hpp)