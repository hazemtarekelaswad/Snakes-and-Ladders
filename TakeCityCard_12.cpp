#include "TakeCityCard_12.h"
#include "Cairo_7.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"

TakeCityCard_12::TakeCityCard_12(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 12; 
}

TakeCityCard_12::TakeCityCard_12(){
	cardNumber = 12;
}

TakeCityCard_12::~TakeCityCard_12(void){}


void TakeCityCard_12::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply (pGrid, pPlayer);

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	outPtr->PrintMessage("Enter the name of the city you want to own for free: ");
	int x, y;
	inPtr->GetPointClicked(x, y);

	string cityName;
	bool isInvalidName;

	do{
		cityName = inPtr->GetSrting(outPtr);

		isInvalidName = cityName != "Cairo" && cityName != "cairo" && cityName != "CAIRO"
		&& cityName != "Alex" && cityName != "alex" && cityName != "ALEX"
		&& cityName != "Aswan" && cityName != "aswan" && cityName != "ASWAN"
		&& cityName != "Luxor" && cityName != "luxor" && cityName != "LUXOR"
		&& cityName != "Hurghada" && cityName != "hurghada" && cityName != "HURGHADA";

	} while(isInvalidName);

	if(cityName == "Cairo" || cityName == "cairo" || cityName == "CAIRO"){
		pGrid->SetCityOwner(pPlayer, 7);
	}

	else if(cityName == "Alex" || cityName == "alex" || cityName == "ALEX"){
		pGrid->SetCityOwner(pPlayer, 8);
	}

	else if(cityName == "Aswan" || cityName == "aswan" || cityName == "ASWAN"){
		pGrid->SetCityOwner(pPlayer, 9);
	}

	else if(cityName == "Luxor" || cityName == "luxor" || cityName == "LUXOR"){
		pGrid->SetCityOwner(pPlayer, 10);
	}

	else{
		pGrid->SetCityOwner(pPlayer, 11);
	}
	
}
void TakeCityCard_12::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}

