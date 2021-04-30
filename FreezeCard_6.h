#pragma once

#include"Card.h"

class FreezeCard_6 : public Card{
private:
	bool isEven;
	int nrOfTurnsToFreeze;
	int count;
	//Player *freezedPlayer;
public:
	FreezeCard_6(const CellPosition &cellPosition);

	FreezeCard_6();

	virtual void ReadCardParameters(Grid *pGrid) override;
	virtual void Apply(Grid *pGrid, Player *pPlayer) override;

	int GetNrOfTurnsToFreeze() const;
	void SetNrOfTurnsToFreeze(int);

	virtual ~FreezeCard_6();

	virtual void Save(ofstream& outFile, Type gameObj);
	virtual void Load(ifstream& InFile);

};