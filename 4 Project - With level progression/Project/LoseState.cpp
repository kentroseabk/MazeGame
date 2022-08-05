#include "LoseState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;


LoseState::LoseState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void LoseState::ProcessInput()
{
	int input = -1;

	if (_kbhit())
	{
		input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}

}

void LoseState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - GAME OVER - - -" << endl << endl;
	cout << "             Better luck next time." << endl << endl << endl;
	cout << "             Press any key to go back to the main menu" << endl << endl << endl;
}