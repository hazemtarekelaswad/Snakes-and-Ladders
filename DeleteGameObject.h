#pragma once

#include "Action.h"


class DeleteGameObject: public Action
{

	CellPosition selectedcell;

public:
	DeleteGameObject(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~DeleteGameObject();
};


