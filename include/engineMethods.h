#pragma once

#include <sstream>
#include <iostream>

#include "types.h"

sVector ParseSerializedString(std::string str)
{
	sVector strList;

	std::stringstream stream(str);
	std::string temp;

	stream >> temp;
	
	while (stream)
	{
		if (temp.at(0) == '"')
		{
			if (temp.at(temp.length() - 1) == '"')
			{
				std::string total = temp.substr(1, temp.length() - 2);
				std::cout << total << std::endl;
			}
			else
			{
				//std::cout << temp.substr(1) << std::endl;
				std::string total = temp.substr(1);	

				stream >> temp;
				while (temp.at(temp.length() - 1) != '"')
				{
					total += " " + temp;

					stream >> temp;
				}

				total += " " + temp.substr(0, temp.length() - 1);
				std::cout << total << std::endl;
			}
		}
		else
		{
				std::cout << temp << std::endl;
		}
		stream >> temp;
	}

	return strList;
}
