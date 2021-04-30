#pragma once

#include "Card.h"

class TakeCityCard_12 :	public Card
{

	
public:
	TakeCityCard_12(const CellPosition & pos); 

	TakeCityCard_12();

	virtual void Apply(Grid* pGrid, Player* pPlayer); 

	virtual ~TakeCityCard_12(); 

	virtual void Save(ofstream& outFile, Type gameObj);

	//virtual void Load(ifstream& InFile)
};

