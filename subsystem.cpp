#include "subsystem.hpp"
#include "system.hpp"
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <iostream>

Subsystem::Subsystem(System *system, std::string path, Instruction *(*ParseInstruction)(Subsystem *, std::string)) : system_{ system }, instructions_ { 0 }, program_counter_(0), running_(false), ParseInstruction_(ParseInstruction)
{
	LoadFile(path);
}

Subsystem::~Subsystem() {
	// Delete any instructions
	for (Instruction *i : instructions_) {
		if (i != nullptr) {
			delete i;
		}
	}
}

void Subsystem::LoadFile(std::string path) {
	// Load File
	std::ifstream file(path);
	if (file.fail()) {
		throw std::runtime_error("Failed to load file " + path);
	}

	// For each line, parse the instruction
	std::string instruction;
	address_t i = 0;
	while(std::getline(file, instruction)) {
		if (i > kInstructionSize) {
			throw std::runtime_error("Subsystem::LoadFile: Too many instructions in code. Please insert up to " + std::to_string(kInstructionSize) + " instructions.");
		}
		instructions_[i++] = ParseInstruction_(this, instruction);
	}
}

void Subsystem::Run() {
	running_ = true;
	while (running_) {
		if (program_counter_ > kInstructionSize) {
			throw std::runtime_error("Subsystem::Run: Attempt to access invalid instruction! PC must be between 0 and " + std::to_string(kInstructionSize));
		}
		if (instructions_[program_counter_] == nullptr) {
			throw std::runtime_error("Subsystem::Run: Attempt to access invalid instruction! Instruction has not been initialized.");
		}
		instructions_[program_counter_++]->Execute();
	}
}

void Subsystem::Reset() {
	// Reset PC and delete all instructions and data
	program_counter_ = 0;
	std::memset(instructions_, 0, sizeof(instructions_));
}

void Subsystem::RunSingle() {
	if (program_counter_ > kInstructionSize) {
		throw std::runtime_error("Subsystem::Run: Attempt to access invalid instruction! PC must be between 0 and " + std::to_string(kInstructionSize));
	}
	if (instructions_[program_counter_] == nullptr) {
		throw std::runtime_error("Subsystem::Run: Attempt to access invalid instruction! Instruction has not been initialized.");
	}
	instructions_[program_counter_++]->Execute();
}

void Subsystem::SetPC(address_t address) {
	if (address > kInstructionSize)
		throw std::runtime_error("Subsystem::SetPC: Invalid Instruction Address Location accessed.");

	program_counter_ = address;
}

void Subsystem::SetData(address_t address, int value) {
	system_->SetData(address, value);
}

int  Subsystem::GetData(address_t address) {
	return system_->GetData(address);
}

void Subsystem::HaltRun() {
	running_ = false;
}