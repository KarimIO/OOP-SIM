#ifndef SIM_INSTRUCTION_HPP
#define SIM_INSTRUCTION_HPP

#include "instruction.hpp"
#include <string>

class System;

class AddInstruction : public Instruction {
public:
    AddInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;
    
    address_t out_address_;

    bool in1_is_address_;
    address_t in1_address_;

    bool in2_is_address_;
    address_t in2_address_;
};

class NegInstruction : public Instruction {
public:
    NegInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;
    
    address_t out_address_;

    bool in_is_address_;
    address_t in_address_;
};

class MultInstruction : public Instruction {
public:
    MultInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;
    
    address_t out_address_;

    bool in1_is_address_;
    address_t in1_address_;

    bool in2_is_address_;
    address_t in2_address_;
};

class Jmp0Instruction : public Instruction {
public:
    Jmp0Instruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;
    
    address_t jump_address_;

    bool in_is_address_;
    address_t in_address_;
};

class JmpInstruction : public Instruction {
public:
    JmpInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;
    
    address_t jump_address_;
};

class AssInstruction : public Instruction {
public:
    AssInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;
    
    address_t out_address_;

    bool in_is_address_;
    address_t in_address_;
};

class LeInstruction : public Instruction {
public:
    LeInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;
    
    address_t out_address_;

    bool in1_is_address_;
    address_t in1_address_;

    bool in2_is_address_;
    address_t in2_address_;
};

class ReadInstruction : public Instruction {
public:
    ReadInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;

    address_t address_;
};

class WriteInstruction : public Instruction {
public:
    WriteInstruction(System *system, std::string);
    virtual void Execute();
private:
    System *system_;

    bool is_address_;
    address_t address_;
};

class PrintInstruction : public Instruction {
public:
    PrintInstruction(std::string param);
    virtual void Execute();
private:
    std::string param_;
};

class PrintLnInstruction : public Instruction {
public:
    PrintLnInstruction(std::string param);
    virtual void Execute();
private:
    std::string param_;
};

class HaltInstruction : public Instruction {
public:
    HaltInstruction(System *system);
    virtual void Execute();
private:
    System *system_;
};

Instruction *ParseSimInstruction(System *system, std::string instruction);

#endif