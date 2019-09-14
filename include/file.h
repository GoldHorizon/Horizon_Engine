#pragma once

#include "types.h"

#include <fstream>
#include <iostream>
#include <sys/stat.h>

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
	int UpdateFileInfo();
	time_t GetModifyTime();
	bool IsOutdated();

	void SetFilePos(std::ios_base::seekdir pos, int offset = 0);

	void PrintData();
	std::vector<std::string>& GetDataVector();

private:

	/*
	 * Private Attributes
	 */
	std::fstream _file;
	std::string _fileName;

	bool _reading;
	bool _writing;

	std::vector<std::string> _data;

	struct stat _fileInfo;
	time_t _lastModifyTime;

};
