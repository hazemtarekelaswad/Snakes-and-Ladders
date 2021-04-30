#include"Alex_8.h"

Alex_8::Alex_8(const CellPosition &position)
	:Card(position){
	cardNumber = 8;
	m_cityOwner = NULL;
	m_originalOwner = NULL;
	isFirst = true;
}

Alex_8::Alex_8(){
	cardNumber = 8;
}

void Alex_8::ReadCardParameters(Grid *pGrid){

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();

	if(pGrid->GetFirstCard(cardNumber)){
		isFirst = false;
		Alex_8* firstCard = dynamic_cast<Alex_8*>(pGrid->GetFirstCard(cardNumber));
		m_cityPrice = firstCard->m_cityPrice;
		m_rent = firstCard->m_rent;
		outPtr->ClearStatusBar();
		return;
	}
	outPtr->PrintMessage("New Monopoly Card (8) | Alex City | Enter its Price: ");
	m_cityPrice = inPtr->GetInteger(outPtr);

	outPtr->PrintMessage("Alex City | Enter its Rent: ");
	m_rent = inPtr->GetInteger(outPtr);

	outPtr->ClearStatusBar();

}

void Alex_8::Apply(Grid *pGrid, Player *pPlayer){
	Card::Apply(pGrid, pPlayer);

	Input *inPtr = pGrid->GetInput();
	Output *outPtr = pGrid->GetOutput();
	int x, y;

	if(!m_cityOwner){
		string option;
		do{
			outPtr->PrintMessage("Do you want to buy Alex City? .. (y | n)");
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

void Alex_8::setCityOwner(Player* pPlayer){
	m_cityOwner = pPlayer;
}

Player* Alex_8::GetCityOwner() const{
	return m_cityOwner;
}

void Alex_8::SetOriginalOwner(Player* pPlayer){
	m_originalOwner = pPlayer;
}

Player* Alex_8::GetOriginalOwner() const{
	return m_originalOwner;
}

int Alex_8::GetCityPrice() const{
	return m_cityPrice;
}

int Alex_8::GetCityRent() const{
	return m_rent;
}


Alex_8::~Alex_8(){}

void Alex_8::Save(ofstream& outFile, Type gameObj)
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

void Alex_8::Load(ifstream& InFile){
	Card::Load(InFile);
	if(isFirst){
		int price;
		int rent;

		InFile >> price >> rent;
		m_cityPrice = price;
		m_rent = rent;
	}
}