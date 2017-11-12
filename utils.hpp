#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>

inline int getValue(System *system, bool is_address, int value) {
    return is_address ? system->GetData((address_t)value) : value;
}

void ParseVariable(char *str, bool &is_address, address_t &address) {
    if (str[0] == '-' || str[0] >= '0' && str[0] <= '9') {
        address = atoi(&str[0]);
        is_address = false;
    }
    else {
        address = atoi(&str[1]);
        is_address = true;
    }
}

void ParseAddress(char *str, address_t &address) {
    if (str[0] == '-' || str[0] >= '0' && str[0] <= '9') {
        address = atoi(&str[0]);
    }
    else {
        address = atoi(&str[1]);
    }
}

void GetFirstToken(char *&str) {
    str = strtok(str, ", \t\n");
}

void GetNextToken(char *&str) {
    str = strtok(NULL, ", \t\n");
}

void toLower(std::string &val) {
	for(char &c : val) {
		if (c >= 'A' && c <= 'Z') {
			c += ('a' - 'A');
		}
	}
}

#endif