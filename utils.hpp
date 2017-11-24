#ifndef UTILS_HPP
#define UTILS_HPP

#include "system.hpp"

int getValue(System *system, bool is_address, int value);
void ParseVariable(char *str, bool &is_address, address_t &address);
void ParseAddress(char *str, address_t &address);
void GetFirstToken(char *&str);
void GetNextToken(char *&str);
void toLower(std::string &val);

#endif