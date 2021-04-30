#include"Hurghada_11.h"

Hurghada_11::Hurghada_11(const CellPosition &position)
	:Card(position){
	cardNumber = 11;
	m_cityOwner = NULL;
	m_originalOwner = NULL;
	isFirst = true;
}

Hurghada_11::Hurghada_11(){
	cardNumber = 11;
}

void Hurghada_11::ReadCardParameters(Grid *pGrid){

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	if(pGrid->GetFirstCard(cardNumber)){
		isFirst = false;

		Hurghada_11* firstCard = dynamic_cast<Hurghada_11*>(pGrid->GetFirstCard(cardNumber));
		m_cityPrice = firstCard->m_cityPrice;
		m_rent = firstCard->m_rent;
		outPtr->ClearStatusBar();
		return;
	}
	outPtr->PrintMessage("New Monopoly Card (11) | Hurghada City | Enter its Price: ");
	m_cityPrice = inPtr->GetInteger(outPtr);

	outPtr->PrintMessage("Hurghada City | Enter its Rent: ");
	m_rent = inPtr->GetInteger(outPtr);

	outPtr->ClearStatusBar();

}

void Hurghada_11::Apply(Grid *pGrid, Player *pPlayer){

	Card::Apply(pGrid, pPlayer);

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();
	int x, y;

	if(!m_cityOwner){
		string option;
		do{
			outPtr->PrintMessage("Do you want to buy Hurghada City? .. (y | n)");
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

void Hurghada_11::setCityOwner(Player* pPlayer){
	m_cityOwner = pPlayer;
}

Player* Hurghada_11::GetCityOwner() const{
	return m_cityOwner;
}

void Hurghada_11::SetOriginalOwner(Player* pPlayer){
	m_originalOwner = pPlayer;
}

Player* Hurghada_11::GetOriginalOwner() const{
	return m_originalOwner;
}

int Hurghada_11::GetCityPrice() const{
	return m_cityPrice;
}

int Hurghada_11::GetCityRent() const{
	return m_rent;
}

Hurghada_11::~Hurghada_11(){}

void Hurghada_11::Save(ofstream& outFile, Type gameObj)
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

void Hurghada_11::Load(ifstream& InFile){
	Card::Load(InFile);
	if(isFirst){
		int price;
		int rent;

		InFile >> price >> rent;
		m_cityPrice = price;
		m_rent = rent;
	}
}