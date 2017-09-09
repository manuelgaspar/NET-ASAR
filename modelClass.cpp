#include "modelClass.h"

modelClass::modelClass(int cont, double alpha_):context(cont), alSize(4), alpha(alpha_)
{
	initialContext.insert(0,cont,'A');
}

int modelClass::getContext()
{
	return context;
}

std::string modelClass::getInitialContext()
{
	return initialContext;
}

