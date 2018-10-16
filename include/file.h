#pragma once

#include "types.h"

#include <fstream>
#include <iostream>

class File
{
public:
	/*
	 * Constructors/Destructors
	 */
	File();
	~File();
	
	/*
	 * Class Methods
	 */
	void OpenFile(std::string name, bool read = true, bool write = true);
	void CloseFile();

	void ReadFileAll();
	void ReadFileLine(int line = -1);
	void WriteFileData();
	void WriteFileLine(std::string data);

	bool IsOpen();

	void SetFilePos(std::ios_base::seekdir pos, int offset = 0);

	void PrintData();
	sVector* GetDataVector();

private:

	/*
	 * Private Attributes
	 */
	std::fstream _file;
	std::string _fileName;

	bool _reading;
	bool _writing;

	sVector _data;

};
