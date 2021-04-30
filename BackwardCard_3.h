#pragma once

#include "Card.h"

class BackwardCard_3 : public Card
{
public:
	BackwardCard_3(const CellPosition & pos);

	BackwardCard_3();

	virtual ~BackwardCard_3();

	void ReadActionParameters();

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& outFile, Type gameObj);


};

