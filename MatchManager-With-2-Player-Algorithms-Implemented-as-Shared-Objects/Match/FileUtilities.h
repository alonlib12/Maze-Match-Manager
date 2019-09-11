/*
 * FileUtilities.h
 *
 *  Created on: Apr 2, 2019
 *      Author: alon
 */

#ifndef SRC_HEADERS_FILEUTILITIES_H_
#define SRC_HEADERS_FILEUTILITIES_H_

#include <sys/stat.h>
#include <fstream>
#include <list>
#include <string>

/* A utility class for files. */

class FileUtilities {
public:
	FileUtilities();
	virtual ~FileUtilities();
	static bool isExists(const char* filename) {
	  struct stat buffer;
	  return (stat (filename, &buffer) == 0);
	}
	static bool isFile(const char* path) {
		struct stat s;
		if( stat(path,&s) == 0 && (s.st_mode & S_IFREG) ) return true;
		return false;
	}
	static void goToPosition(std::ifstream& file, const char* filename, const std::streampos& oldPos) {
		file.close();
		file.open(filename);
		file.seekg(oldPos); //Go to the position before reading the maze structure.
	};
	static std::list<std::string> makeListOfFilesInDirecroty(const char* path);
};

#endif /* SRC_HEADERS_FILEUTILITIES_H_ */
