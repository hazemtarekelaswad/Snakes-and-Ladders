#include "Grid.h"
#include "Cell.h"
#include "Card.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "CoinSet.h"
#include "Card.h"
#include "Player.h"
#include "Cairo_7.h"
#include "Alex_8.h"
#include "Aswan_9.h"
#include "Luxor_10.h"
#include "Hurghada_11.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;

	Count_Of_Mortagage = 0;

	for(int i = 0; i < 5; ++i)
		MortagageList[i] = NULL;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if(pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		//delete CellList[pos.VCell()][pos.HCell()]->GetGameObject();

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}



// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(GameObject * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

GameObject * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}
//TODO//================================//

void Grid::SetCityOwner(Player* pPlayer, int cardNumber){

	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			Card* pCard = CellList[i][j]->HasCard();

			if(pCard && pCard->GetCardNumber() == cardNumber){
				switch(cardNumber){
				case 7:
					dynamic_cast<Cairo_7*>(pCard)->setCityOwner(pPlayer);
					break;
				case 8:
					dynamic_cast<Alex_8*>(pCard)->setCityOwner(pPlayer);
					break;
				case 9:
					dynamic_cast<Aswan_9*>(pCard)->setCityOwner(pPlayer);
					break;
				case 10:
					dynamic_cast<Luxor_10*>(pCard)->setCityOwner(pPlayer);
					break;
				case 11:
					dynamic_cast<Hurghada_11*>(pCard)->setCityOwner(pPlayer);
					break;
				default:
					return;
				}
			}
		}
	}
}

