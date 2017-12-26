#ifndef SUB_SYSTEM_HPP
#define SUB_SYSTEM_HPP

#include "instruction.hpp"
#include "sim_instructions.hpp"
#include <string>

class System;

const address_t kInstructionSize = 1024u;

class Subsystem {
    friend class Instruction;
public:
	Subsystem(System *system, std::string path, Instruction *(*ParseInstruction)(Subsystem *, std::string));
    ~Subsystem();

    void LoadFile(std::string path);
    void Run();
    void Reset();
    void RunSingle();
public:
    void SetPC(address_t address);
    int GetData(address_t address);
    void SetData(address_t address, int value);
    void HaltRun();
private:
	System * system_;
    Instruction *(*ParseInstruction_)(Subsystem *, std::string);

    address_t program_counter_;
    bool running_;

    Instruction *instructions_[kInstructionSize];
};

#endif