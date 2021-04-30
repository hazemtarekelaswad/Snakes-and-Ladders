#pragma once

#include "GameObject.h"

class CoinSet :	public GameObject // inherited from GameObject
{
	int Amount;

public:

	CoinSet(const int Amount, const CellPosition &CellPos); // A constructor for initialization

	CoinSet(); // Default Constructor

	virtual void Draw(Output* pOut) const; // Draws a coinSet in its cell position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the coinSet on the player info

	//CellPosition GetCellPosition() const; // A getter for the coinSet Cell Position

	void SetAmount(int amount); // A setter for the amount of coins in the coinSet 

	int GetAmount() const; // A getter for the the amount of coins in the coinSet

	virtual void Save(ofstream& outFile, Type gameObj); // Saves the data members in a file

	virtual void Load(ifstream& InFile); // Reads the data members from a file

	virtual ~CoinSet(); // Virtual destructor
};
