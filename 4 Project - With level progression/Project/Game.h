#pragma once
#include "GameStateMachine.h"
#include "Player.h"
#include "Level.h"
#include <thread>

class Game
{
	GameStateMachine* m_pStateMachine;
public:
	Game();
	void Initialize(GameStateMachine* pStateMachine);
	void RunGameLoop();
	void Deinitialize();

private:
	void Update();
	void ProcessInput();
	void Draw();
	void UpdateAndRender();
	uint32_t GetTime();

	// how many times per second to draw the level
	const float m_FPS = 60;
	const float m_FRAME_TIME_MS = 1000 / m_FPS;
	uint32_t m_timeOfLastFrame = 0;

	// how many times per second to update the game world 
	const float m_UPDATES_PER_SECOND = 1;
	const float m_UPDATE_TIME_MS = 1000 / m_UPDATES_PER_SECOND;
	uint32_t m_timeOfLastUpdate = 0;

	// how many times per second to check user input
	const float m_INPUT_PER_SECOND = 10;
	const float m_INPUT_TIME_MS = 1000 / m_INPUT_PER_SECOND;
	uint32_t m_timeOfLastInput = 0;

	std::thread m_updateAndRenderThread;
};