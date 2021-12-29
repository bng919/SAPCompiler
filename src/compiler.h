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

//Number of words (instructions) the processor can hold
const unsigned int SAP_RAM_SIZE = 16;
const char CMD_ARG_DELIM = ' ';
const unsigned int ARG_LEN = 3;


class Conversion {
public:
	Conversion();
	Conversion(std::string binaryCmdPath);

	friend std::ostream& operator<<(std::ostream& os, const Conversion& c);

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
	int argBase;
	std::bitset<8> AtoM(const std::string &A) const;
	std::vector<std::string> stringSplit(const std::string &s, char delim) const;
	bool isValidCmdStr(const std::string &str) const;
	std::string assemblyCmd;
	std::bitset<8> machineCmd;

};

class Program {
public:
	Program();
	Program(const Command& cmd);
	~Program();
	Program(const Program& cpy);
	Program& operator=(const Program& cpy);

	void addCommand(Command& cmd);

	std::string getAssemblyCode() const;
	std::bitset<8> getMachineCode() const;

	friend std::ostream& operator<<(std::ostream& os, const Program& p);

private:
	unsigned int size;
	std::string* assemblyCode;
	std::bitset<8>* machineCode;

};

void compile(const std::string& infile, const std::string& outfile, int base, bool display, int verbose);

std::vector<std::string> readFile(const std::string& fileName);

void writeFile(const std::string& fileName, const Program& prog);


#endif /* COMPILER_H_ */
