#include "sim_instructions.hpp"
#include "system.hpp"
#include "utils.hpp"
#include <iostream>

//#define DEBUG_INSTRUCTIONS

AddInstruction::AddInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: ADD " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseVariable(str, in1_is_address_, in1_address_);
    GetNextToken(str);
    ParseVariable(str, in2_is_address_, in2_address_);
    GetNextToken(str);
    ParseAddress(str, out_address_);
}

void AddInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: ADD " << (in1_is_address_?"x":"") << in1_address_ << ", " << (in2_is_address_?"x":"") << in2_address_ << ", x" << out_address_ << std::endl;
#endif
    int val1 = getValue(system_, in1_is_address_, in1_address_);
    int val2 = getValue(system_, in2_is_address_, in2_address_);
    system_->SetData(out_address_, val1 + val2);
}

NegInstruction::NegInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: NEG " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseVariable(str, in_is_address_, in_address_);
    GetNextToken(str);
    ParseAddress(str, out_address_);
}

void NegInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: NEG " << (in_is_address_?"x":"") << in_address_ << ", x" << out_address_ << std::endl;
#endif
    int val = getValue(system_, in_is_address_, in_address_);
    system_->SetData(out_address_, -val);
}

MultInstruction::MultInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: MULT " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseVariable(str, in1_is_address_, in1_address_);
    GetNextToken(str);
    ParseVariable(str, in2_is_address_, in2_address_);
    GetNextToken(str);
    ParseAddress(str, out_address_);
}

void MultInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: MULT " << (in1_is_address_?"x":"") << in1_address_ << ", " << (in2_is_address_?"x":"") << in2_address_ << ", x" << out_address_ << std::endl;
#endif
    int val1 = getValue(system_, in1_is_address_, in1_address_);
    int val2 = getValue(system_, in2_is_address_, in2_address_);
    system_->SetData(out_address_, val1 * val2);
}

JmpInstruction::JmpInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: JMP " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseAddress(str, jump_address_);
}

void JmpInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: JMP x" << jump_address_ << std::endl;
#endif
    system_->SetPC(jump_address_);
}

Jmp0Instruction::Jmp0Instruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: JMP0 " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseVariable(str, in_is_address_, in_address_);
    GetNextToken(str);
    ParseAddress(str, jump_address_);
}

void Jmp0Instruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: JMP0 " << (in_is_address_?"x":"") << in_address_ << ", x" << jump_address_ << std::endl;
#endif
    int val = getValue(system_, in_is_address_, in_address_);
    if (val == 0)
		system_->SetPC(jump_address_);
}

LeInstruction::LeInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: LE " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseVariable(str, in1_is_address_, in1_address_);
    GetNextToken(str);
    ParseVariable(str, in2_is_address_, in2_address_);
    GetNextToken(str);
    ParseAddress(str, out_address_);
}

void LeInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: LE " << (in1_is_address_?"x":"") << in1_address_ << ", " << (in2_is_address_?"x":"") << in2_address_ << ", x" << out_address_ << std::endl;
#endif
    int val1 = getValue(system_, in1_is_address_, in1_address_);
    int val2 = getValue(system_, in2_is_address_, in2_address_);
    system_->SetData(out_address_, (val1 < val2) ? 1 : 0);
}

AssInstruction::AssInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: NEG " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseVariable(str, in_is_address_, in_address_);
    GetNextToken(str);
    ParseAddress(str, out_address_);
}

void AssInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: NEG " << (in_is_address_?"x":"") << in_address_ << ", x" << out_address_ << std::endl;
#endif
    int val = getValue(system_, in_is_address_, in_address_);
    system_->SetData(out_address_, val);
}

ReadInstruction::ReadInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: READ " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseAddress(str, address_);
}

void ReadInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: READ x" << address_ << std::endl;
#endif
	int val;
	std::cin >> val;
	system_->SetData(address_, val);
}

WriteInstruction::WriteInstruction(System *system, std::string params) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: WRITE " << params << std::endl;
#endif
    char *str = const_cast<char *>(params.c_str());
    GetFirstToken(str);
    ParseVariable(str, is_address_, address_);
}

void WriteInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: WRITE " << (is_address_?"x":"") << address_ << std::endl;
#endif
    std::cout << getValue(system_, is_address_, address_) << std::endl;
}

PrintInstruction::PrintInstruction(std::string param) : param_(param) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: PRINT" << std::endl;
#endif
}

void PrintInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: PRINT" << std::endl;
#endif
	std::cout << param_;
}

PrintLnInstruction::PrintLnInstruction(std::string param) : param_(param) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: PRINTLN" << std::endl;
#endif
}

void PrintLnInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: PRINT" << std::endl;
#endif
	std::cout << param_ << std::endl;
}

HaltInstruction::HaltInstruction(System *system) : system_(system) {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Create Instruction: HALT" << std::endl;
#endif
}

void HaltInstruction::Execute() {
#ifdef DEBUG_INSTRUCTIONS
    std::cout << "Execute Instruction: HALT" << std::endl;
#endif
    system_->HaltRun();
}

Instruction *ParseSimInstruction(System *system, std::string command) {
	std::string type, params;

    // Seperate the instruction into the base and the parameters by finding the first space.
	unsigned int p = command.find(' ');
	if (p == -1) {
		type = command;
		toLower(type);
		params = "";
	}
	else {
		type = command.substr(0, p);
		toLower(type);
		params = command.substr(p+1);
	}

    // Factory to create Instructions based on the instruction name
	Instruction *inst = nullptr;
	if (type == "add") {
		inst = new AddInstruction(system, params);
	}
	else if (type == "neg") {
		inst = new NegInstruction(system, params);
	}
	else if (type == "mult") {
		inst = new MultInstruction(system, params);
	}
	else if (type == "jmp") {
		inst = new JmpInstruction(system, params);
	}
	else if (type == "jmp0") {
		inst = new Jmp0Instruction(system, params);
	}
	else if (type == "ass") {
		inst = new AssInstruction(system, params);
	}
	else if (type == "le") {
		inst = new LeInstruction(system, params);
	}
	else if (type == "read") {
		inst = new ReadInstruction(system, params);
	}
	else if (type == "write") {
		inst = new WriteInstruction(system, params);
	}
	else if (type == "print") {
		inst = new PrintInstruction(params);
	}
	else if (type == "println") {
		inst = new PrintLnInstruction(params);
	}
	else if (type == "halt") {
		inst = new HaltInstruction(system);
	}
	else {
		throw std::runtime_error("System::ParseInstruction: Invalid Instruction in File: " + type);
	}

	return inst;
}