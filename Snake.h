#pragma once

#include "GameObject.h"

class Snake : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the Snake's "Start Cell Position"

	CellPosition endCellPos; // here is the Snake's End Cell Position

public:

	Snake(const CellPosition & startCellPos, const CellPosition & endCellPos); // A constructor for initialization

	Snake(); //Default Constructor

	virtual void Draw(Output* pOut) const; // Draws a Snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the Snake by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream&); //Reads the start cell and the end cell of Snake from a file

	virtual ~Snake(); // Virtual destructor
};
