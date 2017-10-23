#include "auxFunc.h"
#include <math.h>

char complement(char c)
{
	switch(c)
	{
		case 'A':
			return 'T';
		case 'T':
			return 'A';
		case 'C':
			return 'G';
		case 'G':
			return 'C';
		default:
			return c;
	}
}

void reverseStr(std::string &str, int n)
{
    char temp;
	for (int i=0; i<n/2; i++)
    {
		temp = str[i];
		str[i] = str[n-i-1];
		str[n-i-1] = temp;
	}
}

double logCalc(modelClass *model, std::string context, int baseI, int mIdx)
{
	if(!model->pMap[mIdx].count(context))
	{
		return -log2(model->alpha / (model->alSize * model->alpha));
	}
	else
	{	
		return -log2((model->pMap[mIdx][context].val[baseI] + model->alpha) / (model->pMap[mIdx][context].val[4] + model->alSize * model->alpha));
	}
}
