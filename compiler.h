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

#ifndef COMPILER_H_
#define COMPILER_H_

class Command {
public:
	Command();
	Command(std::string assemblyCmd);
	std::string getAssemblyCmd() const;
	std::bitset<8> getMachineCmd() const;

private:
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
