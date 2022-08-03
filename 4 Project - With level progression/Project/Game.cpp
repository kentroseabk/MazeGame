#include "Game.h"
#include <chrono>

Game::Game()
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine != nullptr)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}

void Game::RunGameLoop()
{
	while (!m_pStateMachine->m_gameOver)
	{
		Update();
		Draw();
		ProcessInput();
	}

	Draw();
}

void Game::Deinitialize()
{
	if (m_pStateMachine != nullptr)
		m_pStateMachine->Cleanup();
}

void Game::Update()
{
	m_pStateMachine->UpdateCurrentState();
}

void Game::Draw()
{
	uint32_t now = GetTime();

	if (now > m_timeOfLastFrame + m_FRAME_TIME_MS)
	{
		m_pStateMachine->DrawCurrentState();
		m_timeOfLastFrame = now;
	}
}

void Game::ProcessInput()
{
	m_pStateMachine->ProcessInput();
}

uint32_t Game::GetTime()
{
	using namespace std::chrono;
	return static_cast<uint32_t>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}
