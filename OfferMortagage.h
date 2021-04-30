#pragma once

#include "Action.h"

class OfferMortagage : public Action
{
	CellPosition position;
	bool isValid;

public:
	OfferMortagage(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~OfferMortagage();
};

