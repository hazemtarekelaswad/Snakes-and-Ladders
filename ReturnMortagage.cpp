#include "ReturnMortagage.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Cairo_7.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"
#include "Grid.h"
#include "Player.h"

ReturnMortagage::ReturnMortagage(ApplicationManager *pApp) : Action(pApp)
{
	isValid = true;
}

void ReturnMortagage::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut= pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter the mortgaged city number you want to return: ");
	citynum = pIn->GetInteger(pOut);	

	pOut->ClearStatusBar();

	if(citynum < 7 ||citynum > 11){
		isValid = false;
		return;
	}
}




void ReturnMortagage::Execute()
{
	ReadActionParameters();

	if(!isValid)
		return;

	Grid* pGrid = pManager->GetGrid();
	Output* pOut= pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	Player* currPlayer = pGrid->GetCurrentPlayer();

	Card *pCard = pGrid->SearchMortagage(citynum);

	if(!pCard)
		return;

	if(citynum == 7){
		if(!pGrid->GetFirstCard(7))
			return;

		Cairo_7* PCairo = dynamic_cast<Cairo_7*>(pCard);

		if (PCairo->GetOriginalOwner() && PCairo->GetOriginalOwner()->getPlayerNum() == currPlayer->getPlayerNum())
		{
			if(PCairo->GetOriginalOwner()->GetWallet() >= 0.7 * PCairo->GetCityPrice()){
				currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PCairo->GetCityPrice());
				PCairo->GetCityOwner()->SetWallet(PCairo->GetCityOwner()->GetWallet() + 0.7 * PCairo->GetCityPrice());
			
				pGrid->SetCityOwner(PCairo->GetOriginalOwner(), 7);
				pGrid->SetOriginalOwner(NULL, 7);
				pGrid->RemoveMortagage(citynum);
			}
		}
	}

	else if(citynum == 8){
		if(!pGrid->GetFirstCard(8))
			return;

		Alex_8* PAlex = dynamic_cast<Alex_8*>(pCard);

		if (PAlex->GetOriginalOwner() && PAlex->GetOriginalOwner()->getPlayerNum() == currPlayer->getPlayerNum())
		{
			if(PAlex->GetOriginalOwner()->GetWallet() >= 0.7 * PAlex->GetCityPrice()){
				currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PAlex->GetCityPrice());
				PAlex->GetCityOwner()->SetWallet(PAlex->GetCityOwner()->GetWallet() + 0.7 * PAlex->GetCityPrice());
			
				pGrid->SetCityOwner(PAlex->GetOriginalOwner(), 8);
				pGrid->SetOriginalOwner(NULL, 8);
				pGrid->RemoveMortagage(citynum);
			}
		}
	}

	else if(citynum == 9){
		if(!pGrid->GetFirstCard(9))
			return;

		Aswan_9* PAswan = dynamic_cast<Aswan_9*>(pCard);

		if (PAswan->GetOriginalOwner() && PAswan->GetOriginalOwner()->getPlayerNum() == currPlayer->getPlayerNum())
		{
			if(PAswan->GetOriginalOwner()->GetWallet() >= 0.7 * PAswan->GetCityPrice()){
				currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PAswan->GetCityPrice());
				PAswan->GetCityOwner()->SetWallet(PAswan->GetCityOwner()->GetWallet() + 0.7 * PAswan->GetCityPrice());
			
				pGrid->SetCityOwner(PAswan->GetOriginalOwner(), 9);
				pGrid->SetOriginalOwner(NULL, 9);
				pGrid->RemoveMortagage(citynum);
			}
		}
	}

	else if(citynum == 10){
		if(!pGrid->GetFirstCard(10))
			return;

		Luxor_10* PLuxor = dynamic_cast<Luxor_10*>(pCard);

		if (PLuxor->GetOriginalOwner() && PLuxor->GetOriginalOwner()->getPlayerNum() == currPlayer->getPlayerNum())
		{
			if(PLuxor->GetOriginalOwner()->GetWallet() >= 0.7 * PLuxor->GetCityPrice()){
				currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PLuxor->GetCityPrice());
				PLuxor->GetCityOwner()->SetWallet(PLuxor->GetCityOwner()->GetWallet() + 0.7 * PLuxor->GetCityPrice());
			
				pGrid->SetCityOwner(PLuxor->GetOriginalOwner(), 10);
				pGrid->SetOriginalOwner(NULL, 10);
				pGrid->RemoveMortagage(citynum);
			}
		}
	}

	else if(citynum == 11){
		if(!pGrid->GetFirstCard(11))
			return;

		Hurghada_11* PHurghada = dynamic_cast<Hurghada_11*>(pCard);

		if (PHurghada->GetOriginalOwner() && PHurghada->GetOriginalOwner()->getPlayerNum() == currPlayer->getPlayerNum())
		{
			if(PHurghada->GetOriginalOwner()->GetWallet() >= 0.7 * PHurghada->GetCityPrice()){
				currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PHurghada->GetCityPrice());
				PHurghada->GetCityOwner()->SetWallet(PHurghada->GetCityOwner()->GetWallet() + 0.7 * PHurghada->GetCityPrice());
			
				pGrid->SetCityOwner(PHurghada->GetOriginalOwner(), 11);
				pGrid->SetOriginalOwner(NULL, 11);
				pGrid->RemoveMortagage(citynum);
			}
		}
	}


	
}


ReturnMortagage::~ReturnMortagage()
{
}