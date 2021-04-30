#pragma once

#include "Card.h"

class FireCard_5 : public Card
{

public:
	FireCard_5(const CellPosition & pos);

	FireCard_5();

	virtual ~FireCard_5();

	void ReadActionParameters();

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& outFile, Type gameObj);

};
