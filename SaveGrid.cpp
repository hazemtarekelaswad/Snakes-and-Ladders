#include "SaveGrid.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>

SaveGrid::SaveGrid(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

SaveGrid::~SaveGrid()
{
}

void SaveGrid::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

    pOut ->PrintMessage("Name the file to save: ");
	FileName = pIn ->GetSrting(pOut);
	pOut ->ClearStatusBar();
}

void SaveGrid::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();

	ofstream OutFile(FileName + ".txt");

	OutFile << pGrid->GetNumberOfGameObject(LADDERS) << std::endl;
	pGrid->SaveAll(OutFile, LADDERS);

	OutFile << pGrid->GetNumberOfGameObject(SNAKES) << std::endl;
	pGrid->SaveAll(OutFile, SNAKES);

	OutFile << pGrid->GetNumberOfGameObject(COINSETS) << std::endl;
	pGrid->SaveAll(OutFile, COINSETS);

	OutFile << pGrid->GetNumberOfGameObject(CARDS) << std::endl;
	pGrid->SaveAll(OutFile, CARDS);

	OutFile.close();
}