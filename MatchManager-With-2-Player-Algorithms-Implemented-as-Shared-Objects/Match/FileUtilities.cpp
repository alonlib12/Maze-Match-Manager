/*
 * FileUtilities.cpp
 *
 *  Created on: May 5, 2019
 *      Author: Alon Liberman
 */



#include "FileUtilities.h"
#include <dirent.h>
using namespace std;

list<string> FileUtilities::makeListOfFilesInDirecroty(const char* path) {
	struct dirent *entry = nullptr;
		DIR *dp = nullptr;
		list<string> files;
		dp = opendir(path);
		if (dp != nullptr) {
			while ((entry = readdir(dp))) {
				string filePath = string(path) + string(entry->d_name);
				if (isFile(filePath.c_str())) //If current filePath is a file then add to list.
					files.push_back(entry->d_name);
			}
		}
		closedir(dp);
		return files;
}
