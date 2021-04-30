#include "BackwardCard_3.h"

BackwardCard_3 :: BackwardCard_3 (const CellPosition & pos) : Card(pos)
{
	cardNumber = 3;
}

BackwardCard_3::BackwardCard_3(){
	cardNumber = 3;
}

BackwardCard_3::~BackwardCard_3()
{
}

void BackwardCard_3::ReadActionParameters()
{
	// no parameters to read from user
}

void BackwardCard_3 :: Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply (pGrid, pPlayer);

	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	out -> PrintMessage ("New BackwardCard (3) | Click to apply ..");

	int x,y;
	in -> GetPointClicked(x,y);
	out -> ClearStatusBar();

	for (int i = 0; i < 3; i++)
	{
		pGrid -> AdvanceCurrentPlayer();
		pGrid->GetCurrentPlayer() -> Move (pGrid , - pPlayer -> GetjustRolledDiceNum());
	}
	pGrid->AdvanceCurrentPlayer();
}

void BackwardCard_3::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}



