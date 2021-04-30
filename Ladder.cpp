#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{

	///TODO: Do the needed validation

	if (startCellPos.HCell() == endCellPos.HCell() && endCellPos.GetCellNum() > startCellPos.GetCellNum())
	{
	this->endCellPos = endCellPos;
	}

	else if (startCellPos.HCell() != endCellPos.HCell() && endCellPos.GetCellNum() > startCellPos.GetCellNum())
	{
		this->endCellPos = endCellPos;
		this->endCellPos.SetHCell(startCellPos.HCell()); 
	}

	else if (startCellPos.HCell() == endCellPos.HCell() && endCellPos.GetCellNum() < startCellPos.GetCellNum())
	{
		position = endCellPos;
		this->endCellPos = startCellPos;
	}

	else
	{
		position = endCellPos;
		this->endCellPos = startCellPos;
		this->endCellPos.SetHCell(startCellPos.HCell()); 
	}
}

Ladder::Ladder(){}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	out -> PrintMessage ("You have reached a ladder | Click to continue ...");

	int x, y;
	in->GetPointClicked(x,y);
	out->ClearStatusBar();

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	pGrid->UpdatePlayerCell (pPlayer, endCellPos);	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == LADDERS)
	{
		outFile << position.GetCellNum() << ' ' << endCellPos.GetCellNum() << std::endl;
	}
}

void Ladder::Load(ifstream& InFile)
{
	int startPosNumber, endPosNumber;
	InFile >> startPosNumber >> endPosNumber;

	position = CellPosition(startPosNumber);
	endCellPos = CellPosition(endPosNumber);
}

Ladder::~Ladder()
{
}
