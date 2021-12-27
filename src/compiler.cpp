/*
 * compiler.cpp
 *
 *  Created on: Dec. 22, 2021
 *      Author: benng
 */

#include "compiler.h"

void compile() {

}

std::vector<std::string> readFile(std::string fileName) {
	std::ifstream file(fileName);
	std::string line;
	std::vector<std::string> input;

	while(getline(file, line)){
		input.push_back(line);
	}

	return input;
}

std::vector<std::string> stringSplit(const std::string &s, char delim) {
	std::vector<std::string> vec;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		vec.push_back(item);
	}
	return vec;
}

Conversion::Conversion() : binaryCmds("C:\\Users\\benng\\Documents\\Projects\\Active\\SAPCompiler\\data\\binaryCommands.txt") {
	std::string key;
	std::string value;
	while(binaryCmds >> key >> value)
		LUT[key] = value;
}

Conversion::Conversion(std::string binaryCmdPath) : binaryCmds(binaryCmdPath) {
	std::string key;
	std::string value;
	while(binaryCmds >> key >> value)
		LUT[key] = value;
}

std::string Conversion::lookUp(const std::string A) const {
	//std::cout << "from lookUp: " << A << "end" << std::endl;
	return LUT.at(A);
}

Command::Command() {
	Conversion();
	assemblyCmd = "NOP";
	machineCmd = std::bitset<8>(std::string("00000000"));
	argBase = 2;
}

Command::Command(std::string inAssemblyCmd, int argBase) {
	Conversion();
	assemblyCmd = inAssemblyCmd;
	machineCmd = AtoM(assemblyCmd);
	this->argBase = argBase;
}

std::string Command::getAssemblyCmd() const {
	return assemblyCmd;
}

std::bitset<8> Command::getMachineCmd() const {
	return machineCmd;
}

std::bitset<8> Command::AtoM(const std::string &A) const{
	std::vector<std::string> ASplit = stringSplit(A, ' ');
	std::string keyword = ASplit[0];
	std::string keywordBinary = lookUp(keyword);
	std::string argBinary = ASplit[1];

	std::bitset<8> M(keywordBinary);
	M <<= 4; //shift keyword to MSB
	M |= std::bitset<8>(argBinary); //OR with arg (arg can only be in 4 LSB)

	return M;
}

Program::Program() {
	size = 0;
	assemblyCode = new std::string[size];
	machineCode = new std::bitset<8>[size];

}

Program::Program(const Command& cmd){
	size = 1;
	assemblyCode = new std::string[size];
	machineCode = new std::bitset<8>[size];

	assemblyCode[0] = cmd.getAssemblyCmd();
	machineCode[0] = cmd.getMachineCmd();
}

Program::Program(const Program& copy){
	size = copy.size;
	assemblyCode = new std::string[size];
	machineCode = new std::bitset<8>[size];

	for(int i = 0; i < size; i++){
		assemblyCode[i] = copy.getAssemblyCode()[i];
		machineCode[i].set(i, copy.getMachineCode()[i]);
	}
}

Program& Program::operator=(const Program& copy){
	if(this != &copy) {
		size = copy.size;
		for(int i = 0; i < size; i++){
			assemblyCode[i] = copy.getAssemblyCode()[i];
			machineCode[i].set(i, copy.getMachineCode()[i]);
		}
	}
	return *this;
}

void Program::addCommand(Command& cmd) {
	std::string* tempA = new std::string[size+1];
	std::bitset<8>* tempM = new std::bitset<8>[size+1];
	for(int i = 0; i < size; i++){
		tempA[i] = assemblyCode[i];
		tempM[i] = machineCode[i];
	}
	tempA[size] = cmd.getAssemblyCmd();
	tempM[size] = cmd.getMachineCmd();

	size++;
	assemblyCode = tempA;
	machineCode = tempM;
}

Program::~Program(){
	delete[] assemblyCode;
	delete[] machineCode;
	assemblyCode = nullptr;
	machineCode = nullptr;
}

std::string Program::getAssemblyCode() const {
	return *assemblyCode;
}

std::bitset<8> Program::getMachineCode() const {
	return *machineCode;
}

void Program::printAssemblyCode() const {
	for(int i = 0; i < size; i++)
		std::cout << assemblyCode[i] << std::endl;
}

void Program::printMachineCode() const {
	for(int i = 0; i < size; i++) {
		for(int j = 7; j >= 0; j--) {
			std::cout << machineCode[i][j];
			if(j == 4)
				std::cout << " ";

		}
		std::cout << std::endl;
	}
}

void Program::printConversion() const {
	for(int i = 0; i < size; i++) {
		std::cout << assemblyCode[i] << " => ";
		for(int j = 7; j >= 0; j--) {
			std::cout << machineCode[i][j];
			if(j == 4)
				std::cout << " ";

		}
		std::cout << std::endl;
	}
}
