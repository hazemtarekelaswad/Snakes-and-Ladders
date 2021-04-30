#pragma once

#include "Action.h"

class SellCity : public Action
{
	bool isValid;
	CellPosition position;

public:
	SellCity(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SellCity();
};

