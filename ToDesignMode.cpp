#include "ToDesignMode.h"
#include "Player.h"

#include"Grid.h"
//incomplete comparision for the winner player

ToDesignMode::ToDesignMode(ApplicationManager*pApp):Action(pApp)
{
	newGame = new NewGame(pApp);
}

void ToDesignMode::ReadActionParameters()
{}
void ToDesignMode::Execute()
{
	Grid *pG = pManager->GetGrid();
	Output *Out = pG->GetOutput();
	Input *pIn = pG->GetInput();

	Out->PrintMessage("Are You Sure To End This Game? (y / n): ");
	string p = pIn->GetSrting(Out);

	if (p =="Y" || p == "y")
	{
		int wallets[4];
		int stepCounts[4];
		int playerNumbers[4];

		for(int i = 0; i < MaxPlayerCount; ++i){
			wallets[i] = pG->GetCurrentPlayer()->GetWallet();
			stepCounts[i] = pG->GetCurrentPlayer()->GetStepCount();
			playerNumbers[i] = pG->GetCurrentPlayer()->getPlayerNum();

			pG->AdvanceCurrentPlayer();
		}
		pG->AdvanceCurrentPlayer();

		int maxWallet = 0;
		int winnerPlayerNr = 0;
		int maxStepCount = 0;

		for(int i = 0; i < MaxPlayerCount - 1; ++i){
			if(wallets[i] > wallets[i + 1]){
				maxWallet = wallets[i];
				winnerPlayerNr = playerNumbers[i];
			}
			else if(wallets[i] == wallets[i + 1]){

				if(stepCounts[i] > stepCounts[i + 1]){
					maxStepCount = stepCounts[i];
					winnerPlayerNr = playerNumbers[i];
					maxWallet = wallets[i];
				}
				else{
					maxStepCount = stepCounts[i + 1];
					winnerPlayerNr = playerNumbers[i + 1];
					maxWallet = wallets[i];
				}
			}
			else{
				maxWallet = wallets[i + 1];
				winnerPlayerNr = playerNumbers[i + 1];
			}
		}

		Out->PrintMessage("Player " + to_string(winnerPlayerNr) + " is the winner with wallet value " + to_string(maxWallet) + " Coins, Click to continue..");
		int x,y;
		pIn->GetPointClicked(x,y);
		newGame->Execute();

		Out->ClearStatusBar();
		Out->CreateDesignModeToolBar();
	}
	
	else if(p =="n" || p == "N")
		Out->ClearStatusBar();

	else 
	{
		Out->PrintMessage("ERROR: you have not entered a valid answer (y / n) | Click to Continue ..");
		pIn->GetCellClicked();
		Out->ClearStatusBar();
	}
}

ToDesignMode::~ToDesignMode()
{
}
