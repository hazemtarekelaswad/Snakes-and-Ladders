#pragma once

#include "Action.h"

class Copy : public Action
{
	CellPosition SourceCellPosition;
public:

	Copy(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CopyCard action parameters (SourceCellPosition)
	
	virtual void Execute(); // copy a card with all its data to the clip board. 
	

	virtual ~Copy(); // Virtual Destructor
};