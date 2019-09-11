/*
 * ArgumentParser.cpp
 *
 *  Created on: May 1, 2019
 *      Author: Alon Liberman
 */

#include <unistd.h>
#include <dirent.h>
#include "ArgumentParser.h"
#include "FileUtilities.h"
#include <iostream>


using namespace std;
static const unsigned int BUFF_SIZE = 100;
static const string USAGE = "USAGE: -maze_path <path> -algorithm_path <path> -num_threads <num> -output <path>";
ArgumentParser::ArgumentParser(int argc,const char* argv[]): validArgs(true) {
	char buff[BUFF_SIZE];
	string curDir = getcwd(buff,BUFF_SIZE);
	curDir += '/';
	/* Initialize mazePath, algorithmPath and outputPath */
	mazePath = curDir;
	algorithmPath = curDir;
	outputPath = "";
	numOfThreads=1;
	parseInputArgs(argc,argv);
	buildFileLists();
}

ArgumentParser::~ArgumentParser() {}
/* Parses maze_path, algorithm_path and output and save the result in private members.
 * Return value - void */
void ArgumentParser::parseInputArgs(int argc, const char* argv[]) {
	for (int i=1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-maze_path" && i+1 < argc && argv[i+1][0] != '-') {
			mazePath = argv[i+1];
		}
		if (arg == "-algorithm_path" && i+1 < argc && argv[i+1][0] != '-') {
			algorithmPath = argv[i+1];
		}
		if (arg == "-output" && i+1 < argc && argv[i+1][0] != '-') {
			outputPath = argv[i+1];
		}
		if (arg == "-num_threads") {
			size_t idx;
			string threadsArg = argv[i+1];
			int threads = stoi(threadsArg,&idx);
			if (threadsArg.size() != idx || threads <= 0) { //Check if input num_threads is a valid number.
				cerr << USAGE << endl;
				validArgs = false;
			}
			else
				numOfThreads = static_cast<size_t> (threads);
		}
	}
}
/* Builds maze files and algorithm files list.
 * Return value - void. */
void ArgumentParser::buildFileLists() {
	mazeFileNames = FileUtilities::makeListOfFilesInDirecroty(mazePath.c_str());
	algorithmFileNames = FileUtilities::makeListOfFilesInDirecroty(algorithmPath.c_str());
	RemoveFilesWithoutExtension(".maze",mazeFileNames);
	RemoveFilesWithoutExtension(".so",algorithmFileNames);
}

/* Removes strings from input lst that does not end with input extension.
 * Return value - void. */
void ArgumentParser::RemoveFilesWithoutExtension(const string& extension, list<string>& lst) {
	list<string>::iterator next;
	for (list<string>::iterator itr=lst.begin(); itr!=lst.end(); ) {
		size_t pos = itr->rfind(extension);
		bool begin = false;
		next = ++itr;
		itr--;
		if (! (pos != string::npos && pos+extension.size() == itr->size()) ) {
			if (itr == lst.begin())
				begin = true;
			lst.erase(itr);
		}
		if(begin) {
			itr = lst.begin();
		}
		else {
			itr = next;
		}

	}
}
