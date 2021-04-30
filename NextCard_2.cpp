#include "NextCard_2.h"
#include "Ladder.h"
#include "Snake.h"
#include "CoinSet.h"
#include "Card.h"

#include "Grid.h"



NextCard_2::NextCard_2(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (1 here)
}

NextCard_2::NextCard_2(){
	cardNumber = 2;
}

NextCard_2::~NextCard_2(void)
{
}

void NextCard_2::ReadCardParameters(Grid * pGrid)
{

	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	string msg = "Choose the next Game Object, '1' for ladder, '2' for snake, '3' for coin set, '4' for card ";
	out -> PrintMessage (msg) ;

	GO_Type= in -> GetInteger(out);

	while (GO_Type < 1 || GO_Type > 4)
	{
		out -> PrintMessage ("You entered invalid Game object, '1' for ladder, '2' for snake, '3' for coin set, '4' for card");
		GO_Type= in -> GetInteger(out);
	}
	out->ClearStatusBar();
}

void NextCard_2::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply (pGrid, pPlayer);

	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	if (GO_Type == 1)
	{
		Ladder * L = pGrid -> GetNextLadder (pPlayer->GetCell()->GetCellPosition().GetCellNum());
		if(L)
			pGrid -> UpdatePlayerCell (pPlayer, L-> GetPosition());
		

		if (L == NULL)
		{
			out ->PrintMessage("There are no Next ladders.Click to search previous...");
			int x,y;
			in->GetPointClicked(x,y);
			out ->ClearStatusBar();

			L = pGrid -> GetPrevLadder (pPlayer->GetCell()->GetCellPosition().GetCellNum());

			if(L)
				pGrid -> UpdatePlayerCell (pPlayer,  L-> GetPosition());
		}

		if (L == NULL)
		{
			out -> PrintMessage ("There is no Ladder in the grid");
		}

	}

	if (GO_Type == 2)
	{
		Snake * S = pGrid -> GetNextSnake (pPlayer->GetCell()->GetCellPosition().GetCellNum()); 
		if(S)
			pGrid -> UpdatePlayerCell (pPlayer, S-> GetPosition());

		if (S == NULL)
		{
			out ->PrintMessage("There are no Next Snakes.Click to Search previous...");
			int x,y;
			in->GetPointClicked(x,y);
			out ->ClearStatusBar();

			S = pGrid -> GetPrevSnake (pPlayer->GetCell()->GetCellPosition().GetCellNum());
			if(S)
				pGrid -> UpdatePlayerCell (pPlayer, S-> GetPosition());
		}

		if (S == NULL)
		{
			out -> PrintMessage ("There is no Snake in the grid");
		}

	}

	if (GO_Type == 3)
	{
		CoinSet * C = pGrid -> GetNextCoinSet (pPlayer->GetCell()->GetCellPosition().GetCellNum());
		if(C)
			pGrid -> UpdatePlayerCell (pPlayer, C -> GetPosition());

		if (C == NULL)
		{
			out ->PrintMessage("There are no Next Coinsets.Click to Search Previous...");
			int x,y;
			in->GetPointClicked(x,y);
			out ->ClearStatusBar();

			C = pGrid -> GetPrevCoinSet (pPlayer->GetCell()->GetCellPosition().GetCellNum());
			if(C)
				pGrid -> UpdatePlayerCell (pPlayer,  C -> GetPosition());
		}

		if (C == NULL)
		{
			out -> PrintMessage ("There is no CoinSet in the grid");
		}

	}

	if (GO_Type == 4)
	{
		Card * C = pGrid -> GetNextCard (pPlayer->GetCell()->GetCellPosition().GetCellNum());
		if(C)
			pGrid -> UpdatePlayerCell (pPlayer, C-> GetPosition());

		if (C == NULL)
		{
			out ->PrintMessage("There are no Next Cards.Click to Search Previous...");
			int x,y;
			in->GetPointClicked(x,y);
			out ->ClearStatusBar();

			C = pGrid -> GetPrevCard (pPlayer->GetCell()->GetCellPosition().GetCellNum());
			if(C)
				pGrid -> UpdatePlayerCell (pPlayer, C-> GetPosition());
		}

		if (C == NULL)
		{
			out -> PrintMessage ("There is no Card in the grid");
		}

	}

	out->ClearStatusBar();

}

void NextCard_2::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << GO_Type << std::endl;
	}
}

void NextCard_2::Load(ifstream& InFile){
	Card::Load(InFile);
	int type;
	InFile >> type;
	GO_Type = type;
}