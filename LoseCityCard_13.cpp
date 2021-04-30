#include"LoseCityCard_13.h"
#include "Cairo_7.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"
#include<iostream>
#include<vector>
#include<algorithm>


LoseCityCard_13::LoseCityCard_13(const CellPosition &pos) : Card(pos){
	cardNumber = 13;
}

LoseCityCard_13::LoseCityCard_13(){
	cardNumber = 13;
}

LoseCityCard_13::~LoseCityCard_13(){}


void LoseCityCard_13::Apply(Grid *pGrid, Player *pPlayer){
	Card::Apply (pGrid, pPlayer);

	std::vector<int> cityPrices;
	std::vector<int> cityNumbers;
	std::vector<int> mortgagedCityNumbers;

	Card* cityCard;
	Player* ownerPlayer;
	Player* originalPlayer;
	int cityPrice;

	for(int i = 7; i <= 11; ++i){
		cityCard = pGrid->GetFirstCard(i);

		if(!cityCard)
			continue;

		switch (i){
		case 7:
			ownerPlayer = dynamic_cast<Cairo_7*>(cityCard)->GetCityOwner();
			originalPlayer = dynamic_cast<Cairo_7*>(cityCard)->GetOriginalOwner();
			cityPrice = dynamic_cast<Cairo_7*>(cityCard)->GetCityPrice();
			break;
		case 8:
			ownerPlayer = dynamic_cast<Alex_8*>(cityCard)->GetCityOwner();
			originalPlayer = dynamic_cast<Alex_8*>(cityCard)->GetOriginalOwner();
			cityPrice = dynamic_cast<Alex_8*>(cityCard)->GetCityPrice();
			break;
		case 9:
			ownerPlayer = dynamic_cast<Aswan_9*>(cityCard)->GetCityOwner();
			originalPlayer = dynamic_cast<Aswan_9*>(cityCard)->GetOriginalOwner();
			cityPrice = dynamic_cast<Aswan_9*>(cityCard)->GetCityPrice();
			break;
		case 10:
			ownerPlayer = dynamic_cast<Luxor_10*>(cityCard)->GetCityOwner();
			originalPlayer = dynamic_cast<Luxor_10*>(cityCard)->GetOriginalOwner();
			cityPrice = dynamic_cast<Luxor_10*>(cityCard)->GetCityPrice();
			break;
		case 11:
			ownerPlayer = dynamic_cast<Hurghada_11*>(cityCard)->GetCityOwner();
			originalPlayer = dynamic_cast<Hurghada_11*>(cityCard)->GetOriginalOwner();
			cityPrice = dynamic_cast<Hurghada_11*>(cityCard)->GetCityPrice();
			break;
		}

		if(ownerPlayer && !originalPlayer && ownerPlayer->getPlayerNum() == pPlayer->getPlayerNum()){
			cityPrices.push_back(cityPrice);
			cityNumbers.push_back(i);
		}

		else if(originalPlayer->getPlayerNum() == pPlayer->getPlayerNum())
			mortgagedCityNumbers.push_back(i);
	}

	if(!cityPrices.size())
		return;

	int maxPricedCityNumber = cityNumbers.at(std::max_element(cityPrices.begin(), cityPrices.end()) - cityPrices.begin());

	for(auto j = mortgagedCityNumbers.begin(); j != mortgagedCityNumbers.end(); ++j){
		if(*j == maxPricedCityNumber){
			pGrid->SetOriginalOwner(NULL, *j);
			pGrid->RemoveMortagage(*j);
			return;
		}
		
	}

	pGrid->SetCityOwner(NULL, maxPricedCityNumber);
}

void LoseCityCard_13::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}