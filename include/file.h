#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

typedef std::vector<std::string> sVector;

class File
{
public:
	File();

	~File();
	
	void OpenFile(std::string name, bool read = true, bool write = true);
	void CloseFile();

	void ReadFileAll();
	void ReadFileLine(int line = -1);
	void WriteFileData();
	void WriteFileLine(std::string data);

	void SetFilePos(std::ios_base::seekdir pos, int offset = 0);

	void PrintData();
	sVector* GetDataVector();

private:

	std::fstream _file;
	std::string _fileName;

	bool _reading;
	bool _writing;

	sVector _data;

};
