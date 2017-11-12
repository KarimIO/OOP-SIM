#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

typedef unsigned short address_t;

class Instruction {
public:
    virtual void Execute() = 0;
};

#endif