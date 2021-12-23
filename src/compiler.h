/*
 * compiler.h
 *
 *  Created on: Dec. 16, 2021
 *      Author: benng
 */

#pragma once

#include <map>
#include <string>
#include <bitset>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#ifndef COMPILER_H_
#define COMPILER_H_x

std::vector<std::string> stringSplit(const std::string &s, char delim);

class Conversion {
public:
	Conversion();
	Conversion(std::string binaryCmdPath);

	std::string lookUp(const std::string A) const;


private:

	std::ifstream binaryCmds;
	std::map<std::string, std::string> LUT;

};

class Command : public Conversion {
public:
	Command();
	Command(std::string assemblyCmd, int argBase);
	std::string getAssemblyCmd() const;
	std::bitset<8> getMachineCmd() const;



private:

	std::bitset<8> AtoM(const std::string &A) const;

	int argBase;

	std::string assemblyCmd;
	std::bitset<8> machineCmd;

};

class Program {
public:
	Program();
	Program(Command cmd);
	~Program();
	Program(const Program& cpy);
	Program& operator=(const Program& cpy);

	void addCommand(Command cmd);

	std::string* getAssemblyCode() const;
	std::bitset<8>* getMachineCode() const;

private:
	std::string* assemblyCode;
	std::bitset<8>* machineCode();

};


#endif /* COMPILER_H_ */
