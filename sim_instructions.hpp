#ifndef SIM_INSTRUCTION_HPP
#define SIM_INSTRUCTION_HPP

#include "instruction.hpp"
#include <string>

class Subsystem;

class AddInstruction : public Instruction {
public:
    AddInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;
    
    address_t out_address_;

    bool in1_is_address_;
    address_t in1_address_;

    bool in2_is_address_;
    address_t in2_address_;
};

class NegInstruction : public Instruction {
public:
    NegInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;
    
    address_t out_address_;

    bool in_is_address_;
    address_t in_address_;
};

class MultInstruction : public Instruction {
public:
    MultInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;
    
    address_t out_address_;

    bool in1_is_address_;
    address_t in1_address_;

    bool in2_is_address_;
    address_t in2_address_;
};

class Jmp0Instruction : public Instruction {
public:
    Jmp0Instruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;
    
    address_t jump_address_;

    bool in_is_address_;
    address_t in_address_;
};

class JmpInstruction : public Instruction {
public:
    JmpInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;
    
    address_t jump_address_;
};

class AssInstruction : public Instruction {
public:
    AssInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;
    
    address_t out_address_;

    bool in_is_address_;
    address_t in_address_;
};

class LeInstruction : public Instruction {
public:
    LeInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;
    
    address_t out_address_;

    bool in1_is_address_;
    address_t in1_address_;

    bool in2_is_address_;
    address_t in2_address_;
};

class ReadInstruction : public Instruction {
public:
    ReadInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;

    address_t address_;
};

class WriteInstruction : public Instruction {
public:
    WriteInstruction(Subsystem *system, std::string);
    virtual void Execute();
private:
    Subsystem *system_;

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
    HaltInstruction(Subsystem *system);
    virtual void Execute();
private:
    Subsystem *system_;
};

class SleepInstruction : public Instruction {
public:
	SleepInstruction(std::string param);
	virtual void Execute();
private:
	long long time_;
};

Instruction *ParseSimInstruction(Subsystem *system, std::string instruction);

#endif