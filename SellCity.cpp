#include "SellCity.h"
#include "Grid.h"
#include "Cairo_7.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"

#define SELL_RATIO 0.9

SellCity::SellCity(ApplicationManager *pApp) : Action(pApp)
{
	isValid = true;
}

void SellCity::ReadActionParameters()
{
	Grid *pGrid =  pManager->GetGrid();
	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	outPtr->PrintMessage("Click on the city you want to sell: ");
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


void SellCity::Execute()
{
	ReadActionParameters();

	if(!isValid)
		return;

	Grid *pGrid = pManager->GetGrid();
	Output *pOut = pGrid->GetOutput();
	Input *pIn = pGrid->GetInput();

	Player* currPlayer = pGrid->GetCurrentPlayer();
	Card *pCard = pGrid->HasCard(position);
	int cityNumber = pGrid->HasCard(position)->GetCardNumber();

	if(cityNumber == 7){
		if(!pGrid->GetFirstCard(7))
			return;

		Cairo_7* cityCard7 = dynamic_cast<Cairo_7*>(pCard);
		if(!cityCard7 || !cityCard7->GetCityOwner() || cityCard7->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
			return;

		currPlayer->SetWallet(currPlayer->GetWallet() + SELL_RATIO * cityCard7->GetCityPrice());
		pGrid->SetCityOwner(NULL, 7);
	}

	else if(cityNumber == 8){
		if(!pGrid->GetFirstCard(8))
			return;

		Alex_8* cityCard8 = dynamic_cast<Alex_8*>(pCard);
		if(!cityCard8 || !cityCard8->GetCityOwner() || cityCard8->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
			return;

		currPlayer->SetWallet(currPlayer->GetWallet() + SELL_RATIO * cityCard8->GetCityPrice());
		pGrid->SetCityOwner(NULL, 8);	
	}

	else if(cityNumber == 9){
		if(!pGrid->GetFirstCard(9))
			return;
		Aswan_9* cityCard9 = dynamic_cast<Aswan_9*>(pCard);
		if(!cityCard9 || !cityCard9->GetCityOwner() || cityCard9->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
			return;

		currPlayer->SetWallet(currPlayer->GetWallet() + SELL_RATIO * cityCard9->GetCityPrice());
		pGrid->SetCityOwner(NULL, 9);
	}

	else if(cityNumber == 10){
		if(!pGrid->GetFirstCard(10))
			return;
		Luxor_10* cityCard10 = dynamic_cast<Luxor_10*>(pCard);
		if(!cityCard10 || !cityCard10->GetCityOwner() || cityCard10->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
			return;

		currPlayer->SetWallet(currPlayer->GetWallet() + SELL_RATIO * cityCard10->GetCityPrice());
		pGrid->SetCityOwner(NULL, 10);
		
	}
		
	else if(cityNumber == 11){
		if(!pGrid->GetFirstCard(11))
			return;
		Hurghada_11* cityCard11 = dynamic_cast<Hurghada_11*>(pCard);
		if(!cityCard11 || !cityCard11->GetCityOwner() || cityCard11->GetCityOwner()->getPlayerNum() != currPlayer->getPlayerNum())
			return;

		currPlayer->SetWallet(currPlayer->GetWallet() + SELL_RATIO * cityCard11->GetCityPrice());
		pGrid->SetCityOwner(NULL, 11);
	}

}

SellCity::~SellCity()
{
}
