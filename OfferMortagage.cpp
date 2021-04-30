#include "OfferMortagage.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Cairo_7.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"
#include "Grid.h"
#include "Player.h"

OfferMortagage::OfferMortagage(ApplicationManager *pApp) : Action(pApp)
{
	isValid = true;
}

void OfferMortagage::ReadActionParameters()
{
	Grid *pGrid =  pManager->GetGrid();
	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	outPtr->PrintMessage("Click on the city you want to offer for Mortgage.. ");
	position = inPtr->GetCellClicked();

	outPtr->ClearStatusBar();

	if(!position.IsValidCell()){
		isValid = false;
		return;
	}

	if(!pGrid->HasCard(position)){
		isValid = false;
		return;
	}

	if(pGrid->HasCard(position)->GetCardNumber() < 7 || pGrid->HasCard(position)->GetCardNumber() > 11){
		isValid = false;
		return;
	}

}


void OfferMortagage::Execute()
{
	
		//First we should get pointer to Grid and for output
		Grid *pGrid =  pManager->GetGrid();
		Input *inPtr = pGrid->GetInput();
		Output *outPtr = pGrid->GetOutput();

		ReadActionParameters();

		if(!isValid)
			return;

		Player* currPlayer = pGrid->GetCurrentPlayer();
		Card *pCard = pGrid->HasCard(position);
		int cityNumber = pGrid->HasCard(position)->GetCardNumber();

		if(cityNumber == 7){
			if(!pGrid->GetFirstCard(7))
				return;

			Cairo_7* cityCard7 = dynamic_cast<Cairo_7*>(pCard);
			if(!cityCard7 || !cityCard7->GetCityOwner() || cityCard7->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
				return;

			pGrid->AddMortagage(cityCard7);
		}

		else if(cityNumber == 8){
			if(!pGrid->GetFirstCard(8))
				return;

			Alex_8* cityCard8 = dynamic_cast<Alex_8*>(pCard);
			if(!cityCard8 || !cityCard8->GetCityOwner() || cityCard8->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
				return;

			pGrid->AddMortagage(cityCard8);
		}

		else if(cityNumber == 9){
			if(!pGrid->GetFirstCard(9))
				return;
			Aswan_9* cityCard9 = dynamic_cast<Aswan_9*>(pCard);
			if(!cityCard9 || !cityCard9->GetCityOwner() || cityCard9->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
				return;

			pGrid->AddMortagage(cityCard9);
		}

		else if(cityNumber == 10){
			if(!pGrid->GetFirstCard(10))
				return;
			Luxor_10* cityCard10 = dynamic_cast<Luxor_10*>(pCard);
			if(!cityCard10 || !cityCard10->GetCityOwner() || cityCard10->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
				return;

			pGrid->AddMortagage(cityCard10);
		}

		else if(cityNumber == 11){
			if(!pGrid->GetFirstCard(11))
				return;
			Hurghada_11* cityCard11 = dynamic_cast<Hurghada_11*>(pCard);
			if(!cityCard11 || !cityCard11->GetCityOwner() || cityCard11->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
				return;

			pGrid->AddMortagage(cityCard11);
		}

}

OfferMortagage::~OfferMortagage()
{
}