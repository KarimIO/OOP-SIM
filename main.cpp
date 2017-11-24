#include <iostream>
#include "system.hpp"
#include "sim_instructions.hpp"

int main(int argc, char *argv[]) {
    // Check args if there are any, or check for inputs
    std::string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        std::cout << "Please insert a path to the assembly file: ";
        std::cin  >> path;
    }


    // Try to execute the program
    try {
        System sys(path, ParseSimInstruction);
        sys.Run();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}