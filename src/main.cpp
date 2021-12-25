/*
 * main.cpp
 *
 *  Created on: Dec. 16, 2021
 *      Author: benng
 */

#include "compiler.h"

int main(){

	Command b("LDA 1010", 2);
	Command c("ADD 0000", 2);
	Command d("ADD 0001", 2);
	Command e("ADD 0010", 2);
	Command f("ADD 0011", 2);

	Program a(b);

	a.addCommand(c);
	a.addCommand(d);
	a.addCommand(e);
	a.addCommand(f);


	a.printConversion();
	a.printMachineCode();

	std::bitset<8> temp = a.getMachineCode();

	std::cout << temp;


	return 0;
}
