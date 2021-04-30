#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode

	ADD_LADDER,		// Add Ladder Action
	ADD_SNAKE,		// Add Snake Action	
	ADD_CARD,		// Add Card Action	
	ADD_COINS,
	COPY,
	CUT,
	PASTE,
	ACTION_DELETE,
	SAVE,
	OPEN_GRID,
	EXIT,			// Exit Application
	TO_PLAY_MODE,	// Go to Play Mode

	///TODO: Add more action types of Design Mode

	//  [2] Actions of Play Mode

	ROLL_DICE,		// Roll Dice 
	ENTER_DICE_VALUE,
	OFFER_MORTGAGE,
	ACCEPT_MORTGAGE,
	RETURN_MORGAGE,
	SELL_CITY,
	NEW_GAME,
	//ITM_PLAY_EXIT,
	TO_DESIGN_MODE,	// Go to Design Mode


	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS 				// Inside StatusBar Area
};

#endif