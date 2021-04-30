#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	// Make all the needed initialization or validations

	this->pCell = pCell;
	this->turnCount = 0;

	PreventState = false;	// A default of player's prevention state
	Freeze = false;			// A default of player's freeze state for freeze Card
	Benefit = false;		// A default of player's benefitit all state for BenefitAll Card
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell){
	pCell = cell;
}

Cell* Player::GetCell() const{
	return pCell;
}

void Player::SetWallet(int wallet){
	this->wallet = (wallet > 0 ? wallet : 0);
}

int Player::GetWallet() const{
	return wallet;
}

int Player::GetStepCount() const{
	return stepCount;
}

void Player::SetTurnCount(int count){
	if(count >= 0 && count <= 3)
		turnCount = count;
}

int Player::GetTurnCount() const{
	return turnCount;
}

int Player::getPlayerNum() const{
	return  playerNum;
}

int Player::GetjustRolledDiceNum(){
	return justRolledDiceNum;
}

CellPosition Player::GetPlayerCellPosition()
{
	return (pCell -> GetCellPosition());
}


//============ Special Setters and Getters for card states and cities ============

void Player::setPreventState(bool state){
	PreventState = state;
}

bool Player::getPreventState(){
	return PreventState;
}

void Player::SetNrOfTurnsToFreeze(int nr){
	nrOfTurnsToFreeze = nr;
}

int Player::GetNrOfTurnsToFreeze() const{
	return nrOfTurnsToFreeze;
}

void Player::SetNrOfTurnsToBenefit(int nr){
	nrOfTurnsToBenefit = nr;
}

int Player::GetNrOfTurnsToBenefit() const{
	return nrOfTurnsToBenefit;
}

void Player::SetFreeze(bool Freeze){
	this->Freeze = Freeze;
}

bool Player::GetFreeze() const{
	return Freeze;
}

void Player::SetBenefit(bool Benefit){
	this->Benefit = Benefit;
}

bool Player::GetBenefit() const{
	return Benefit;
}

void Player::setCheckAnothRoll(bool state){
	CheckAnothRoll = state;
}

bool Player::getCheckAnothRoll(){
	return CheckAnothRoll;
}

void Player::SetCityOwner(Player* owner){ 
	cityOwner = owner; 
}

Player* Player::GetCityOwner() const{ 
	return cityOwner; 
}

void Player::SetCityNumber(int number) {
	cityNumber = number; 
}

int Player::GetCityNumber() const{ 
	return cityNumber; 
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{

	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut ->DrawPlayer(pCell->GetCellPosition(), playerNum, UI.PlayerColors[playerNum]);
}

void Player::ClearDrawing(Output* pOut) const
{
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut ->DrawPlayer(pCell ->GetCellPosition() , playerNum , (pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard));
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once

	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)

	// 3- Set the justRolledDiceNum with the passed diceNumber

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

	// 6- Apply() the game object of the reached cell (if any)
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();
	int x,y;

	Player * CurrPlayer = pGrid -> GetCurrentPlayer();

	turnCount++;

	if (turnCount == 3)
	{
		
		wallet += diceNumber * 10;

		out ->PrintMessage("Your total wallet amount has increased by: " + to_string(diceNumber * 10) + " Coins | Click to continue ..");
		in->GetPointClicked(x,y);
		out ->ClearStatusBar();

		out ->PrintMessage("Your new wallet amount has increased to: " + to_string(wallet) + " Coins | Click to continue ..");
		in->GetPointClicked(x,y);
		out ->ClearStatusBar();

		turnCount = 0;
		return;
	}

	if (!CurrPlayer->GetWallet())
	{
		out ->PrintMessage("You have no money! wait for the recharging | Click to continue ...");
		in->GetPointClicked(x,y);
		out ->ClearStatusBar();
		return;
	}

	justRolledDiceNum = diceNumber;

	CellPosition pos = CurrPlayer ->GetCell() ->GetCellPosition();
	pos.AddCellNum(justRolledDiceNum);

	pGrid ->UpdatePlayerCell(CurrPlayer, pos);

	CellPosition checkCellPosition = pos, tempCellPosition = pos;

	bool check = true;

	CurrPlayer ->setCheckAnothRoll(false);

	while (pGrid->GetGameObject(checkCellPosition))
	{
		if (check)
		{
			tempCellPosition = checkCellPosition;
			pGrid->GetGameObject(checkCellPosition)->Apply(pGrid,CurrPlayer);
			checkCellPosition = CurrPlayer ->GetCell()->GetCellPosition();
			check = false;
		}

		else if (pGrid ->GetGameObject(checkCellPosition) != pGrid ->GetGameObject(tempCellPosition))
		{
			tempCellPosition = checkCellPosition;
			pGrid ->GetGameObject(checkCellPosition)->Apply(pGrid,CurrPlayer);
			checkCellPosition = CurrPlayer->GetCell()->GetCellPosition();
		}

		else if (pGrid ->GetGameObject(checkCellPosition) == pGrid ->GetGameObject(tempCellPosition))
			break;
	} 

	if (pos.GetCellNum() == 99)
		pGrid ->SetEndGame(true);
}



void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(3 - turnCount) + ")";
}