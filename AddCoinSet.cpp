#include "AddCoinSet.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "CoinSet.h"

AddCoinSet::AddCoinSet(ApplicationManager *pApp): Action(pApp)
{
	isValid = true;
}// A Constructor

void AddCoinSet::ReadActionParameters()
{
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Coin Set: Enter the amount of coins you want to add for this coin set ...");
	amount = pIn->GetInteger(pOut);

	while (amount < 0)
	{
		pOut -> PrintMessage ("Re-enter a valid value of Amount (it must be positive value)");
		amount = pIn -> GetInteger(pOut);
	}

	pOut->ClearStatusBar();

	pOut->PrintMessage("Click on the cell you want to add Coin Set in ...");
	CoinPosition = pIn ->GetCellClicked();

	if (!CoinPosition.IsValidCell()){

		pGrid ->PrintErrorMessage("The have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	if (CoinPosition.GetCellNum() == 1 || CoinPosition.GetCellNum() == 99)
	{
		pGrid ->PrintErrorMessage("You cannot place game objects in the first or last cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	pOut->ClearStatusBar();

}// Reads Addcoinset action parameters

void AddCoinSet::Execute()
{
	ReadActionParameters();

	if(!isValid)
		return;

	CoinSet* pCoinSet = new CoinSet(amount ,CoinPosition);

	Grid *pGrid = pManager -> GetGrid();
	Output *pOut = pGrid->GetOutput();

	bool added = pGrid->AddObjectToCell(pCoinSet);

	if (! added)
	
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	
	pOut->ClearStatusBar();
}
AddCoinSet::~AddCoinSet()
	{
	}// A Virtual Destructor