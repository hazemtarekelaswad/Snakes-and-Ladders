#include "ApplicationManager.h"

#include "Grid.h"
#include "AddLadderAction.h"
#include "AddSnakeAction.h"
#include "AddCardAction.h"
#include "AddCoinSet.h"
#include "RollDiceAction.h"
#include "InputDiceValue.h"
#include "DeleteGameObject.h"
#include "NewGame.h"
#include "ToPlayMode.h"
#include "ToDesignMode.h"
#include "SellCity.h"
#include "OfferMortagage.h"
#include "AcceptMortagage.h"
#include "ReturnMortagage.h"
#include "SaveGrid.h"
#include "OpenGrid.h"
#include "Copy.h"
#include "Cut.h"
#include "Paste.h"

///TODO: Add #include for all action types

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;

	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case ADD_COINS:
		pAct = new AddCoinSet(this);
		break;

	case COPY:
		pAct = new Copy(this);
		break;

	case CUT:
		pAct = new Cut(this);
		break;
	
	case PASTE:
		pAct = new Paste(this);
		break;

	case ACTION_DELETE:
		pAct = new DeleteGameObject(this);
		break;

	case SAVE:
		pAct = new SaveGrid(this);
		break;

	case OPEN_GRID:
		pAct = new OpenGrid(this);
		break;

	case EXIT:
		break;

	case TO_PLAY_MODE:
		pAct = new ToPlayMode(this); ///TODO: temporary till you made its action class (CHANGE THIS LATTER)
		break;

	case ROLL_DICE:
		// create an object of RollDiceAction here
		pAct = new RollDiceAction(this);
		break;

	case ENTER_DICE_VALUE:
		pAct = new InputDiceValue(this);
		break;

	case OFFER_MORTGAGE:
		pAct = new OfferMortagage(this);
		break;

	case ACCEPT_MORTGAGE:
		pAct = new AcceptMortagage(this);
		break;

	case RETURN_MORGAGE:
		pAct = new ReturnMortagage(this);
		break;

	case SELL_CITY:
		pAct = new SellCity(this);
		break;

	case NEW_GAME:
		pAct = new NewGame(this);
		break;

	case TO_DESIGN_MODE:
		pAct = new ToDesignMode(this); ///TODO: temporary till you made its action class (CHANGE THIS LATTER)
		break;

		

		///TODO: Add a case for EACH Action type in the Design mode or Play mode



	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
