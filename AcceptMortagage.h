#pragma once

#include "Action.h"

class AcceptMortagage : public Action
{
	int citynum;
	bool isValid;
	
public:
	AcceptMortagage(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~AcceptMortagage();
};

