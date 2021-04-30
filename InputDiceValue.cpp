#include "InputDiceValue.h"

#include "Grid.h"
#include "Player.h"

InputDiceValue::InputDiceValue(ApplicationManager *pApp) : Action(pApp)
{
}

void InputDiceValue::ReadActionParameters()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut= pGrid->GetOutput() ;
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter a Dice Value [1 to 6]: ");
	diceValue = pIn->GetInteger(pOut);
	
	//using while to make sure this loop will not be ended until to achieve condition
	while(diceValue < 1 || diceValue > 6)
	{
		pOut->PrintMessage("ERROR: You have not entered a valid dice number! re-enter a dice number [1 to 6] ..");
		diceValue = pIn->GetInteger(pOut);
	}
	

	// no parameters to read from user
}

void InputDiceValue::Execute()
{
	//First we should get pointer to Grid and for output
	Grid* pGrid = pManager->GetGrid();
	Output* pOut= pGrid->GetOutput() ;
	Input* pIn = pGrid->GetInput();

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

	
	ReadActionParameters();
	// Printing message for input
	int a,b;
	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if(pGrid->GetEndGame())
	{
		pOut->PrintMessage("Game is already ended | Click to continue ..");
		pIn->GetPointClicked(a,b);
		pOut->ClearStatusBar();
		return;
	}

	// -- If not ended, do the following --:
	

	pOut->PrintMessage("Then next player is in turn | Click to continue ..");
	pIn->GetPointClicked(a,b);
	pOut->ClearStatusBar();

	// 2- Get the "current" player from pGrid
	Player *player = pGrid->GetCurrentPlayer();

	if(player->GetBenefit()){
		if(!player->GetNrOfTurnsToBenefit()){
			player->SetBenefit(false);
			pGrid->SetCityOwner(player->GetCityOwner(), player->GetCityNumber());
		}
		player->SetNrOfTurnsToBenefit(player->GetNrOfTurnsToBenefit() - 1);
	}

	// 3- Move the currentPlayer using function Move of class player
	player->Move(pGrid,diceValue);

	// 4- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();


	
}

InputDiceValue::~InputDiceValue()
{
}
