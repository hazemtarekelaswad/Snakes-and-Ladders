#include "Input.h"
#include "Output.h"
#include "Cut.h"
#include "Grid.h"
#include "Card.h"
#include "CoinSet.h"

Cut::Cut(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

Cut::~Cut()
{
}

void Cut::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut ->PrintMessage("Cut Action: Click on the object you want to cut ..");
	// Read the SourceCellPosition
	SourceCellPosition = pIn ->GetCellClicked();
	pOut ->ClearStatusBar();	
}

void Cut::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters(); // Reading the Parameters 

	if (pGrid ->GetGameObjFromCellPosition(SourceCellPosition))
	{
		if(dynamic_cast<Card*>(pGrid->GetGameObjFromCellPosition(SourceCellPosition)) || dynamic_cast<CoinSet*>(pGrid->GetGameObjFromCellPosition(SourceCellPosition) )){
			pGrid ->SetClipboard(pGrid ->GetGameObjFromCellPosition(SourceCellPosition)); // Setting all SourceCellPositionCard data to the clip board
			pGrid ->RemoveObjectFromCell(SourceCellPosition); // Removing the selcted card from the SourceCell
		}
	}
}

