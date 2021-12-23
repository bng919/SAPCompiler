/*
 * main.cpp
 *
 *  Created on: Dec. 16, 2021
 *      Author: benng
 */

#include "compiler.h"

int main(){

	Command test("LDA 1001", 2);

	std::cout << test.getMachineCmd();




	return 0;
}
