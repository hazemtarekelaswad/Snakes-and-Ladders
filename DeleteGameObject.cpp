#include "DeleteGameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Grid.h"
#include "Card.h"
#include "Input.h"
#include "Output.h"

DeleteGameObject::DeleteGameObject(ApplicationManager *pApp):Action(pApp), selectedcell(0, 0)
{
}
void DeleteGameObject::ReadActionParameters()
{
	Grid *pGrid = pManager->GetGrid();
	Output*pOut = pGrid->GetOutput();
	Input*pIn = pGrid->GetInput();

	pOut->PrintMessage("Click on the Game Object you want delete ..");
	selectedcell = pIn->GetCellClicked();//Getting Cell Clicked
	pOut->ClearStatusBar();//Clear statue bar
}

void DeleteGameObject::Execute()
{
	int x,y;
	ReadActionParameters();

	Grid *pGrid = pManager->GetGrid();//Pointer to Grid
	Output*pOut = pGrid->GetOutput();//Pointer to output for printing
	Input*pIn = pGrid->GetInput();//Pointer for input for any click

	
	pGrid->RemoveObjectFromCell(selectedcell);

	pOut->PrintMessage("The selected object has been deleted! Click To Continue ..");
	pIn->GetPointClicked(x,y);
	pOut->ClearStatusBar();
}

DeleteGameObject::~DeleteGameObject()
{
}
