#pragma once

#include "Action.h"

class AddSnakeAction : public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition startPos; // 1- The start position of the snake
	CellPosition endPos;   // 2- The end position of the snake
	bool isValid; // 3- for checking snake drawing
	// Note: These parameters should be read in ReadActionParameters()

public:

	AddSnakeAction(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddSnakeAction action parameters (startPos, endPos)
	
	virtual void Execute(); // Creates a new snake Object 
	                        // then Sets this snake object to the GameObject Pointer of its Cell
	

	virtual ~AddSnakeAction(); // Virtual Destructor

};

