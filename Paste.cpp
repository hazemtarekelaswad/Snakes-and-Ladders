#include "Input.h"
#include "Output.h"
#include "Paste.h"
#include "Grid.h"
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


Paste::Paste(ApplicationManager *pApp) : Action(pApp)
{
	isValid = true; // checkPaste is initially true
	// Initializes the pManager pointer of Action with the passed pointer
}

Paste::~Paste()
{
}

void Paste::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut ->PrintMessage("Paste Action: Click on the cell you want to paste in ..");
	// Read the DestinationCellPosition
	DestinationCellPosition = pIn ->GetCellClicked();

	if (!DestinationCellPosition.IsValidCell())
	{
		pGrid ->PrintErrorMessage("ERROR: You have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	if (DestinationCellPosition.GetCellNum() == 1 || DestinationCellPosition.GetCellNum() == 99 )
	{	
		pGrid->PrintErrorMessage("ERROR: It is not possible to add any game object on the first cell or on the last cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	pOut ->ClearStatusBar();
}

void Paste::Execute() 
{
	Grid* pGrid = pManager->GetGrid();

	ReadActionParameters(); // Reading the Parameters 

	if (!isValid)
		return;

	if (!pGrid ->GetClipboard()){
		pGrid->PrintErrorMessage("ERROR: There is no object to be pasted! Click to continue ...");
		return;
	}

	if(dynamic_cast<Card*>(pGrid->GetClipboard())){
		Card* DestinationCard;
		int cardNr = dynamic_cast<Card*>(pGrid->GetClipboard())->GetCardNumber();
		switch (cardNr)
		{
		case 1:
			DestinationCard = new DecWalletCard_1(*(dynamic_cast <DecWalletCard_1*>(pGrid ->GetClipboard())));
			break;
		case 2:
			DestinationCard = new NextCard_2(*(dynamic_cast <NextCard_2*>(pGrid ->GetClipboard())));
			break;
		case 3:
			DestinationCard = new BackwardCard_3(*(dynamic_cast <BackwardCard_3*>(pGrid ->GetClipboard())));
			break;
		case 4:
			DestinationCard = new PreventCard_4(*(dynamic_cast <PreventCard_4*>(pGrid ->GetClipboard())));
			break;
		case 5:
			DestinationCard = new FireCard_5(*(dynamic_cast <FireCard_5*>(pGrid ->GetClipboard())));
			break;
		case 6:
			DestinationCard = new FreezeCard_6(*(dynamic_cast <FreezeCard_6*>(pGrid ->GetClipboard())));
			break;
		case 7:
			DestinationCard = new Cairo_7(*(dynamic_cast <Cairo_7*>(pGrid ->GetClipboard())));
			break;
		case 8:
			DestinationCard = new Alex_8(*(dynamic_cast <Alex_8*>(pGrid ->GetClipboard())));
			break;
		case 9:
			DestinationCard = new Aswan_9(*(dynamic_cast <Aswan_9*>(pGrid ->GetClipboard())));
			break;
		case 10:
			DestinationCard = new Luxor_10(*(dynamic_cast <Luxor_10*>(pGrid ->GetClipboard())));
			break;
		case 11:
			DestinationCard = new Hurghada_11(*(dynamic_cast <Hurghada_11*>(pGrid ->GetClipboard())));
			break;
		case 12:
			DestinationCard = new TakeCityCard_12(*(dynamic_cast <TakeCityCard_12*>(pGrid ->GetClipboard())));
			break;
		case 13:
			DestinationCard = new LoseCityCard_13(*(dynamic_cast <LoseCityCard_13*>(pGrid ->GetClipboard())));
			break;
		case 14:
			DestinationCard = new ReturnMortgagedCard_14(*(dynamic_cast <ReturnMortgagedCard_14*>(pGrid ->GetClipboard())));
			break;
		case 15:
			DestinationCard = new BenefitAllCard_15(*(dynamic_cast <BenefitAllCard_15*>(pGrid ->GetClipboard())));
			break;
		}

		DestinationCard ->SetPosition(DestinationCellPosition);

		bool added = pGrid ->AddObjectToCell(DestinationCard);	
		if (! added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("ERROR: Cell already has an object! Click to continue ...");
		}

		DestinationCard = NULL;
		return;
	}

	CoinSet* DestinationCoinSet = new CoinSet(*(dynamic_cast <CoinSet*>(pGrid ->GetClipboard())));

	DestinationCoinSet ->SetPosition(DestinationCellPosition);

	bool added = pGrid ->AddObjectToCell(DestinationCoinSet);	
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("ERROR: Cell already has an object! Click to continue ...");
	}
	DestinationCoinSet = NULL;






}
