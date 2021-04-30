#include "Cell.h"
#include "Snake.h"
#include "Grid.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "CoinSet.h"

Cell::Cell(const CellPosition & pos) : position(pos)
{
	// initializes the data members (position & pGameObject)
	pGameObject = NULL;
}

Cell::Cell(int v, int h) : position(v, h)
{
	// initializes the data members (position & pGameObject)
	pGameObject = NULL;
}


// ======= Setters and Getters Functions ======= 


CellPosition Cell::GetCellPosition() const
{
	return position;
}

bool Cell::SetGameObject(GameObject * pGObj)
{
	if (pGameObject != NULL && pGObj != NULL) // already contains one
		return false; // do NOT add it and return false

	pGameObject = pGObj;
	return true;
}

GameObject * Cell::GetGameObject() const
{
	return pGameObject;
}

Ladder * Cell::HasLadder() const
{
	return dynamic_cast<Ladder *>(pGameObject);
}

Snake * Cell::HasSnake() const
{

	///TODO: Implement the following function like HasLadder() function
	return dynamic_cast<Snake *>(pGameObject);

}

CoinSet * Cell::HasCoinSet() const
{
	///TODO: Implement the following function like HasLadder() function

	return dynamic_cast<CoinSet *>(pGameObject);

}

Card * Cell::HasCard() const
{

	///TODO: Implement the following function like HasLadder() function

	return dynamic_cast<Card *>(pGameObject);

}



// ======= Drawing Functions ======= 

void Cell::DrawCellOrCard(Output* pOut) const
{
	// Checks if there is a Card on the cell
	if (HasCard()) // means if not NULL
		pGameObject->Draw(pOut); // draw the card then
	else
		pOut->DrawCell(position, -1); // draw empty cell (no card -1)
	
	///TODO: Think where to add the code that draws the CoinSet game objects
}

// separate from the above function because ladders/snakes should be drawn AFTER All Cells are drawn
void Cell::DrawLadderOrSnake(Output* pOut) const
{
	if (HasLadder() || HasSnake())
		pGameObject->Draw(pOut); // draw it either ladder or snake

	///TODO: Think where to add the code that draws the CoinSet game objects
}

void Cell::DrawCoinSet(Output* pOut) const
{
	if (HasCoinSet())
		pGameObject->Draw(pOut); 

}
