#pragma once

#include "Action.h"
#include "NewGame.h"
class ToDesignMode : public Action
{
	NewGame *newGame;
	// No parameters for this action

public:
	ToDesignMode(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~ToDesignMode();
};

