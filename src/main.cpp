/*
 * main.cpp
 *
 *  Created on: Dec. 16, 2021
 *      Author: benng
 */

#include "compiler.h"
#include "cxxopts.hpp"


int main(int argc, char* argv[]){


	cxxopts::Options options("sapcmp", "Simple CLI to compile a custom assembly language for a Ben Eater inspired 8-bit SAP (Simple As Possible) CPU.");

	options.add_options()
		("i,input", "Input file", cxxopts::value<std::string>())
		("o,output", "Output file", cxxopts::value<std::string>()->default_value("sapcmp_output.txt"))
		("b,base", "Infile argument base", cxxopts::value<int>()->default_value("2"))
		("d,display", "Display conversion", cxxopts::value<bool>()->implicit_value("true"))
		("v,verbose", "Verbose (0,1)", cxxopts::value<int>()->default_value("0"))
		("h,help", "Print usage")
	;

	auto results = options.parse(argc, argv);

	std::string infile;
	if(results.count("input"))
		infile = results["input"].as<std::string>();

	std::string outfile = results["output"].as<std::string>();

	int base = results["base"].as<int>();

	bool display = false;
	if(results.count("display"))
		display = results["display"].as<bool>();

	int verbose = results["verbose"].as<int>();

	if(results.count("help")) {
	  std::cout << options.help() << std::endl;
	  exit(0);
	}

	if(!results.count("input")) {
		//TODO: Display conversion table
		std::cout << "No input or output file";
		exit(1);
	}

	compile(infile, outfile, base, display, verbose);

	return 0;
}
