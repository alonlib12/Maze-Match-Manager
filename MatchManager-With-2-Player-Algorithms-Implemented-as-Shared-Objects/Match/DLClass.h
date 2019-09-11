/*
 * DLClass.h
 *
 *  Created on: May 5, 2019
 *      Author: Alon Liberman
 */

/* Description - A class that handles opening and closing .so files appropriatly */
#ifndef MATCHMANAGER_DLCLASS_H_
#define MATCHMANAGER_DLCLASS_H_

#include <string>
#include <dlfcn.h>
#include <memory>
#include <iostream>

static const std::string  SO_FILE_ERROR = "Could not load so file: ";

/* A class to manage Dll Handlers */
class DLClass {
private:
	std::shared_ptr<void> dllHandler; //unique_ptr<void> is ill-formed. Causes a compile error, therefore shared_ptr is used instead.
	bool validSoFile;
public:
	DLClass(std::string module):dllHandler(dlopen(module.c_str(), RTLD_LAZY), [](void*){ ; }){
		if(!dllHandler) {
			std::cerr << SO_FILE_ERROR << module << std::endl;
			validSoFile=false;
		}
		else {
			validSoFile=true;
		}
	};
	DLClass (const DLClass& other) {
		dllHandler = other.dllHandler;
		validSoFile = other.validSoFile;
	};
	/* Close so file when this object is the only one that points to the .so file */
	virtual ~DLClass() {
	if (validSoFile && dllHandler.use_count() == 1)
			dlclose(dllHandler.get());
	};
	bool getValidSoFile() const {return validSoFile;};

};

#endif /* MATCHMANAGER_DLCLASS_H_ */
