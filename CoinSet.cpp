#include "CoinSet.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"


CoinSet::CoinSet(const int Amount, const CellPosition &CellPos) : GameObject(CellPos)
{
	SetAmount(Amount);
}

CoinSet::CoinSet(){}

void CoinSet::Draw(Output* pOut) const
{
	pOut->DrawCoinSet(position);
}

void CoinSet::Apply(Grid* pGrid, Player* pPlayer) 
{
	Input * in = pGrid->GetInput();
	Output * out = pGrid->GetOutput();
	int x,y;

	out->PrintMessage("You have reached a coin set with amount value of " + to_string(Amount) + " | Click to continue ...");
	in -> GetPointClicked(x,y);
	out -> ClearStatusBar();

	pPlayer -> SetWallet (pPlayer -> GetWallet() + Amount);

	out -> PrintMessage("Your total wallet amount has increased to " + to_string (pPlayer -> GetWallet()) + " Coins | Click to continue ...");
	in -> GetPointClicked(x,y);
	out -> ClearStatusBar();
}

void CoinSet::SetAmount(int amount) 
{
	Amount = (amount >= 0 ? amount : -1);
}

int CoinSet::GetAmount() const
{
	return Amount;
}

void CoinSet::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == COINSETS)
	{
		outFile << position.GetCellNum() << ' ' << Amount << std::endl;
	}
}

void CoinSet::Load(ifstream& InFile)
{
	int cellNumber, coins;
	InFile >> cellNumber >> coins;

	position = CellPosition(cellNumber);
	Amount = coins;
}

CoinSet::~CoinSet()
{
}
