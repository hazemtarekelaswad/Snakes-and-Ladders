#include "Input.h"
#include "Output.h"
#include "Copy.h"
#include "Grid.h"
#include "Card.h"
#include "CoinSet.h"

Copy::Copy(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

Copy::~Copy()
{
}

void Copy::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut ->PrintMessage("Copy Action: Click on the object you want to copy ..");
	// Read the SourceCellPosition
	SourceCellPosition = pIn ->GetCellClicked();
	pOut ->ClearStatusBar();	
}

void Copy::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters(); // Reading the Parameters 

	if ( pGrid ->GetGameObjFromCellPosition(SourceCellPosition) ){
		if(dynamic_cast<Card*>(pGrid->GetGameObjFromCellPosition(SourceCellPosition)) || dynamic_cast<CoinSet*>(pGrid->GetGameObjFromCellPosition(SourceCellPosition) ))
			pGrid ->SetClipboard(pGrid ->GetGameObjFromCellPosition(SourceCellPosition)); // Setting all SourceCellPositionCard data to the clip board
	}

	pOut ->PrintMessage("The object has been copied! Click to continue ..");
	int x,y;
	pIn->GetPointClicked(x, y);
	pOut ->ClearStatusBar();
}

