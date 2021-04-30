#pragma once

#include "Action.h"

class Cut : public Action
{
	CellPosition SourceCellPosition;
public:

	Cut(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CutCard action parameters (SourceCellPosition)
	
	virtual void Execute(); // cuts a card with all its data to the clip board

	virtual ~Cut(); // Virtual Destructor
};