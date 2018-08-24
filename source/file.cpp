#include "../include/file.h"

File::File() : 	
	_reading(false),
	_writing(false)
{
}

File::~File()
{

}

void File::OpenFile(std::string name, bool read, bool write)
{
	_fileName = name;
	_reading = read;
	_writing = write;

	if (_file.is_open()) _file.close();

	if (read)
	{
		if (write) _file.open(_fileName.c_str(), std::ios_base::in | std::ios_base::out);
		else _file.open(_fileName.c_str(), std::ios_base::in);
	}
	else
	{
		if (write) _file.open(_fileName.c_str(), std::ios_base::out);
		else std::cout << "Error: cannot open file with read or write" << std::endl;
	}
}

void File::CloseFile()
{
	if (_file.is_open()) _file.close();
	else std::cout << "File not open!" << std::endl;
}

void File::ReadFileAll()
{
	if (_file.is_open())
	{
		// Empty out the current data
		while (_data.size() > 0)
			_data.pop_back();

		while (_file)
		{
			std::string line;

			std::getline(_file, line);
			if (line != "")
				_data.push_back(line);
		}

		SetFilePos(std::ios_base::end);
	}	
	else std::cout << "File not open!" << std::endl;
}

void File::ReadFileLine(int line)
{
	// @Todo: implement if needed
	std::cout << "Attempted to read single line from file while not implemented!" << std::endl;
}

void File::WriteFileData()
{
	if (_file.is_open())
	{
		for (int i = 0; i < _data.size(); i++)
			_file << _data[i] << std::endl;
	}
	else std::cout << "File not open!" << std::endl;

}

void File::WriteFileLine(std::string data)
{
	if (_file.is_open())
	{
		_file << data << std::endl;	
	}
	else std::cout << "File not open!" << std::endl;
}

bool File::IsOpen()
{
	return _file.is_open();
}

void File::SetFilePos(std::ios_base::seekdir pos, int offset)
{
	if (_file.is_open())
	{
		_file.seekp(offset, pos);
		_file.clear();
	}
	else std::cout << "File not open!" << std::endl;
}

void File::PrintData()
{
	std::cout << ">>>>>>>>>> Printing data contents for file " << _fileName << std::endl;
	for (int i = 0; i < _data.size(); i++)
		std::cout << _data[i] << std::endl;
	std::cout << "<<<<<<<<<< End print of data contents." << std::endl;
}

sVector* File::GetDataVector()
{
	return &_data;	
}

