#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"
#include "PreventCard_4.h"
#include "FreezeCard_6.h"
#include "BenefitAllCard_15.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp), count(0)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
	//First we should get pointer to Grid and for output
	Grid* pGrid = pManager->GetGrid();
	Output* pOut= pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int a,b;

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if(pGrid->GetEndGame())
	{
		pOut->PrintMessage("Game is already Ended");
		pIn->GetPointClicked(a,b);
		pOut->ClearStatusBar();
		return;
	}

	// -- If not ended, do the following --:
	pOut->PrintMessage("Then next player is in turn | Click to continue ..");
	pIn->GetPointClicked(a,b);
	pOut->ClearStatusBar();

	Player *preventedPlayer = pGrid->GetCurrentPlayer();

	if(preventedPlayer->getPreventState()){
		preventedPlayer->Move(pGrid, 0);

		if(preventedPlayer->GetFreeze()){
			preventedPlayer->SetNrOfTurnsToFreeze(preventedPlayer->GetNrOfTurnsToFreeze() - 1);
			if(!preventedPlayer->GetNrOfTurnsToFreeze()){
				preventedPlayer->setPreventState(false);
				preventedPlayer->SetFreeze(false);
			}
			pGrid->AdvanceCurrentPlayer();
			return;
		}

		preventedPlayer->setPreventState(false);
		pGrid->AdvanceCurrentPlayer();
		return;
	}

	// 2- Generate a random number from 1 to 6 --> This step is done for you
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed
	//NEEDED TO GET DICENUMBER IN MASSAGE
	pOut->PrintMessage("The Roll Dice is " + to_string(diceNumber));
	pIn->GetPointClicked(a,b);
	pOut->ClearStatusBar();
	// 3- Get the "current" player from pGrid
	Player *player = pGrid->GetCurrentPlayer();

	if(player->GetBenefit()){
		if(!player->GetNrOfTurnsToBenefit()){
			player->SetBenefit(false);
			pGrid->SetCityOwner(player->GetCityOwner(), player->GetCityNumber());
		}
		player->SetNrOfTurnsToBenefit(player->GetNrOfTurnsToBenefit() - 1);
	}

	// 4- Move the currentPlayer using function Move of class player
	player->Move(pGrid, diceNumber);

	// 5- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();


	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

RollDiceAction::~RollDiceAction()
{
}
