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

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <data file full path> <threshold>\n";
	}
	else{
	std::string filename = argv[1];
	double threshold = std::stod(argv[2]);
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
	int inputSize = 0;
	while(getline(std::cin,input))
	{
		if(input.empty())
        break;
		intervals.push_back(input);
		++inputSize;
	}
	std::string aux;
	
	std::vector<std::string> positions;
	for(int i = 0;i < inputSize; ++i)
	{
		std::stringstream ss(intervals[i]);		
		while(std::getline(ss,aux,':'))
		{
			positions.push_back(aux);
		}
	}
	
	script << "reset\n";
	script << "set terminal png size 3000,750 enhanced font 'Verdana,22'\n";
	script << "set tics font \"Helvetica,18\"\n";
	script << "set style line 12 lc rgb '#808080' lt 0 lw 1\n";
	script << "set grid back ls 12\n";
	script << "unset object\n";
	script << "set output '" << filename << ".png'\n";
	script << "unset log\n";
    script << "unset label\n"; 
    script << "set title \"Bits Per Base\" font \"Verdana:Bold,24\"\n";
	script << "set nokey\n";
	script << "set xlabel \"Base Index\"\n";
	script << "set ylabel \"Bits\" offset 3,0\n";
	script << "set style line 11 lc rgb '#808080' lt 1\n";
	script << "set border 3 back ls 11\n";
	script << "set tics nomirror\n";
	script << "stats '"<< filename << "' using 1:2 name 'data'\n";
	script << "set arrow 1 from graph 0,graph 0.98 to graph 1, graph 0.98 nohead lw 4 lc rgb \"#DC143C\" front\n";
	script << "set arrow 2 from 0, " << threshold << " to data_max_x, " << threshold <<" nohead lw 3 lc rgb \"#FF4500\" front\n";
	script << "set label 1 \"Threshold\" at data_max_x," << threshold <<" rotate left tc rgb \"#FF4500\" font \"Verdana:/Bold,18\" front\n";
	script << "set label 2 \"" << threshold << "\" at data_min_x," << threshold << " offset -3,0 tc rgb \"#FF4500\" font \"Verdana:/Bold,18\" front\n";
	script << "set xrange [data_min_x:data_max_x]\n";
	script << "set yrange [data_min_y - 0.1:data_max_y + 0.15]\n";	
	script << "d = 1/data_max_x\n";
	
	for(int j = 0; j < inputSize * 2; j = j+2)
	{
		script << "set object " << j+1 << " rect from graph (" << positions[j] << "-0.001*data_max_x)*d,graph 1 to graph (" << positions[j+1]  << "+ 0.001*data_max_x)*d,graph 0.96 front fc rgb \"#DC143C\" fs noborder\n"; 
	}
	script << "plot '" << filename << "' w l lw 0.5 lc rgb \"#00008B\"\n";
	script.close();
	}
	return 0;
}
