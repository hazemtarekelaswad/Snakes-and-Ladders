#include "ToPlayMode.h"

#include"Grid.h"
#include "NewGame.h"


ToPlayMode::ToPlayMode(ApplicationManager*pApp):Action(pApp)
{
	newGame = new NewGame(pApp);
}
void ToPlayMode::ReadActionParameters()
{}
void ToPlayMode::Execute()
{
	Grid *pG = pManager->GetGrid();
	Output *Out = pG->GetOutput();
	Input *pIn = pG->GetInput();

	
	Out->PrintMessage("Do you want to play? (y | n)");
	string p = pIn->GetSrting(Out);

	if (p == "Y" || p =="y")
	{
		Out->ClearStatusBar();
		Out->CreatePlayModeToolBar();
		newGame->Execute();
		
	}
	else 
		Out->ClearStatusBar();	
}

ToPlayMode::~ToPlayMode()
{
	delete newGame;
}