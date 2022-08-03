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

	bool m_didBeatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Draw() override;

protected:
	void ProcessInput() override;
	void CheckBeatLevel();

private:
	void HandleCollisionForPlayer(int newPlayerX, int newPlayerY);
	void HandleCollisionForTrap(int trapX, int trapY);
	bool Load();
	void DrawHUD(const HANDLE& console);

	void HandleEnemyCollision(PlacableActor* collidedActor, int x, int y);
	void HandleMoneyCollision(PlacableActor* collidedActor, int x, int y);
	void HandleKeyCollision(PlacableActor* collidedActor, int x, int y);
	void HandleTrapCollision(PlacableActor* collidedActor, int x, int y);
	void HandleDoorCollision(PlacableActor* collidedActor, int x, int y);
	void HandleGoalCollision(PlacableActor* collidedActor, int x, int y);

	void LookAtCollision(PlacableActor* collidedActor, int x, int y);
};
