#include "Snake.h"

Snake::Snake(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	///TODO: Do the needed validation

	if (startCellPos.HCell() == endCellPos.HCell() && endCellPos.GetCellNum() < startCellPos.GetCellNum())
	{
	this->endCellPos = endCellPos;
	}

	else if (startCellPos.HCell() != endCellPos.HCell() && endCellPos.GetCellNum() < startCellPos.GetCellNum())
	{
		this->endCellPos = endCellPos;
		this->endCellPos.SetHCell(startCellPos.HCell()); 
	}

	else if (startCellPos.HCell() == endCellPos.HCell() && endCellPos.GetCellNum() > startCellPos.GetCellNum())
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

Snake::Snake(){}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer) 
{
	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	out -> PrintMessage ("You have reached a snake | Click to continue ...");

	int x, y;
	in -> GetPointClicked (x,y);
	out -> ClearStatusBar();

	pGrid -> UpdatePlayerCell (pPlayer, endCellPos);
}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == SNAKES)
	{
		outFile << position.GetCellNum() << ' ' << endCellPos.GetCellNum() << std::endl;
	}
}

void Snake::Load(ifstream& InFile)
{
	int startPosNumber, endPosNumber;
	InFile >> startPosNumber >> endPosNumber;

	position = CellPosition(startPosNumber);
	endCellPos = CellPosition(endPosNumber);
}

Snake::~Snake()
{
}
