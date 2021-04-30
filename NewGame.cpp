#include "NewGame.h"
#include "Grid.h"
#include "Player.h"

NewGame::NewGame(ApplicationManager *pApp):Action(pApp)
{
	
}
void NewGame::ReadActionParameters()
{
	// no parameters to read from user
}

void NewGame::Execute()
{
	CellPosition Restart(NumVerticalCells - 1, 0);
	Grid *P = pManager->GetGrid();
	Output *pOut = P->GetOutput();
	Input *pIn = P->GetInput();

	pOut->PrintMessage("You Will begin a New Game | Click to Continue..");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();

	//Here We want to make current player zero then got to for loop with current player0
	P->GetCurrentPlayer();
	while (P->GetCurrentPlayer()->getPlayerNum())
	{
		P->AdvanceCurrentPlayer();
	}

	for(int i = 0; i < MaxPlayerCount; i++)//Because there are 4 Players in the game
	{
		P->UpdatePlayerCell(P->GetCurrentPlayer(), Restart);
		
		//PP = P->GetCurrentPlayer();
		P->GetCurrentPlayer()->SetWallet(100);
		P->GetCurrentPlayer()->SetTurnCount(0);
		for(int i = 7; i <= 11; ++i)
			P->SetCityOwner(NULL, i);
		//in completing Setters in player for turncount and sterpcount PP->Set...(0);
		
		
		P->AdvanceCurrentPlayer();
		
	}
	//Players of course don't End Game IT's just A check
	P->SetEndGame(false);
}
NewGame::~NewGame(void)
{
}
