#pragma once

#include"Card.h"

class Luxor_10 : public Card{
private:
	int m_cityPrice;
	int m_rent;
	Player *m_cityOwner;
	Player *m_originalOwner;
	bool isFirst;

public:
	Luxor_10(const CellPosition &position);
	Luxor_10();
	virtual void ReadCardParameters(Grid *pGrid) override;

	//Don't know if it will work
	virtual void Apply(Grid *pGrid, Player *pPlayer) override;

	Player *GetCityOwner() const;
	void setCityOwner(Player *pPlayer);

	Player *GetOriginalOwner() const;
	void SetOriginalOwner(Player *pPlayer);
	
	int GetCityPrice() const;
	int GetCityRent() const;

	virtual void Save(ofstream& outFile, Type gameObj);
	virtual void Load(ifstream&);

	virtual ~Luxor_10();
	
};