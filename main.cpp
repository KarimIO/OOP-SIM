#include <iostream>
#include "system.hpp"
#include "sim_instructions.hpp"

#ifdef _WIN32
#define _CRT_NO_WARNINGS
#endif

int main(int argc, char *argv[]) {
    // Check args if there are any, or check for inputs
    std::string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        std::cout << "Please insert a path to either an assembly (.s) file, or a manifest (.txt) file: ";
        std::cin  >> path;
    }

    // Try to execute the program
    try {
        System sys(path, ParseSimInstruction);
        sys.Run();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

#ifdef _WIN32
	system("pause");
#endif
}