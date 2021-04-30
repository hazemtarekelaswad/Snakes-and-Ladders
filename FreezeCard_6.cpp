#include"FreezeCard_6.h"

FreezeCard_6::FreezeCard_6(const CellPosition &cellPosition) 
	:Card(cellPosition), count(0){

		cardNumber = 6;	
}

FreezeCard_6::FreezeCard_6(){
	cardNumber = 6;
}

FreezeCard_6::~FreezeCard_6(){}

void FreezeCard_6::ReadCardParameters(Grid *pGrid){

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	outPtr->PrintMessage("New FreezeCard (6) | Enter (0) to freeze players in odd cells and (1) to freeze players in even cells...");
	isEven = static_cast<bool>(inPtr->GetInteger(outPtr));
	
	do{
		outPtr->PrintMessage("Enter the number of turns to freeze other players [1 turn or more]...");
		nrOfTurnsToFreeze = inPtr->GetInteger(outPtr);
	} while(nrOfTurnsToFreeze < 1);

	outPtr->ClearStatusBar();
}

void FreezeCard_6::Apply(Grid *pGrid, Player *pPlayer){

	Card::Apply(pGrid, pPlayer);

	for(int i = 0; i < MaxPlayerCount - 1; ++i){

		pGrid->AdvanceCurrentPlayer();
		int cellPositionOfCurrentPlayer = pGrid->GetCurrentPlayer()->GetCell()->GetCellPosition().GetCellNum();
			
		if(isEven && !(cellPositionOfCurrentPlayer % 2)){
			pGrid->Apply_Prevent(pGrid->GetCurrentPlayer()->getPlayerNum());
			pGrid->ApplyFreeze(pGrid->GetCurrentPlayer()->getPlayerNum(), nrOfTurnsToFreeze);
		}
			
		else if(!isEven && cellPositionOfCurrentPlayer % 2){
			pGrid->Apply_Prevent(pGrid->GetCurrentPlayer()->getPlayerNum());
			pGrid->ApplyFreeze(pGrid->GetCurrentPlayer()->getPlayerNum(), nrOfTurnsToFreeze);
		}
	}
		pGrid->AdvanceCurrentPlayer();
}

int FreezeCard_6::GetNrOfTurnsToFreeze() const{
	return nrOfTurnsToFreeze;
}

void FreezeCard_6::SetNrOfTurnsToFreeze(int nrOfTurns){
	nrOfTurnsToFreeze = nrOfTurns;
} 

void FreezeCard_6::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << isEven << ' ' << nrOfTurnsToFreeze << std::endl;
	}
}

void FreezeCard_6::Load(ifstream& InFile){
	Card::Load(InFile);

	bool even;
	int nrOfTurns;
	InFile >> even >> nrOfTurns;

	isEven = even;
	nrOfTurnsToFreeze = nrOfTurns;
}