#ifndef MODELCLASS_H
#define MODELCLASS_H

#include <string>
#include <unordered_map>
#include "valueStruct.h"

class modelClass
{
	private:
	const int context;
	std::string initialContext;	
	
	public:
	const int alSize;
	const double alpha;
	modelClass(int cont, double alpha_);
	std::unordered_map<std::string,values> pMap[3];
	int getContext();
	std::string getInitialContext();
	
};


#endif
