#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class MainMenuState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	MainMenuState(StateMachineExampleGame* pOwner);
	~MainMenuState() = default;

	void ProcessInput() override;
	virtual void Draw() override;

private:
	bool m_shouldQuit = false;
};

