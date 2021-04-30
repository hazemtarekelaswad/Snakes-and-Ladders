#include "OpenGrid.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "CoinSet.h"
#include "DecWalletCard_1.h"
#include "NextCard_2.h"
#include "BackwardCard_3.h"
#include "PreventCard_4.h"
#include "FireCard_5.h"
#include "FreezeCard_6.h"
#include "Cairo_7.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"
#include "TakeCityCard_12.h"
#include "LoseCityCard_13.h"
#include "ReturnMortgagedCard_14.h"
#include "BenefitAllCard_15.h"
#include <fstream>

OpenGrid::OpenGrid(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

OpenGrid::~OpenGrid()
{
}

void OpenGrid::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut ->PrintMessage("Enter the name of saved designed grid: ");
	FileName = pIn ->GetSrting(pOut);
	pOut ->ClearStatusBar();
}

void OpenGrid::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ReadActionParameters();

	ifstream InFile(FileName + ".txt");

	if (!InFile){
		pGrid->PrintErrorMessage("ERROR: This File does not exist! Click to continue ... ");
		return;
	}

	if (pGrid->GetNextLadder(CellPosition(1)) || pGrid->GetNextSnake(CellPosition(1)) || pGrid->GetNextCoinSet(CellPosition(1)) || pGrid->GetNextCard(CellPosition(1)))
		pGrid->ClearGridArea();
	

	int nrOfLadders;
	InFile >> nrOfLadders;
	GameObject* pNewObject;

	for (int i = 0; i < nrOfLadders; i++)
	{
		pNewObject = new Ladder;
		pNewObject ->Load(InFile);
		pGrid ->AddObjectToCell(pNewObject);
	}

	int nrOfSnakes;
	InFile >> nrOfSnakes;
	for ( int i = 0; i < nrOfSnakes ; i++)
	{
		pNewObject = new Snake;
		pNewObject ->Load(InFile);
		pGrid ->AddObjectToCell(pNewObject);
	}

	int nrOfCoinSets;
	InFile >> nrOfCoinSets;
	for (int i = 0; i < nrOfCoinSets ; i++)
	{
		pNewObject = new CoinSet;
		pNewObject ->Load(InFile);
		pGrid ->AddObjectToCell(pNewObject);
	}


	int nrOfCards;
	InFile >> nrOfCards;
	for ( int i = 0; i < nrOfCards ; i++)
	{
		int CardNumber;
		InFile >> CardNumber;
		switch ( CardNumber )
		{
		case 1 :
			pNewObject = new DecWalletCard_1;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 2 :
			pNewObject = new NextCard_2;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 3 :
			pNewObject = new BackwardCard_3;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 4 :
			pNewObject = new PreventCard_4;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 5 :
			pNewObject = new FireCard_5();
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 6 :
			pNewObject = new FreezeCard_6;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 7 :
			pNewObject = new Cairo_7;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 8 :
			pNewObject = new Alex_8;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 9:
			pNewObject = new Aswan_9;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 10:
			pNewObject = new Luxor_10;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 11 :
			pNewObject = new Hurghada_11;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 12 :
			pNewObject = new TakeCityCard_12;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 13 :
			pNewObject = new LoseCityCard_13;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 14 :
			pNewObject = new ReturnMortgagedCard_14;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		case 15 :
			pNewObject = new BenefitAllCard_15;
			pNewObject ->Load(InFile);
			pGrid ->AddObjectToCell(pNewObject);
			break;
		}
	}

	InFile.close();
}