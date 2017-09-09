#ifndef AUXFUNC_H
#define AUXFUNC_H

#include <string>
#include "modelClass.h"

char complement(char c);
void reverseStr(std::string &str, int n);
double logCalc(modelClass *model, std::string context, int baseI, int mIdx);

#endif
