#pragma once

#include "Action.h"
#include "NewGame.h"

class ToPlayMode : public Action
{

	// No parameters for this action
	NewGame *newGame;

public:
	ToPlayMode(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~ToPlayMode();
};


