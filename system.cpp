#include "system.hpp"
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>

std::string getExtension(std::string &str) {
	std::size_t found = str.find_last_of(".");
	return str.substr(found + 1);
}

System::System(std::string path, Instruction *(*ParseInstruction)(Subsystem *, std::string)) : data_{0}, ParseInstruction_(ParseInstruction) {
	std::string ext = getExtension(path);
	if (ext == "s") {
		subsystems_.push_back(new Subsystem(this, path, ParseInstruction));
	}
	else if (ext == "txt") {
		LoadFile(path);
	}
	else {
		throw std::runtime_error("Invalid input type! Please input either a .txt or .s file.");
	}
}

System::~System() {
	for (auto &s : subsystems_) {
		delete s;
	}
}

void System::LoadFile(std::string path) {
	std::ifstream file(path);
	if (file.fail()) {
		throw std::runtime_error("Failed to load file " + path);
	}

	std::string dir = "";
	std::size_t found = path.find_last_of("\//");
	if (found == std::string::npos) {
		std::size_t found = path.find_last_of("\\");
		if (found != std::string::npos) {
			dir = path.substr(0, found + 1);
		}
	}
	else {
		dir = path.substr(0, found + 1);
	}
	std::string line;
	while (std::getline(file, line)) {
		subsystems_.push_back(new Subsystem(this, dir + line, ParseInstruction_));
	}
}

void System::Run() {
	std::thread *threads = new std::thread[subsystems_.size()];
	for (int i = 0; i < subsystems_.size(); i++) {
		threads[i] = std::thread(&Subsystem::Run, subsystems_[i]);
	}

	for (int i = 0; i < subsystems_.size(); i++) {
		threads[i].join();
	}
}

void System::Reset() {
	// Reset PC and delete all instructions and data
	for (auto &s : subsystems_) {
		s->Reset();
	}
	std::memset(data_, 0, sizeof(data_));
}

void System::RunSingle() {
	for (auto &s : subsystems_) {
		s->RunSingle();
	}
}

void System::SetData(address_t address, int value) {
	if (address > kDataSize)
		throw std::runtime_error("System::SetData: Invalid Data Address Location accessed.");

	data_[address] = value;
}

int  System::GetData(address_t address) {
	if (address > kDataSize)
		throw std::runtime_error("System::SetData: Invalid Data Address Location accessed.");

	return data_[address];
}

void System::HaltRun() {
	for (auto &s : subsystems_) {
		s->HaltRun();
	}
}