void Grid::SetOriginalOwner(Player* pPlayer, int cardNumber){

	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			Card* pCard = CellList[i][j]->HasCard();

			if(pCard && pCard->GetCardNumber() == cardNumber){
				switch(cardNumber){
				case 7:
					dynamic_cast<Cairo_7*>(pCard)->SetOriginalOwner(pPlayer);
					break;
				case 8:
					dynamic_cast<Alex_8*>(pCard)->SetOriginalOwner(pPlayer);
					break;
				case 9:
					dynamic_cast<Aswan_9*>(pCard)->SetOriginalOwner(pPlayer);
					break;
				case 10:
					dynamic_cast<Luxor_10*>(pCard)->SetOriginalOwner(pPlayer);
					break;
				case 11:
					dynamic_cast<Hurghada_11*>(pCard)->SetOriginalOwner(pPlayer);
					break;
				default:
					return;
				}
			}
		}
	}
}
// ========= Other Getters =========

Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if(CellList[i][j]->HasLadder())
				return CellList[i][j]->HasLadder();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Snake * Grid::GetNextSnake(const CellPosition & position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if(CellList[i][j]->HasSnake())
				return CellList[i][j]->HasSnake();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

CoinSet * Grid::GetNextCoinSet(const CellPosition & position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if(CellList[i][j]->HasCoinSet())
				return CellList[i][j]->HasCoinSet();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Card * Grid::GetNextCard(const CellPosition & position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if(CellList[i][j]->HasCard())
				return CellList[i][j]->HasCard();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Ladder* Grid::GetPrevLadder(const CellPosition & position){
	int startH = position.HCell(); 
	for (int i = position.VCell(); i < NumVerticalCells; i++) 
	{
		for (int j = startH; j >= 0; j--) 
		{
			if(CellList[i][j]->HasLadder())
				return CellList[i][j]->HasLadder();

		}
		startH = NumHorizontalCells - 1; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Snake* Grid::GetPrevSnake(const CellPosition & position){
	int startH = position.HCell(); 
	for (int i = position.VCell(); i < NumVerticalCells; i++) 
	{
		for (int j = startH; j >= 0; j--) 
		{
			if(CellList[i][j]->HasSnake())
				return CellList[i][j]->HasSnake();

		}
		startH = NumHorizontalCells - 1; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

CoinSet* Grid::GetPrevCoinSet(const CellPosition & position){
	int startH = position.HCell(); 
	for (int i = position.VCell(); i < NumVerticalCells; i++) 
	{
		for (int j = startH; j >= 0; j--) 
		{
			if(CellList[i][j]->HasCoinSet())
				return CellList[i][j]->HasCoinSet();

		}
		startH = NumHorizontalCells - 1; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Card* Grid::GetPrevCard(const CellPosition & position){
	int startH = position.HCell(); 
	for (int i = position.VCell(); i < NumVerticalCells; i++) 
	{
		for (int j = startH; j >= 0; j--) 
		{
			if(CellList[i][j]->HasCard())
				return CellList[i][j]->HasCard();

		}
		startH = NumHorizontalCells - 1; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Card* Grid::HasCard(const CellPosition &position){
	return CellList[position.VCell()][position.HCell()]->HasCard();
}

void Grid::AddMortagage(Card *CArdNum)
{
	MortagageList[Count_Of_Mortagage++] = CArdNum;
}

Card *Grid::SearchMortagage(int CityNum)
{
	for(int i = 0; i < Count_Of_Mortagage; i++)
	{
		if (MortagageList[i]->GetCardNumber() == CityNum)
		{
			return MortagageList[i];
		}
	}
	return NULL;
}

void Grid::RemoveMortagage(int citynum)
{
	for(int i = 0; i < Count_Of_Mortagage; i++)
	{
		if (MortagageList[i]->GetCardNumber() == citynum)
		{
			MortagageList[i] = MortagageList[Count_Of_Mortagage - 1];
			MortagageList[Count_Of_Mortagage - 1] = NULL;
			Count_Of_Mortagage--;
		}
	}


}

Card* Grid::GetFirstCard(int cityCardNumber) const{

	for (int i = NumVerticalCells - 1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			if(CellList[i][j]->HasCard() && CellList[i][j]->HasCard()->GetCardNumber() == cityCardNumber)
				return CellList[i][j]->HasCard();
		}
	}
	return NULL;
}

GameObject* Grid::GetGameObject(const CellPosition & position)
{
	return CellList[position.VCell()][position.HCell()] ->GetGameObject();
}

void Grid::Apply_Prevent(int Index_Player)
{
	PlayerList[Index_Player] ->setPreventState(true);
}

void Grid::ApplyFreeze(int index, int nrOfTurnToFreeze){
	PlayerList[index]->SetFreeze(true);
	PlayerList[index]->SetNrOfTurnsToFreeze(nrOfTurnToFreeze);
}
// ========= User Interface Functions =========

void Grid::ApplyBenefit(int index, int nr, Player* cityOwner, int i){
	PlayerList[index]->SetBenefit(true);
	PlayerList[index]->SetNrOfTurnsToBenefit(nr);
	PlayerList[index]->SetCityOwner(cityOwner);
	PlayerList[index]->SetCityNumber(i);
}

void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		///TODO: Add the code that draws the CoinSet game objects

		for (int i = NumVerticalCells-1; i >= 0 ; i--) 
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				CellList[i][j]->DrawCoinSet(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}


void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

int Grid::GetNumberOfGameObject(Type type) const{
	int count = 0;

	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			switch(type)
			{
			case LADDERS:
				if(CellList[i][j]->HasLadder())
					++count;
				break;
			case SNAKES:
				if(CellList[i][j]->HasSnake())
					++count;
				break;
			case COINSETS:
				if(CellList[i][j]->HasCoinSet())
					++count;
				break;
			case CARDS:
				if(CellList[i][j]->HasCard())
					++count;
				break;

			}
		}
	}

	return count;
}

//================Additional Functions=========================

void Grid::SaveAll(ofstream &outFile, Type gameObj){
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			if(CellList[i][j]->GetGameObject())
				CellList[i][j]->GetGameObject()->Save(outFile, gameObj);
		}
	}

}

void Grid::ClearGridArea(){
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			if(CellList[i][j]->GetGameObject())
				RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
		}
	}

}

GameObject* Grid::GetGameObjFromCellPosition(const CellPosition& pos){
	if(CellList[pos.VCell()][pos.HCell()]->HasCard())
		return  CellList[pos.VCell()][pos.HCell()]->HasCard();
	if(CellList[pos.VCell()][pos.HCell()]->HasCoinSet())
		return CellList[pos.VCell()][pos.HCell()]->HasCoinSet();
	if(CellList[pos.VCell()][pos.HCell()]->HasLadder())
		return CellList[pos.VCell()][pos.HCell()]->HasLadder();
	if(CellList[pos.VCell()][pos.HCell()]->HasSnake())
		return CellList[pos.VCell()][pos.HCell()]->HasSnake();
	return NULL;
}

//============================================================


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}