#pragma once

#include "Action.h"

class OpenGrid : public Action
{
	string FileName;
public:
	OpenGrid(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads OpenGridAction action parameters (FileName)
	
	virtual void Execute(); //  Reads the Parameters of OpenGridAction 
	                        // then opens a saved grid from a FileNmae and re-drawing it
	virtual ~OpenGrid(); // A Virtual Destructor

};
