/*
 * main.cpp
 *
 *  Created on: Dec. 16, 2021
 *      Author: benng
 */

//#include "compiler.h"
#include "cxxopts.hpp"


int main(int argc, char* argv[]){


	cxxopts::Options options("sapcmp", "Simple CLI to compile a custom assembly language for a Ben Eater inspired 8-bit SAP (Simple As Possible) CPU.");

	options.add_options()
		("o,output", "Output file", cxxopts::value<std::string>())
		("b,base", "Infile argument base", cxxopts::value<int>()->default_value("2"))
		("d,display", "Display conversion", cxxopts::value<bool>()->default_value("true"))
		("v,verbose", "Verbose (0,1)", cxxopts::value<int>()->default_value("0"))
		("h,help", "Print usage")
	;

	auto results = options.parse(argc, argv);

	std::string outfile;
		if(results.count("output"))
			outfile = results["output"].as<std::string>();

	int base = results["base"].as<int>();
	bool display = results["display"].as<bool>();
	int verbose = results["verbose"].as<int>();

	if(results.count("help")) {
	  std::cout << options.help() << std::endl;
	  exit(0);
	}





	/*
	std::cout << "You have entered " << argc
		 << " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		std::cout << argv[i] << "\n";


	std::cout << "starting";



	std::vector<std::string> inVec = readFile(argv[1]);

	//std::cout << inVec[0] << std::endl;



	Program prog;

	for(std::string& cmd : inVec) {
		//std::cout << cmd;
		Command tmp(cmd, 2);
		prog.addCommand(tmp);
	}

	prog.printConversion();

*/


	return 0;
}
