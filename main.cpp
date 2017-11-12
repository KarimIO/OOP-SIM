#include <iostream>
#include "system.hpp"
#include "sim_instructions.hpp"

int main(int argc, char *argv[]) {
    try {
        System sys("test.s", ParseSimInstruction);
        sys.Run();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}