#pragma once

#include "Card.h"

// [ NextCard_2 ] Summary:
// Moves the current player forward to the start of the next game object of a chosen type (ladder, snake, coin set or cards).
// 
class NextCard_2 :	public Card
{
	// NextCard_2 Parameters:
	int GO_Type; // the wallet value to decrease from the player

public:
	NextCard_2(const CellPosition & pos); // A Constructor takes card position

	NextCard_2();

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of NextCar_2 which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of NextCard_2 on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	
	virtual ~NextCard_2(); // A Virtual Destructor

	virtual void Save(ofstream& outFile, Type gameObj);

	virtual void Load(ifstream& InFile);
};

