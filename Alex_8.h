#pragma once

#include"Card.h"

class Alex_8 : public Card{
private:
	int m_cityPrice;
	int m_rent;
	Player *m_cityOwner;
	Player *m_originalOwner;
	bool isFirst;

public:
	Alex_8(const CellPosition &position);
	Alex_8();
	virtual void ReadCardParameters(Grid *pGrid) override;
	virtual void Apply(Grid *pGrid, Player *pPlayer) override;

	Player *GetCityOwner() const;
	void setCityOwner(Player *pPlayer);

	Player *GetOriginalOwner() const;
	void SetOriginalOwner(Player *pPlayer);

	int GetCityPrice() const;
	int GetCityRent() const;

	virtual ~Alex_8();

	virtual void Save(ofstream& outFile, Type gameObj);
	void Load(ifstream& InFile);
	
};