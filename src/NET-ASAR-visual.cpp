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

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <libgen.h>
#include <iomanip>
#include <unistd.h>


int main(int argc, char *argv[])
{	
	int c;
	std::string filename;
	double threshold = 100.1;
	std::string sourceFile;
	bool extract = false;
	
	while ((c = getopt(argc, (char **)argv, "f:t:e:h")) != -1)
	{
        switch(c)
        {
			case 'f':
			filename = optarg;
			break;
			case 't':
			threshold = std::stod(optarg);
			break;
			case 'e':
			sourceFile = optarg;
			extract = true;
			break;
			case 'h':
			default:	
			std::cerr << "Usage: " << argv[0] << " [options]\n";
			std::cerr << "options: -f data file full path(*)\n";
			std::cerr << std::setw(11) << "-t" << " threshold value(*)\n";	
			std::cerr << std::setw(11) << "-e" << " full path of file containing sequence to be extracted from\n";
			std::cerr << std::setw(11) << "-h" << " (print this help)\n";
			std::cerr << "Note: options marked with (*) are mandatory" << std::endl;
			return 0;
		}
	}
	if(filename.empty() | (threshold == 100.1))
	{
		std::cerr << "Mandatory usage: " << argv[0] << " -f <data file full path> -t <threshold>\n";
	}
	else{

	std::string directory;
	const size_t last_slash_idx = filename.rfind('/');
	if (std::string::npos != last_slash_idx)
	{
		directory = filename.substr(0, last_slash_idx);
	}
	std::string scriptDirectory = directory + "/plotScript.gp";
	std::ofstream script(scriptDirectory);
	std::vector<std::string> intervals;
	std::string input;
	
	std::ifstream extractIn(sourceFile,std::fstream::binary);
	if(!extractIn && extract)
	{
		std::cerr << "Source file does not exist!" << std::endl;
		return 0;
	}
	std::string name = filename + "_segment_";
	int inputSize = 0;
	while(getline(std::cin,input))
	{
		if(input.empty())
        break;
		intervals.push_back(input);
		++inputSize;
	}
	std::string auxS;
	
	std::ofstream extractOut[inputSize];
	std::vector<std::string> positions;
	for(int i = 0;i < inputSize; ++i)
	{
		std::stringstream ss(intervals[i]);		
		while(std::getline(ss,auxS,':'))
		{
			positions.push_back(auxS);
		}
		if(extract){ extractOut[i].open(name + std::to_string(i+1), std::ofstream::out | std::ofstream::binary);}
	}
	
	script << "reset\n";
	script << "set terminal png size 3000,750 enhanced font 'Verdana,30'\n";
	script << "set tics font \"Helvetica,26\"\n";
	script << "set style line 12 lc rgb '#000000' lt 0 lw 1\n";
	script << "set grid back ls 12\n";
	script << "unset object\n";
	script << "set output '" << filename << ".png'\n";
	script << "unset log\n";
	script << "unset label\n"; 
	script << "set nokey\n";
	script << "set xlabel \"Base Index\" offset 0,0.5\n";
	script << "set ylabel \"Bits\" offset 3,0\n";
	script << "set style line 11 lc rgb '#000000' lt 1\n";
	script << "set border 3 back ls 11\n";
	script << "set tics nomirror\n";
	script << "stats '" << filename << "' using 1:2 name 'data'\n";
	script << "set arrow 1 from graph 0,graph 0.98 to graph 1, graph 0.98 nohead lw 4 lc rgb \"#DC143C\" front\n";
	script << "set arrow 2 from 0, " << threshold << " to data_max_x, " << threshold <<" nohead lw 3 lc rgb \"#FF4500\" front\n";
	script << "set label 1 \"Threshold\" at data_max_x," << threshold <<" rotate left tc rgb \"#FF4500\" font \"Verdana:/Bold,30\" front\n";
	script << "set label 2 \"" << threshold << "\" at data_min_x," << threshold << " offset -3,0 tc rgb \"#FF4500\" font \"Verdana:/Bold,30\" front\n";
	script << "set xrange [data_min_x:data_max_x]\n";
	script << "set yrange [data_min_y - 0.1:data_max_y + 0.15]\n";	
	script << "d = 1/data_max_x\n";

	int idx = 0;
	
	char seg;
	int start, end, aux;
	
	for(int j = 0; j < inputSize * 2; j = j+2)
	{
		if(extract)
		{
			start = std::stoi(positions[j]);
			end = std::stoi(positions[j+1]);
			aux = start;
			for(int i = 0;i < end-start;++i)
			{
				extractIn.seekg(aux);
				extractIn.get(seg);
				extractOut[idx] << seg;
				++aux;
			}
			++idx;
		}
		script << "set object " << j+1 << " rect from graph (" << positions[j] << "-0.005*data_max_x)*d,graph 1 to graph (" << positions[j+1]  << "+ 0.005*data_max_x)*d,graph 0.96 front fc rgb \"#DC143C\" fs noborder\n"; 

	}
	script << "plot '" << filename << "' w l lw 0.5 lc rgb \"#00008B\"\n";
	script.close();
	
	if(extract)
	{
		for(int i = 0;i < inputSize;++i)
		{
			extractOut[i].close();
		}
	}
	}
	return 0;

}
