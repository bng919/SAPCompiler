/*
 * main.cpp
 *
 *  Created on: Dec. 16, 2021
 *      Author: benng
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <bitset>

int main(){
	std::ifstream binaryCmds("binaryCommands.txt");

	std::string key;
	std::string value;

	std::map<std::string, std::bitset<4>> bc;
	//m.insert(std::pair<std::string, int>("LDA", 0b0001));

	while(binaryCmds >> key >> value){

		bc[key] = std::stoi(value, 0, 2);
	}

	std::cout << bc["LDA"];

	return 0;
}
