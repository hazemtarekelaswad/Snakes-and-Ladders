#pragma once

#include "Action.h"

class Paste : public Action
{
	CellPosition DestinationCellPosition;
	bool isValid;
public:

	Paste(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads PasteCard action parameters (DestinationCellPosition)
	
	virtual void Execute(); // Paste the card in the clip board to the destination cell
	
	virtual ~Paste(); // Virtual Destructor
};