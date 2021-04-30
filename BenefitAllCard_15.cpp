#include"BenefitAllCard_15.h"
#include "Cairo_7.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"

BenefitAllCard_15::BenefitAllCard_15(const CellPosition &cellPosition) 
	:Card(cellPosition){

		cardNumber = 15;	
}

BenefitAllCard_15::BenefitAllCard_15(){
	cardNumber = 15;
}

BenefitAllCard_15::~BenefitAllCard_15(){}

void BenefitAllCard_15::ReadCardParameters(Grid *pGrid){

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	outPtr->PrintMessage("New BenefitAllCard (15) | Enter the number of turns you want other players to benefit...");
	nrOfTurnsToBenefit = inPtr->GetInteger(outPtr);

	outPtr->ClearStatusBar();
}

void BenefitAllCard_15::Apply(Grid *pGrid, Player *pPlayer){

	Card::Apply(pGrid, pPlayer);
	
	Card *cityCard;
	Player* cityOwner;

	for(int i = 7; i <= 11; ++i){
		cityCard = pGrid->GetFirstCard(i);

		if(!cityCard)
			continue;

		switch(i){
		case 7:
			cityOwner = dynamic_cast<Cairo_7*>(cityCard)->GetCityOwner();
			break;
		case 8:
			cityOwner = dynamic_cast<Alex_8*>(cityCard)->GetCityOwner();
			break;
		case 9:
			cityOwner = dynamic_cast<Aswan_9*>(cityCard)->GetCityOwner();
			break;
		case 10:
			cityOwner = dynamic_cast<Luxor_10*>(cityCard)->GetCityOwner();
			break;
		case 11:
			cityOwner = dynamic_cast<Hurghada_11*>(cityCard)->GetCityOwner();
			break;
		default:
			return;
		}

		if(cityOwner){
			pGrid->ApplyBenefit(pPlayer->getPlayerNum(), nrOfTurnsToBenefit, cityOwner, i);
			pGrid->SetCityOwner(pPlayer, i);
		}
	}

}

int BenefitAllCard_15::GetNrOfTurnsToBenefit() const{
	return nrOfTurnsToBenefit;
}

void BenefitAllCard_15::SetNrOfTurnsToBenefit(int nrOfTurns){
	nrOfTurnsToBenefit = nrOfTurns;
} 

void BenefitAllCard_15::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << nrOfTurnsToBenefit << std::endl;
	}
}

void BenefitAllCard_15::Load(ifstream &InFile){
	Card::Load(InFile);
	int nrOfTurns;
	InFile >> nrOfTurns;
	nrOfTurnsToBenefit = nrOfTurns;
}
