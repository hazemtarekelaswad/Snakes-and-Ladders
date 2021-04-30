#pragma once

#include"Card.h"

class LoseCityCard_13 : public Card{
private:
public:

	LoseCityCard_13(const CellPosition & pos); 

	LoseCityCard_13();

	virtual void Apply(Grid* pGrid, Player* pPlayer); 

	virtual ~LoseCityCard_13(); 

	virtual void Save(ofstream& outFile, Type gameObj);
};