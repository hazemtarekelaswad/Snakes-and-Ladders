#include"Cairo_7.h"

Cairo_7::Cairo_7(const CellPosition &position)
	:Card(position){
		cardNumber = 7;
		m_cityOwner = NULL;
		m_originalOwner = NULL;
		isFirst = true;
}

Cairo_7::Cairo_7(){
	cardNumber = 7;
}

void Cairo_7::ReadCardParameters(Grid *pGrid){

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	if(pGrid->GetFirstCard(cardNumber)){
		isFirst = false;

		Cairo_7* firstCard = dynamic_cast<Cairo_7*>(pGrid->GetFirstCard(cardNumber));
		m_cityPrice = firstCard->m_cityPrice;
		m_rent = firstCard->m_rent;
		outPtr->ClearStatusBar();
		return;
	}
	outPtr->PrintMessage("New Monopoly Card (7) | Cairo City | Enter its Price: ");
	m_cityPrice = inPtr->GetInteger(outPtr);

	outPtr->PrintMessage("Cairo City | Enter its Rent: ");
	m_rent = inPtr->GetInteger(outPtr);

	outPtr->ClearStatusBar();

}

void Cairo_7::Apply(Grid *pGrid, Player *pPlayer){

	Card::Apply(pGrid, pPlayer);

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();
	int x, y;

	if(!m_cityOwner){
		string option;
		do{
			outPtr->PrintMessage("Do you want to buy Cairo City? .. (y | n)");
			option = inPtr->GetSrting(outPtr);

		} while(option != "y" && option != "Y" && option != "n" && option != "N");

		if(option == "n" || option == "N"){
			outPtr->ClearStatusBar();
			return;
		}

		if(pPlayer->GetWallet() < m_cityPrice){
			outPtr->PrintMessage("Sorry, you don't have enough coins to buy this city! Click to continue ...");
			inPtr->GetPointClicked(x,y);
			outPtr->ClearStatusBar();
			return;
		}

		pPlayer->SetWallet(pPlayer->GetWallet() - m_cityPrice);
		outPtr->PrintMessage("Your new wallet amount: " + to_string(pPlayer->GetWallet()) + " Coins");

		inPtr->GetPointClicked(x,y);
		outPtr->ClearStatusBar();

		m_cityOwner = pPlayer;
		pGrid->SetCityOwner(m_cityOwner, cardNumber);
	}

	else if(pPlayer->getPlayerNum() != m_cityOwner->getPlayerNum()){
		pPlayer->SetWallet(pPlayer->GetWallet() - m_rent);
		outPtr->PrintMessage("Your new wallet amount: " + to_string(pPlayer->GetWallet()) + " Coins");

		inPtr->GetPointClicked(x, y);
		outPtr->ClearStatusBar();

		m_cityOwner->SetWallet(m_cityOwner->GetWallet() + m_rent);
		outPtr->PrintMessage("Cairo City Owner's new wallet amount: " + to_string(m_cityOwner->GetWallet()) + " Coins");

		inPtr->GetPointClicked(x, y);
		outPtr->ClearStatusBar();
	}	
}

void Cairo_7::setCityOwner(Player* pPlayer){
	m_cityOwner = pPlayer;
}

Player* Cairo_7::GetCityOwner() const{
	return m_cityOwner;
}

void Cairo_7::SetOriginalOwner(Player* pPlayer){
	m_originalOwner = pPlayer;
}

Player* Cairo_7::GetOriginalOwner() const{
	return m_originalOwner;
}

int Cairo_7::GetCityPrice() const{
	return m_cityPrice;
}

int Cairo_7::GetCityRent() const{
	return m_rent;
}

Cairo_7::~Cairo_7(){}

void Cairo_7::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);

		if(isFirst)
			outFile << m_cityPrice << ' ' << m_rent << std::endl;
		else 
			outFile << std::endl;
	}
}

void Cairo_7::Load(ifstream& InFile){
	Card::Load(InFile);
	if(isFirst){
		int price;
		int rent;

		InFile >> price >> rent;
		m_cityPrice = price;
		m_rent = rent;
	}
}
