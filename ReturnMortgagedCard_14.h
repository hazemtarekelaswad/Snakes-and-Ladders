#pragma once

#include "Card.h"
#include "CellPosition.h"

class ReturnMortgagedCard_14 : public Card
{


public:
	ReturnMortgagedCard_14(const CellPosition & pos);

	ReturnMortgagedCard_14();


	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual~ReturnMortgagedCard_14();

	virtual void Save(ofstream& outFile, Type gameObj);
};

