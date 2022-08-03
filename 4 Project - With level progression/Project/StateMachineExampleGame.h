#pragma once
#include "GameStateMachine.h"

class Game;
class GameState;

class StateMachineExampleGame : public GameStateMachine
{
public:
	enum class SceneName
	{
		None,
		MainMenu,
		Gameplay,
		Settings,
		HighScore,
		Lose,
		Win,
	};

private:
	Game* m_pOwner;

	GameState* m_pCurrentState;
	GameState* m_pNextState;

public:
	StateMachineExampleGame(Game* pOwner);

	virtual bool Init() override;
	virtual void UpdateCurrentState() override;
	virtual void DrawCurrentState() override;
	virtual void ProcessInput() override;
	virtual void ChangeState(GameState* pNewState) override;
	void LoadScene(SceneName scene);
	virtual bool Cleanup() override;
};

