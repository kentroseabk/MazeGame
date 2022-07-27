#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	bool m_beatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

	static constexpr int m_ignoreActorsLength = 2;
	static constexpr ActorType m_ignoreActors[m_ignoreActorsLength]{ ActorType::Player, ActorType::Trap };

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

private:
	void HandleCollision(int newPlayerX, int newPlayerY);
	void HandleCollisionForTrap(int trapX, int trapY);
	bool Load();
	void DrawHUD(const HANDLE& console);
};
