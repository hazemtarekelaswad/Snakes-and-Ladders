#pragma once

#include "Action.h"

class AddCoinSet : public Action
{
	// [Action Parameters]         
	CellPosition CoinPosition; // 2- cell position of the card
	bool isValid;
	int amount;


	// Note: These parameters should be read in ReadActionParameters()

public:
	AddCoinSet(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
	// and Reads the Parameters of This Card Number (if any)
	// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~AddCoinSet(); // A Virtual Destructor
};