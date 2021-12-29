/*
 * compiler.cpp
 *
 *  Created on: Dec. 22, 2021
 *      Author: benng
 */

#include "compiler.h"

//TODO: Fix binary Commands path
Conversion::Conversion() : binaryCmds("C:\\Users\\benng\\Documents\\Projects\\Active\\SAPCompiler\\data\\binaryCommands.txt") {
	std::string key;
	std::string value;
	if(!binaryCmds.is_open()) {
		//TODO: Throw ConversionException
		std::cout << "ConversionError - could not open file\n";
		exit(1);
	}
	while(binaryCmds >> key >> value)
		LUT[key] = value;
}

Conversion::Conversion(std::string binaryCmdPath) : binaryCmds(binaryCmdPath) {
	std::string key;
	std::string value;
	if(!binaryCmds.is_open()) {
		//TODO: Throw ConversionException
		std::cout << "ConversionError - could not open file\n";
		exit(1);
	}
	while(binaryCmds >> key >> value)
		LUT[key] = value;
}

std::string Conversion::lookUp(const std::string A) const {
	//TODO: Try catch .at to handle invalid keyword. Throw InvaildKeywordException
	return LUT.at(A);
}

Command::Command() {
	Conversion();
	assemblyCmd = "NOP";
	machineCmd = std::bitset<8>(std::string("00000000"));
	argBase = 2;
}

//TODO: error check inAssemblyCmd and argBase
Command::Command(std::string inAssemblyCmd, int argBase) {
	Conversion();
	if(argBase < 2 || argBase > 16) {
		//TODO: Throw CommandException
		std::cout << "CommandException - invalid Argument Base, must be between 2 and 16 inclusive";
		exit(1);
	}
	if(isValidCmdStr(inAssemblyCmd)){

	}

	this->argBase = argBase;
	assemblyCmd = inAssemblyCmd;
	machineCmd = AtoM(assemblyCmd);
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
	std::string argString = ASplit[1];

	std::bitset<8> M(keywordBinary);
	M <<= 4; //shift keyword to MSB
	M |= std::bitset<8>(std::stoi(argString, nullptr, argBase));

	return M;
}

std::vector<std::string> Command::stringSplit(const std::string &s, char delim) const {
	std::vector<std::string> vec;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		vec.push_back(item);
	}
	return vec;
}

bool Command::isValidCmdStr(const std::string& str) const {
	bool rslt = true;
	int strLen = str.length();
	if(strLen != 8 || strLen != 3) {
		rslt = false;
	} else if(strLen == 8 && str.at(ARG_LEN) != CMD_ARG_DELIM) {
		rslt = false;
	}
	return rslt;
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
	if(size+1 > SAP_RAM_SIZE) {
		//TODO: throw ProgramError
		std::cout << "Program error - program too large\n";
		exit(1);
	}
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

std::ostream& operator<<(std::ostream& os, const Program& p) {
	for(int i = 0; i < p.size; i++) {
		os << p.assemblyCode[i] << " => ";
		for(int j = 7; j >= 0; j--) {
			os << p.machineCode[i][j];
			if(j == 4)
				os << " ";

		}
		os << '\n';
	}
	return os;
}

void compile(const std::string& infile, const std::string& outfile, int base, bool display, int verbose) {
	Program prog;
	std::vector<std::string> inVec = readFile(infile);

	for(std::string& cmd : inVec) {
		Command tmp(cmd, base);
		prog.addCommand(tmp);
	}

	if(display)
		std::cout << prog;


	writeFile(outfile, prog);

}

std::vector<std::string> readFile(const std::string& fileName) {
	std::ifstream file(fileName);
	std::string line;
	std::vector<std::string> input;

	while(getline(file, line)){
		input.push_back(line);
	}

	return input;
}

void writeFile(const std::string& fileName, const Program& prog){
	std::ofstream file(fileName);
	if(file.is_open()) {
		file << "---  sapcmp compilation summary  ---\n";
		file << "---    [INPUT] => [OUTPUT]     ---\n\n";
		file << prog;
		file.close();
	}
}
