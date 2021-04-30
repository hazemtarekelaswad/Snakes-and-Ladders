#pragma once

#include "UI_Info.h"
#include "DEFS.h"

#include "Input.h"
#include "Output.h"
#include "CellPosition.h"

// forward declarations (the includes are in the cpp)
class Cell;
class GameObject;
class Ladder;
class Snake;
class CoinSet;
class Card;
class Player;

enum Type{LADDERS, SNAKES, COINSETS, CARDS};

class Grid
{
	Output * pOut;   // A pointer to the Output object
	Input * pIn;     // A pointer to the Input object

	Cell * CellList[NumVerticalCells][NumHorizontalCells];  // An array of "Pointers" to All Cells of the Grid Cells
															// We make it array of pointers not objects because
															// there are NO default constructor for class Cell

	Player* PlayerList[MaxPlayerCount]; // An array of "Pointers" to the Players of the Game (MaxPlayerCount Players)
	int currPlayerNumber;   // The player number that has the turn to play 
							// currPlayerNumber is: from 0 to MaxPlayerCount - 1

	GameObject * Clipboard;	// This is used in copy/cut/paste card (should be set in copy/cut and got in paste)

	bool endGame;			// A boolean indicating if the Game is ended or not (a player reaches the end cell of the grid or not)
	
	Card * MortagageList[5];	//A container for mortgaged cities with max 5 cities
	int Count_Of_Mortagage;		//Counter to track the added mortgaged cities in the container

public:

	Grid(Input * pIn, Output * pOut);	  // Gives the Grid a Pointer to the Output Object and the Input Object
										  // and makes any needed initializations

	// ========= Adding or Removing GameObjects to Cells =========

	bool AddObjectToCell(GameObject * pNewObject);		 // Adds a GameObject to the Cell of its "position" data member
	                                                     // only if the Cell does NOT already contain an object, 
	                                                     // otherwise return false and don't add

	void RemoveObjectFromCell(const CellPosition & pos); // Removes the GameObject of the Cell of the passed "position"

	void UpdatePlayerCell(Player * player, const CellPosition & newPosition); // Update the player's pCell with the CellList's Cell pointer of the "newPosition",
	                                                                          // Clears the player's circle from the previous cell
	    																	  // and  Draws it in the new cell
	// ========= Setters and Getters Functions =========

	Input * GetInput() const;	// Gets a Pointer to the Input
	Output * GetOutput() const; // Gets a Pointer to the Output 

	void SetClipboard(GameObject * card);  // A setter to be used in copy/cut (in order NOT to break class responsibilities)
	GameObject * GetClipboard() const;	 // A getter to be used in paste (in order NOT to break class responsibilities)

	void SetEndGame(bool endGame);	 // A setter for endGame data member
	bool GetEndGame() const;		 // A getter for endGame data member

	Player * GetCurrentPlayer() const;	// Gets a Pointer to the Current Player

	void AdvanceCurrentPlayer();     // Increments the currPlayerNum and if reaches MaxPlayerCount reset to 0 (using %)


	///TODO: add any needed setter/getter "EXCEPT" ANY setters or getters of "CellList" or "PlayerList" (Forbidden for class Responsibilities)
	
	Card* GetFirstCard(int cityCardNumber) const;	// Gets the first card, with card number as a parameter, in the grid 
	void SetCityOwner(Player*, int);				//Sets the city owner for a specified city to all this city cards in the grid
	void SetOriginalOwner(Player*, int);			//Sets the original owner, used for mortgaged cities

		                                    
	
	Ladder * GetNextLadder(const CellPosition & position);  // Gets a Pointer to the first Ladder after the passed "position"
	Snake* GetNextSnake(const CellPosition & position);		// Gets a Pointer to the first Snake after the passed "position"
	CoinSet* GetNextCoinSet(const CellPosition & position);	// Gets a Pointer to the first CoinSet after the passed "position"
	Card* GetNextCard(const CellPosition & position);		// Gets a Pointer to the first Card after the passed "position"

	Ladder * GetPrevLadder(const CellPosition & position);  // Gets a Pointer to the first Ladder just before the passed "position"
	Snake* GetPrevSnake(const CellPosition & position);		// Gets a Pointer to the first Snake just before the passed "position"
	CoinSet* GetPrevCoinSet(const CellPosition & position);	// Gets a Pointer to the first CoinSet just before the passed "position"
	Card* GetPrevCard(const CellPosition & position);		// Gets a Pointer to the first Card just before the passed "position"

	Card* HasCard(const CellPosition & position);			// Returns a card, if any, in the passed position
	GameObject* GetGameObject(const CellPosition & position);	//Gets the game object, if any, in the passed positon
	
	//================ Functions for cards ================
	void Apply_Prevent(int index);			//Applys preventCard effect on player of the passed index
	void ApplyFreeze(int index, int nr);	//Applys freezeCard effect on player of the passed index, and the number of turns to freeze
	void ApplyBenefit(int index, int nr, Player* cityOwner, int i);	//Applys benefitAllCard effect on player of the passed index, and the number of turns to benefit

	////================ Functions for cities mortgage //================
	void AddMortagage(Card *CArdNum);
	Card* SearchMortagage(int CityNum);
	void RemoveMortagage(int citynum);

	// ========= User Interface Functions =========

	///TODO: add an implementation for the TODO written inside the function
	void UpdateInterface() const;		// It Updates the Grid according to the last state of the game
	                                    // In Design mode, it draws all cells/cards THEN all ladders/snakes THEN all players
	                                    // In Play mode, it only draws the player's info on the right side of the toolbar
	                                    // Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
	                                    //       and the cards/snakes/ladders positions do NOT change already in Play Mode

	void PrintErrorMessage(string msg); // Prints an error message on statusbar, Waits for mouse click then clears statusbar
									    // We added this function once here because it is used many times by other classes
	
	int GetNumberOfGameObject(Type type) const;

	//================Additional Functions=========================

	void SaveAll(ofstream& ,Type type);

	//Card* GetCardFromCellPosition(const CellPosition&);
	//CoinSet* GetCoinSetFromCellPosition(const CellPosition&);
	GameObject* GetGameObjFromCellPosition(const CellPosition&);

	void ClearGridArea();

	~Grid(); // A destructor for any needed deallcations
};

