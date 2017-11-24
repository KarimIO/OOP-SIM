#include "system.hpp"
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <iostream>

System::System(std::string path, Instruction *(*ParseInstruction)(System *, std::string)) : instructions_{0}, data_{0}, program_counter_(0), running_(false), ParseInstruction_(ParseInstruction) {
	LoadFile(path);
}

System::~System() {
	// Delete any instructions
	for (Instruction *i : instructions_) {
		if (i != nullptr) {
			delete i;
		}
	}
}

void System::LoadFile(std::string path) {
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
			throw std::runtime_error("System::LoadFile: Too many instructions in code. Please insert up to " + std::to_string(kInstructionSize) + " instructions.");
		}
		instructions_[i++] = ParseInstruction_(this, instruction);
	}
}

void System::Run() {
	running_ = true;
	while (running_) {
		if (program_counter_ > kInstructionSize) {
			throw std::runtime_error("System::Run: Attempt to access invalid instruction! PC must be between 0 and " + std::to_string(kInstructionSize));
		}
		if (instructions_[program_counter_] == nullptr) {
			throw std::runtime_error("System::Run: Attempt to access invalid instruction! Instruction has not been initialized.");
		}
		instructions_[program_counter_++]->Execute();
	}
}

void System::Reset() {
	// Reset PC and delete all instructions and data
	program_counter_ = 0;
	std::memset(instructions_, 0, sizeof(instructions_));
	std::memset(data_, 0, sizeof(data_));
}

void System::RunSingle() {
	if (program_counter_ > kInstructionSize) {
		throw std::runtime_error("System::Run: Attempt to access invalid instruction! PC must be between 0 and " + std::to_string(kInstructionSize));
	}
	if (instructions_[program_counter_] == nullptr) {
		throw std::runtime_error("System::Run: Attempt to access invalid instruction! Instruction has not been initialized.");
	}
	instructions_[program_counter_++]->Execute();
}

void System::SetPC(unsigned short address) {
	if (address > kInstructionSize)
		throw std::runtime_error("System::SetPC: Invalid Instruction Address Location accessed.");

	program_counter_ = address;
}

void System::SetData(unsigned short address, int value) {
	if (address > kDataSize)
		throw std::runtime_error("System::SetData: Invalid Data Address Location accessed.");

	data_[address] = value;
}

int  System::GetData(unsigned short address) {
	if (address > kDataSize)
		throw std::runtime_error("System::SetData: Invalid Data Address Location accessed.");

	return data_[address];
}

void System::HaltRun() {
	running_ = false;
}