/*
 * AlgorithmRegistrar.cpp
 *
 *  Created on: Apr 29, 2019
 *      Author: Alon Liberman
 */


#include "AlgorithmRegistrar.h"
#include <dlfcn.h>

using namespace std;

static const string SO_SUFFIX = ".so";


AlgorithmRegistrar AlgorithmRegistrar::instance;
/* Loads all so files in input path.
 * If so file cannot be loaded the print error to the screen.
 * Return value - void.*/
void AlgorithmRegistrar::loadAlgorithms(const std::string& path, const std::list<std::string>& soFiles) {
	AlgorithmRegistrar& registrar = AlgorithmRegistrar::getInstance();
	for (const string& soFile : soFiles) {
		string soFileWithoutSuffix = soFile.substr(0, soFile.rfind(SO_SUFFIX)); //Removes .so suffix from file name.
		string module = path + soFile;
		DLClass dllHandler(module);
		if (dllHandler.getValidSoFile()) {
			dllHandlers.push_back((dllHandler));
			registrar.setNameForLastAlgorithm(soFileWithoutSuffix);
		}
	}
}


