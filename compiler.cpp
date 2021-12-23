/*
 * compiler.cpp
 *
 *  Created on: Dec. 22, 2021
 *      Author: benng
 */

#include "compiler.h"


std::vector<std::string> stringSplit(const std::string &s, char delim) {
	std::vector<std::string> vec;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		vec.push_back(item);
	}
	return vec;
}

Conversion::Conversion() : binaryCmds("binaryCommands.txt") {
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
	return LUT.at(A);
}


Command::Command(){
	Conversion();
	assemblyCmd = "NOP";
	machineCmd = std::bitset<8>(std::string("00000000"));
	argBase = 2;
}

Command::Command(std::string inAssemblyCmd, int argBase){
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

