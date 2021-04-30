#include "AddCardAction.h"
#include "Input.h"
#include "Output.h"
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

AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	isValid = true;
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces

	Grid *pGrid =  pManager->GetGrid();
	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	// 2- Read the "cardNumber" parameter and set its data member

	outPtr->PrintMessage("New Card | Enter the card number you want to add [1 --> 15]: ");
	cardNumber = inPtr->GetInteger(outPtr);

	if(cardNumber > 15 || cardNumber < 1){
		pGrid->PrintErrorMessage("ERROR: You have not entered a valid card number! it must be between 1 and 15 | Click to continue ...");
		outPtr->ClearStatusBar();
		isValid = false;
		return;
	}
	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	outPtr->PrintMessage("Click on the cell you want to add this card on ...");
	cardPosition = inPtr->GetCellClicked();

	// 4- Make the needed validations on the read parameters

	if (!cardPosition.IsValidCell()){
		pGrid ->PrintErrorMessage("ERROR: You have not selected a valid cell! Click to continue ...");
		outPtr->ClearStatusBar();
		isValid = false;
		return;
	}

	if (cardPosition.GetCellNum() == 1 || cardPosition.GetCellNum() == 99)
	{
		pGrid ->PrintErrorMessage("ERROR: It is not possible to add any game object on the first cell or on the last cell! Click to continue ...");
		outPtr->ClearStatusBar();
		isValid = false;
		return;
	}

	// 5- Clear status bar
	outPtr->ClearStatusBar();
}

void AddCardAction::Execute() 
{

	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	if(!isValid) // if it is not a valid input or cell, cancel the operation
		return;

	// 2- Switch case on cardNumber data member and create the appropriate card object type
	
	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new DecWalletCard_1(cardPosition);
		break;
	case 2:
		pCard = new NextCard_2(cardPosition);
		break;
	case 3:
		pCard = new BackwardCard_3(cardPosition);
		break;
	case 4:
		pCard = new PreventCard_4(cardPosition);
		break;
	case 5:
		pCard = new FireCard_5(cardPosition);
		break;
	case 6:
		pCard = new FreezeCard_6(cardPosition);
		break;
	case 7:
		pCard = new Cairo_7(cardPosition);
		break;
	case 8:
		pCard = new Alex_8(cardPosition);
		break;
	case 9:
		pCard = new Aswan_9(cardPosition);
		break;
	case 10:
		pCard = new Luxor_10(cardPosition);
		break;
	case 11:
		pCard = new Hurghada_11(cardPosition);
		break;
	case 12:
		pCard = new TakeCityCard_12(cardPosition);
		break;
	case 13:
		pCard = new LoseCityCard_13(cardPosition);
		break;
	case 14:
		pCard = new ReturnMortgagedCard_14(cardPosition);
		break;
	case 15:
		pCard = new BenefitAllCard_15(cardPosition);
		break;
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid *pGrid = pManager->GetGrid();
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);
		// C- Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pCard);
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if(!added)
			pGrid->PrintErrorMessage("ERROR: Cell already has an object! Click to continue ...");
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
