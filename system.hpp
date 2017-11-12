#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "instruction.hpp"
#include "sim_instructions.hpp"
#include <string>

const address_t kInstructionSize = 1024u;
const address_t kDataSize = 1024u;

class System {
    friend class Instruction;
public:
    System(std::string path, Instruction *(*ParseInstruction)(System *, std::string));
    ~System();

    void LoadFile(std::string path);
    void Run();
    void Reset();
    // void RunSingle();
public:
    void SetPC(address_t address);
    int GetData(address_t address);
    void SetData(address_t address, int value);
    void HaltRun();
private:
    Instruction *(*ParseInstruction_)(System *, std::string);

    address_t program_counter_;
    bool running_;

    Instruction *instructions_[kInstructionSize];
    int data_[kDataSize];
};

#endif