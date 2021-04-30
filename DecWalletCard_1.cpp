#include "DecWalletCard_1.h"

DecWalletCard_1::DecWalletCard_1(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

DecWalletCard_1::DecWalletCard_1(){
	cardNumber = 1;
}

DecWalletCard_1::~DecWalletCard_1(void)
{
}

void DecWalletCard_1::ReadCardParameters(Grid * pGrid)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	Input * in = pGrid -> GetInput();
	Output * out = pGrid -> GetOutput();

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New DecWalletCard_1: Enter its wallet amount ..."
	
	out -> PrintMessage ("New DecWalletCard (1) | Enter its wallet amount ...");
	int a = 0;
	a = in -> GetInteger(out);
	walletAmount = (a < 0 ? 0 : a);

	// [ Note ]:
	// In DecWalletCard_1, the only parameter of DecWalletCard_1 is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar

	out -> ClearStatusBar();
}

void DecWalletCard_1::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply (pGrid, pPlayer);

	pPlayer -> SetWallet (pPlayer -> GetWallet() - walletAmount);

	Output * out = pGrid -> GetOutput();
	Input * in = pGrid -> GetInput();

	out -> PrintMessage("Your total wallet amount has decreaced to " + to_string (pPlayer -> GetWallet()) + " Coins | Click to continue ..");

	int x,y;
	in -> GetPointClicked(x,y);
	out -> ClearStatusBar();

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number

	// 2- Decrement the wallet of pPlayer by the walletAmount data member of DecWalletCard_1

}

void DecWalletCard_1::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << walletAmount << std::endl;
	}
}

void DecWalletCard_1::Load(ifstream& InFile){
	Card::Load(InFile);
	int wallet;
	InFile >> wallet;

	walletAmount = wallet;
}
