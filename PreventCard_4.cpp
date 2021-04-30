#include "PreventCard_4.h"

#include "Player.h"

PreventCard_4::PreventCard_4(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number
}

PreventCard_4::PreventCard_4(){
	cardNumber = 4;
}

PreventCard_4::~PreventCard_4()
{
}

void PreventCard_4::ReadActionParameters()
{
	//No ReadAction Parameters
}

void PreventCard_4 :: Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply (pGrid, pPlayer);
	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	out -> PrintMessage ("Prevent Card, Choose the prevented player");
	
	CellPosition p = in -> GetCellClicked();

	for (int i = 0; i < MaxPlayerCount - 1; i++)
	{
		pGrid -> AdvanceCurrentPlayer();
		CellPosition c = pGrid -> GetCurrentPlayer() -> GetPlayerCellPosition();

		if (p.HCell() == c.HCell() && p.VCell() == c. VCell())
			pGrid -> Apply_Prevent(pGrid -> GetCurrentPlayer() -> getPlayerNum());
		
	}

	pGrid -> AdvanceCurrentPlayer();

	out->ClearStatusBar();
	

}

void PreventCard_4::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}
