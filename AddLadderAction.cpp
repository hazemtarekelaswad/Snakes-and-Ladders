#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	isValid = true;
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	if (!startPos.IsValidCell())
	{
		pGrid ->PrintErrorMessage("ERROR: You have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid= false;
		return;
	}


	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();


	///TODO: Make the needed validations on the read parameters
	if (!endPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("ERROR: You have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}


	if (startPos.GetCellNum() == endPos.GetCellNum())
	{
		pGrid ->PrintErrorMessage("ERROR: It is not possible for Start Cell and End Cell to be the same! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	if ( pGrid ->GetGameObjFromCellPosition(endPos) && dynamic_cast<Snake*>(pGrid ->GetGameObjFromCellPosition(endPos)) )
	{
		Snake* overlappedSnake = dynamic_cast<Snake*>(pGrid->GetGameObjFromCellPosition(endPos));
		if (overlappedSnake->GetPosition().GetCellNum() == endPos.GetCellNum())
		{
			pGrid ->PrintErrorMessage("ERROR: You can not add the Ladder exactly on a Snake! Click to continue ...");
			pOut->ClearStatusBar();
			isValid = false;
			return;
		}
	}

	if ( pGrid ->GetGameObjFromCellPosition(endPos) && dynamic_cast<Ladder*>(pGrid ->GetGameObjFromCellPosition(endPos)) )
	{
		Ladder* overlappedLadder = dynamic_cast<Ladder*>(pGrid->GetGameObjFromCellPosition(endPos));
		if ( overlappedLadder->GetPosition().GetCellNum() == endPos.GetCellNum())
		{
			pGrid ->PrintErrorMessage("ERROR: You can not add another ladder exactly on this Ladder! Click to continue ...");
			pOut->ClearStatusBar();
			isValid = false;
			return;
		}
	}


	if (startPos.GetCellNum() == 1 || endPos.GetCellNum() == 99 )
	{
		pGrid ->PrintErrorMessage("ERROR: It is not possible to add any game object on the first cell or on the last cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}


	if (endPos.GetCellNum() < startPos.GetCellNum())
	{
		pGrid ->PrintErrorMessage("ERROR: It is not allowed for the Start Cell to be larger than the End Cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}


	if (endPos.HCell() != startPos.HCell())
	{
		pGrid ->PrintErrorMessage("ERROR: Try to select Start cell and End cell such that they are in the same column! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	for(int i = startPos.GetCellNum(); i <= endPos.GetCellNum(); i += NumHorizontalCells){
		if(pGrid->GetGameObjFromCellPosition(CellPosition(i)) && dynamic_cast<Ladder*>(pGrid->GetGameObjFromCellPosition(CellPosition(i)))){

			pGrid ->PrintErrorMessage("ERROR: It is not possible for two ladders to overlap! Click to continue ...");
			pOut->ClearStatusBar();
			isValid = false;
			return;
		}
	}

	for(int i = NumVerticalCells - 1; i > 0; --i){
		if(pGrid->GetGameObjFromCellPosition(CellPosition(i, startPos.HCell())) && dynamic_cast<Ladder*>(pGrid->GetGameObjFromCellPosition(CellPosition(i, startPos.HCell())))){
			Ladder* overlappedLadder = dynamic_cast<Ladder*>(pGrid->GetGameObjFromCellPosition(CellPosition(i, startPos.HCell())));

			if(startPos.VCell() < overlappedLadder->GetPosition().VCell() && startPos.VCell() >= overlappedLadder->GetEndPosition().VCell() ){
				pGrid ->PrintErrorMessage("ERROR: It is not possible for two ladders to overlap! Click to continue ...");
				pOut->ClearStatusBar();
				isValid = false;
				return;
			}
		}

		else if(pGrid->GetGameObjFromCellPosition(CellPosition(i, startPos.HCell())) && dynamic_cast<Snake*>(pGrid->GetGameObjFromCellPosition(CellPosition(i, startPos.HCell())))){
			Snake* overlappedSnake = dynamic_cast<Snake*>(pGrid->GetGameObjFromCellPosition(CellPosition(i, startPos.HCell())));

			if(startPos.VCell() == overlappedSnake->GetEndPosition().VCell()){
				pGrid ->PrintErrorMessage("ERROR: You can not select Ladder's End cell to be on a Snake start cell! Click to continue ...");
				pOut->ClearStatusBar();
				isValid = false;
				return;
			}
		}
	}

	///TODO: Make the needed validations on the read parameters
	// Clear messages
	pOut->ClearStatusBar();
}




// Execute the action
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	if(!isValid)
		return;
	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("ERROR: Cell already has an object! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
