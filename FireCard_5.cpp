#include "FireCard_5.h"

FireCard_5::FireCard_5(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number 
}

FireCard_5::FireCard_5(){
	cardNumber = 5;
}

FireCard_5::~FireCard_5()
{
}

void FireCard_5::ReadActionParameters()
{
	// no parameters to read from user
}

void FireCard_5 :: Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply (pGrid, pPlayer);

	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	for (int i = 0; i < 3; i++)
	{
		pGrid -> AdvanceCurrentPlayer();
		if (pGrid -> GetCurrentPlayer() -> GetCell () -> GetCellPosition() . HCell() == GetPosition() . HCell() || pGrid -> GetCurrentPlayer() -> GetCell () -> GetCellPosition() . VCell() == GetPosition() . VCell() )
		{
			pGrid -> UpdatePlayerCell (pGrid -> GetCurrentPlayer() , CellPosition(NumVerticalCells - 1, 0));

			pGrid -> GetCurrentPlayer() -> SetWallet (pGrid -> GetCurrentPlayer() -> GetWallet () / 2);

		}
	} 

	pGrid -> AdvanceCurrentPlayer();

}

void FireCard_5::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}

