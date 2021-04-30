#pragma once

#include"Card.h"

class Cairo_7 : public Card{
private:
	int m_cityPrice;
	int m_rent;
	Player *m_cityOwner;
	Player *m_originalOwner;
	bool isFirst;

public:
	Cairo_7(const CellPosition &position);
	Cairo_7();

	virtual void ReadCardParameters(Grid *pGrid) override;

	virtual void Apply(Grid *pGrid, Player *pPlayer) override;

	Player *GetOriginalOwner() const;
	void SetOriginalOwner(Player *pPlayer);

	Player *GetCityOwner() const;
	void setCityOwner(Player *pPlayer);

	int GetCityPrice() const;
	int GetCityRent() const;

	virtual ~Cairo_7();

	virtual void Save(ofstream& outFile, Type gameObj);
	virtual void Load(ifstream& InFile);

	
};