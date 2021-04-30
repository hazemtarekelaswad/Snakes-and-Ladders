#pragma once

#include "Card.h"

class PreventCard_4  : public Card
{
public:

	PreventCard_4(const CellPosition & pos); 

	PreventCard_4();
	
	virtual ~PreventCard_4();

	void ReadActionParameters();

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	Player* GetPlayerToBePrevented() const;

	virtual void Save(ofstream& outFile, Type gameObj);

	//virtual void Load(ifstream& InFile);
};