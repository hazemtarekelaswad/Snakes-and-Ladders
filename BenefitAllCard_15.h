#pragma once

#include"Card.h"

class BenefitAllCard_15 : public Card{
private:
	int nrOfTurnsToBenefit;

public:
	BenefitAllCard_15(const CellPosition &cellPosition);

	BenefitAllCard_15();

	virtual void ReadCardParameters(Grid *pGrid) override;
	virtual void Apply(Grid *pGrid, Player *pPlayer) override;

	int GetNrOfTurnsToBenefit() const;
	void SetNrOfTurnsToBenefit(int);

	virtual ~BenefitAllCard_15();

	virtual void Save(ofstream& outFile, Type gameObj);

	virtual void Load(ifstream& InFile);
};