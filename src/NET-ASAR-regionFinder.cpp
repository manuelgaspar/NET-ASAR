/*
	Copyright (C) 2017  Manuel Gaspar

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <iomanip>
#include <map>

int main(int argc, char *argv[])
{
	int pos;
	double bits, prevBits = 20;
	bool ordered = false;
	double min = 100.1;
	std::string file;
	int c;
	while ((c = getopt(argc, (char **)argv, "f:t:eh")) != -1)
	{
        switch(c)
        {
			case 'f':
			file = optarg;
			break;
			case 't':
			min = std::stod(optarg);
			break;
			case 'e':
			ordered = true;
			break;
			case 'h':
			default:	
			std::cerr << "Usage: " << argv[0] << " [options]\n";
			std::cerr << "options: -f filtered values file(*)\n";
			std::cerr << std::setw(11) << "-t" << " threshold value(*)\n";	
			std::cerr << std::setw(11) << "-e" << " (print regions including minimum entropy)\n";
			std::cerr << std::setw(11) << "-h" << " (print this help)\n";
			std::cerr << "Note: options marked with (*) are mandatory" << std::endl;
			return 0;
		}
	}

	if(file.empty() | (min == 100.1))
	{
		std::cout << "Mandatory usage: " << argv[0] << " -f <filtered values file> -t <threshold value>\n";
		return 1;
	}

	
	bool first = true;
	std::multimap<double,std::string> intervals;
	std::multimap<double,std::string>::iterator it;
	
	int initPos = 0, finalPos = 0;
	
	std::ifstream data(file);

	std::string aux;
	
	while(data >> pos >> bits)
	{
		if(bits <= min)
		{
			if(prevBits > bits)
			{
				prevBits = bits;
			}
			if(first)
			{
				initPos = pos;
				first = false;

			}
			if(!first)
			{
				finalPos = pos;
			}
		}
		else
		{
			if(!first)
			{
				aux = std::to_string(initPos)+":"+std::to_string(finalPos);
				intervals.insert(std::pair<double,std::string>(prevBits,aux));
				first = true;
				prevBits = 20;
			}
		}
		
	}
	
	for (it=intervals.begin(); it!=intervals.end(); ++it)
	{
		if(!ordered)
		{	
			std::cout << (*it).second << '\n';
		}
		else
		{
			std::cout << (*it).second << " - Minimum entropy in region: " << (*it).first << '\n';
		}
	}
	return 0;
}
