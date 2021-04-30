#include "AcceptMortagage.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Cairo_7.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"
#include "Grid.h"
#include "Player.h"

AcceptMortagage::AcceptMortagage(ApplicationManager *pApp) : Action(pApp)
{
	isValid = true;
}

void AcceptMortagage::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut= pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter the city number you want to accept for mortgage: ");
	citynum = pIn->GetInteger(pOut);	

	pOut->ClearStatusBar();

	if(citynum < 7 ||citynum > 11){
		isValid = false;
		return;
	}
}




void AcceptMortagage::Execute()
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

		if (currPlayer->GetWallet() >= 0.7 * PCairo->GetCityPrice())
		{
			pGrid->SetOriginalOwner(PCairo->GetCityOwner(), 7);

			currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PCairo->GetCityPrice());
			PCairo->GetCityOwner()->SetWallet(PCairo->GetCityOwner()->GetWallet() + 0.7 * PCairo->GetCityPrice());
			pGrid->SetCityOwner(currPlayer, 7);
		}
	}


	else if(citynum == 8){
		if(!pGrid->GetFirstCard(8))
			return;

		Alex_8* PAlex = dynamic_cast<Alex_8*>(pCard);

		if (currPlayer->GetWallet() >= 0.7 * PAlex->GetCityPrice())
		{
			pGrid->SetOriginalOwner(PAlex->GetCityOwner(), 8);

			currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PAlex->GetCityPrice());
			PAlex->GetCityOwner()->SetWallet(PAlex->GetCityOwner()->GetWallet() + 0.7 * PAlex->GetCityPrice());
			pGrid->SetCityOwner(currPlayer, 8);
		}
	}


	else if(citynum == 9){
		if(!pGrid->GetFirstCard(9))
			return;

		Aswan_9* PAswan = dynamic_cast<Aswan_9*>(pCard);

		if (currPlayer->GetWallet() >= 0.7 * PAswan->GetCityPrice())
		{
			pGrid->SetOriginalOwner(PAswan->GetCityOwner(),9);

			currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PAswan->GetCityPrice());
			PAswan->GetCityOwner()->SetWallet(PAswan->GetCityOwner()->GetWallet() + 0.7 * PAswan->GetCityPrice());
			pGrid->SetCityOwner(currPlayer, 9);
		}
	}


	else if(citynum == 10){
		if(!pGrid->GetFirstCard(10))
			return;

		Luxor_10* PLuxor = dynamic_cast<Luxor_10*>(pCard);

		if (currPlayer->GetWallet() >= 0.7 * PLuxor->GetCityPrice())
		{
			pGrid->SetOriginalOwner(PLuxor->GetCityOwner(), 10);

			currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PLuxor->GetCityPrice());
			PLuxor->GetCityOwner()->SetWallet(PLuxor->GetCityOwner()->GetWallet() + 0.7 * PLuxor->GetCityPrice());
			pGrid->SetCityOwner(currPlayer, 10);
		}
	}


	else if(citynum == 11){
		if(!pGrid->GetFirstCard(11))
			return;

		Hurghada_11* PHurghada = dynamic_cast<Hurghada_11*>(pCard);

		if (currPlayer->GetWallet() >= 0.7 * PHurghada->GetCityPrice())
		{
			pGrid->SetOriginalOwner(PHurghada->GetCityOwner(), 11);

			currPlayer->SetWallet(currPlayer->GetWallet() - 0.7 * PHurghada->GetCityPrice());
			PHurghada->GetCityOwner()->SetWallet(PHurghada->GetCityOwner()->GetWallet() + 0.7 * PHurghada->GetCityPrice());
			pGrid->SetCityOwner(currPlayer, 11);
		}
	}

}

AcceptMortagage::~AcceptMortagage()
{
}