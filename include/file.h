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
	File(std::string name);

	~File();
	
	void OpenFile(std::string name, bool read, bool write);
	void CloseFile();

	void ReadFileAll();
	void ReadFileLine(int line);
	void WriteFileData(sVector data);
	void WriteFileData(std::string data);

private:

	std::fstream _file;
	std::string _fileName;

	bool _reading;
	bool _writing;

	sVector _data;

};
