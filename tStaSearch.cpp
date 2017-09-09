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
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <unistd.h>
#include <vector>
#include <iomanip>


#include "valueStruct.h"
#include "modelClass.h"
#include "auxFunc.h"

using namespace std;

int main(int argc, char *argv[])
{
	int c;
	string file;	
	string search;
	bool invComp = true;
	int contSize = -1;
	double alpha = 	1.0/100;
	
	while ((c = getopt(argc, (char **)argv, "c:f:s:a:ih")) != -1)
	{
        switch(c)
        {
			case 'c':
			contSize = atoi(optarg);
			break;
			case 'f':
			file = optarg;
			break;
			case 's':
			search = optarg;
			break;
			case 'i':
			invComp = false;
			break;
			case 'a':
			alpha = stod(optarg);
			break;
			case 'h':
			default:
			cerr << "Usage: ./tripleModel [options]\n";
			cerr << "options: -c context size(*)\n";
			cerr << setw(11);
			cerr << "-f" << " file name(*)\n";
			cerr << setw(11);
			cerr << "-s" << " gene file name(*)\n";
			cerr << setw(11);
			cerr << "-i" << " (do not include inverted complements)\n";
			cerr << setw(11);
			cerr << "-a" << " alpha (default:1/100)\n";
			cerr << setw(11);
			cerr << "-h" << " (print this help)\n";
			cerr << "Results are directed to standard output.\n";
			cerr << "Note: options marked with (*) are mandatory" << endl;			
			return 0;
		}
    }

	if(contSize == -1 || file.empty() || search.empty())
	{
		cerr << "Mandatory usage: ./tripleModel -c <order> -f <file name>\n";
	}
	
	else{
	
	ifstream fileRead(file,fstream::binary);
	ifstream gene(search,fstream::binary);
	
	if(!gene.is_open())
	{
		cerr << "Error! Check gene file name." << endl;
		return 0;
	}
	if(!fileRead.is_open())
	{
		cerr << "Error! Check file name." << endl;
		return 0;
	}

	auto start = std::chrono::system_clock::now();
	modelClass model(contSize, alpha);
	modelClass modelInv(contSize, alpha);
	char sB;
	int length;
	double bitSimbol = 0, totalBits = 0, bitSimbolInv = 0;
	int mIdx;
	string context = model.getInitialContext();
	char compBase = 'A';	// Initialized as 'A' for first iteration
	string invComplemented;
	invComplemented.resize(contSize);
	/*
	 * Three states construction
	 * */
	 
	gene.seekg(0,ios::end);
	length = gene.tellg();		// Total number of bases
	gene.seekg(0,ios::beg);
	cerr << "Gene: " << length << '\n';
	for(int i = 0; i < length; ++i)
	{
		gene.get(sB);
		mIdx = i % 3;

		switch(sB)
		{
			case 'A':
			model.pMap[mIdx][context].val[0]++;
			break;
			case 'C':
			model.pMap[mIdx][context].val[1]++;
			break;
			case 'G':
			model.pMap[mIdx][context].val[2]++;
			break;
			case 'T':
			model.pMap[mIdx][context].val[3]++;
			break;
			default:
			model.pMap[mIdx][context].val[4]--;
			break;
		}
		
		model.pMap[mIdx][context].val[4]++;
		
		if(invComp)
		{
			transform(context.begin(),context.end(),invComplemented.begin(),complement);	// Complement context
			reverseStr(invComplemented, contSize);
			switch(compBase)
			{
				case 'A':
				modelInv.pMap[mIdx][invComplemented].val[3]++;
				break;
				case 'C':
				modelInv.pMap[mIdx][invComplemented].val[2]++;
				break;
				case 'G':
				modelInv.pMap[mIdx][invComplemented].val[1]++;
				break;
				case 'T':
				modelInv.pMap[mIdx][invComplemented].val[0]++;
				break;
				default:
				modelInv.pMap[mIdx][invComplemented].val[4]--;
				break;
			}
			compBase = context[0];
			modelInv.pMap[mIdx][invComplemented].val[4]++;
		}
		
		context = context + sB;
		context.erase(context.begin());
	}
	gene.close();

	/* 
	 * Bit calculations 
	 * */
	
	fileRead.seekg(0,ios::end);
	length = fileRead.tellg();		// Total number of bases
	vector<double> minBitFrames, minBitFramesInv;
	minBitFrames.reserve(length);
	minBitFramesInv.reserve(length);
	for(int offset = 0; offset < 3; ++offset)
	{
	context = model.getInitialContext();
	fileRead.seekg(0,ios::beg);

	for(int i = 0; i < length; ++i)
	{
		fileRead.get(sB);
		mIdx = (i + offset) % 3;

		switch(sB)
		{
			case 'A':
			bitSimbol = logCalc(&model,context,0,mIdx);
			if(invComp) bitSimbolInv = logCalc(&modelInv,context,0,mIdx);
			break;
			case 'C':
			bitSimbol = logCalc(&model,context,1,mIdx);
			if(invComp) bitSimbolInv = logCalc(&modelInv,context,1,mIdx);
			break;
			case 'G':
			bitSimbol = logCalc(&model,context,2,mIdx);
			if(invComp) bitSimbolInv = logCalc(&modelInv,context,2,mIdx);
			break;
			case 'T':
			bitSimbol = logCalc(&model,context,3,mIdx);
			if(invComp) bitSimbolInv = logCalc(&modelInv,context,3,mIdx);
			break;
			default:
			bitSimbol = 2;
			if(invComp) bitSimbolInv = 2;
			break;
		}
		
		if(offset == 0)
		{
			minBitFrames[i] = bitSimbol;
			if(invComp) minBitFramesInv[i] = bitSimbolInv;
		}		
		
		else 
		{
			if(bitSimbol < minBitFrames[i])
			{
				minBitFrames[i] = bitSimbol;
			}
			if(invComp && bitSimbolInv < minBitFramesInv[i])
			{
				minBitFramesInv[i] = bitSimbolInv;
			}
		}
		
		context = context + sB;
		context.erase(context.begin());

	}
	}
	fileRead.close();
	double minimumValue;
	for(int j = 0; j < length; ++j)
	{
		if(invComp)
		{
			minimumValue = std::min(minBitFrames[j],minBitFramesInv[j]);
			totalBits += minimumValue;
			cout << minimumValue << '\n';
		}
		else
		{
			totalBits += minBitFrames[j];
			cout << minBitFrames[j] << '\n';
		}
	}
	
	cerr << "Total bits: " << totalBits << '\n';
	cerr << "Length: " << length << '\n';
	cerr << "Bits per simbol: " << totalBits/length << '\n';
	
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cerr << elapsed.count() << " ms\n";
	}
	return 0;
}
