#pragma once

#include "Action.h"

class SaveGrid : public Action
{
	string FileName;
public:
	SaveGrid(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads SaveGridAction action parameters (FileName)
	
	virtual void Execute(); //  Reads the Parameters of SaveGridAction 
	                        // then calls SaveAll of every gameobject
	virtual ~SaveGrid(); // A Virtual Destructor


};
