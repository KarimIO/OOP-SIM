#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "instruction.hpp"
#include "sim_instructions.hpp"
#include"subsystem.hpp"
#include <string>
#include <vector>

const address_t kDataSize = 1024u;

class System {
public:
    System(std::string path, Instruction *(*ParseInstruction)(Subsystem *, std::string));
    ~System();

    void LoadFile(std::string path);
    void Run();
    void Reset();
    void RunSingle();
public:
    int GetData(address_t address);
    void SetData(address_t address, int value);
    void HaltRun();
private:
    Instruction *(*ParseInstruction_)(Subsystem *, std::string);
	std::vector<Subsystem *> subsystems_;
	int data_[kDataSize];
};

#endif