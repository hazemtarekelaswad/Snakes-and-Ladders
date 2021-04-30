#pragma once

#include "Action.h"

class ReturnMortagage : public Action
{

	int citynum;
	bool isValid;

public:
	ReturnMortagage(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~ReturnMortagage();
};


