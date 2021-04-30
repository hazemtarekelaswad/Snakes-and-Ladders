#include "ReturnMortgagedCard_14.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Cairo_7.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"
#include "Grid.h"
#include<iostream>
#include<vector>
#include<algorithm>


ReturnMortgagedCard_14::ReturnMortgagedCard_14(const CellPosition & pos) : Card(pos)
{
	cardNumber = 14;
}

ReturnMortgagedCard_14::ReturnMortgagedCard_14(){
	cardNumber = 14;
}

void ReturnMortgagedCard_14::Apply(Grid* pGrid, Player* pPlayer){
	Card::Apply(pGrid, pPlayer);

	Output* outPtr = pGrid->GetOutput();
	Input* inPtr = pGrid->GetInput();

	Card *pCard;
	Player* originalPlayer;
	std::vector<int> mortgagedCityPrices;
	std::vector<int> cityNumbers;
	int price;

	for(int i = 7; i <= 11; ++i){

		pCard = pGrid->SearchMortagage(i);

		if(!pCard)
			continue;

		switch(i){
		case 7:
			originalPlayer = dynamic_cast<Cairo_7*>(pCard)->GetOriginalOwner();
			price = dynamic_cast<Cairo_7*>(pCard)->GetCityPrice();
			break;
		case 8:
			originalPlayer = dynamic_cast<Alex_8*>(pCard)->GetOriginalOwner();
			price = dynamic_cast<Alex_8*>(pCard)->GetCityPrice();
			break;
		case 9:
			originalPlayer = dynamic_cast<Aswan_9*>(pCard)->GetOriginalOwner();
			price = dynamic_cast<Aswan_9*>(pCard)->GetCityPrice();
			break;
		case 10: 
			originalPlayer = dynamic_cast<Luxor_10*>(pCard)->GetOriginalOwner();
			price = dynamic_cast<Luxor_10*>(pCard)->GetCityPrice();
			break;
		case 11:
			originalPlayer = dynamic_cast<Hurghada_11*>(pCard)->GetOriginalOwner();
			price = dynamic_cast<Hurghada_11*>(pCard)->GetCityPrice();
			break;
		}
		
		if(originalPlayer->getPlayerNum() != pPlayer->getPlayerNum() || !originalPlayer)
			continue;

		mortgagedCityPrices.push_back(price);
		cityNumbers.push_back(i);
	}

	if(!mortgagedCityPrices.size()){
		pGrid->PrintErrorMessage("There is no mortgaged cities found. Click to continue..");
		outPtr->ClearStatusBar();
		return;
	}

	int minPricedCityNumber = cityNumbers.at(std::min_element(mortgagedCityPrices.begin(), mortgagedCityPrices.end()) - mortgagedCityPrices.begin());

	outPtr->PrintMessage("You have got back your mortgaged city (number " + to_string(minPricedCityNumber) + ") for free. Click to continue ...");

	int x,y;
	inPtr->GetPointClicked(x, y);
	outPtr->ClearStatusBar();

	pGrid->SetOriginalOwner(NULL, minPricedCityNumber);
	pGrid->SetCityOwner(pPlayer, minPricedCityNumber);
	pGrid->RemoveMortagage(minPricedCityNumber);

}

ReturnMortgagedCard_14::~ReturnMortgagedCard_14()
{
}

void ReturnMortgagedCard_14::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}
