#include "system.hpp"
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <iostream>

System::System(std::string path, Instruction *(*ParseInstruction)(System *, std::string)) : instructions_{0}, data_{0}, program_counter_(0), running_(false), ParseInstruction_(ParseInstruction) {
	LoadFile(path);
}

System::~System() {
	for (Instruction *i : instructions_) {
		delete i;
	}
}

void System::LoadFile(std::string path) {
	std::ifstream file(path);
	if (file.fail()) {
		throw std::runtime_error("Failed to load file " + path);
	}

	std::string instruction;
	address_t i = 0;
	while(std::getline(file, instruction)) {
		instructions_[i++] = ParseInstruction_(this, instruction);
	}
}

void System::Run() {
	running_ = true;
	while (running_) {
		instructions_[program_counter_++]->Execute();
	}
}

void System::Reset() {
	program_counter_ = 0;
	std::memset(instructions_, 0, sizeof(instructions_));
	std::memset(data_, 0, sizeof(data_));
}

// void System::RunSingle() {}

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