#include "GameplayState.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>

#include "Enemy.h"
#include "Key.h"
#include "Trap.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
	, m_didBeatLevel(false)
	, m_skipFrameCount(0)
	, m_currentLevel(0)
	, m_pLevel(nullptr)
{
	m_LevelNames.push_back("Level1.txt");
	m_LevelNames.push_back("Level2.txt");
	m_LevelNames.push_back("Level3.txt");
}

GameplayState::~GameplayState()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}

bool GameplayState::Load()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_player.Reset();

	m_pLevel = new Level();
	
	return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());

}

void GameplayState::Enter()
{
	Load();
}

void GameplayState::ProcessInput()
{
	int input = _getch();
	int arrowInput = 0;
	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	// One of the arrow keys were pressed
	if (input == kArrowInput)
	{
		arrowInput = _getch();
	}

	if ((input == kArrowInput && arrowInput == kLeftArrow) ||
		(char)input == 'A' || (char)input == 'a')
	{
		newPlayerX--;
	}
	else if ((input == kArrowInput && arrowInput == kRightArrow) ||
		(char)input == 'D' || (char)input == 'd')
	{
		newPlayerX++;
	}
	else if ((input == kArrowInput && arrowInput == kUpArrow) ||
		(char)input == 'W' || (char)input == 'w')
	{
		newPlayerY--;
	}
	else if ((input == kArrowInput && arrowInput == kDownArrow) ||
		(char)input == 'S' || (char)input == 's')
	{
		newPlayerY++;
	}
	else if (input == kEscapeKey)
	{
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	else if ((char)input == 'Z' || (char)input == 'z')
	{
		m_player.DropKey();
	}
	else if ((char)input == 'T' || (char)input == 't')
	{
		m_player.DropTrap();
	}

	// If position never changed
	if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
	{
		//return false;
	}
	else
	{
		HandleCollisionForPlayer(newPlayerX, newPlayerY);
	}

	// if the player is NOT holding the trap, see if it collided with an enemy
	if (!m_player.HasTrap())
	{
		// get trap currently in level
		Trap* trap = m_pLevel->GetTrap();

		// if trap was found in the level
		if (trap) HandleCollisionForTrap(trap->GetXPosition(), trap->GetYPosition());
	}
}

void GameplayState::CheckBeatLevel()
{
	// TODO: Create a function that handles this
	if (m_didBeatLevel)
	{
		++m_skipFrameCount;
		if (m_skipFrameCount > kFramesToSkip)
		{
			m_didBeatLevel = false;
			m_skipFrameCount = 0;
			++m_currentLevel;
			if (m_currentLevel == m_LevelNames.size())
			{
				Utility::WriteHighScore(m_player.GetMoney());

				AudioManager::GetInstance()->PlayWinSound();

				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
			}
			else
			{
				// On to the next level
				Load();
			}
		}
	}
}

bool GameplayState::Update(bool processInput)
{
	if (processInput && !m_didBeatLevel) ProcessInput();

	CheckBeatLevel();

	return false;
}

/*
	Updates all actors in the level and checks for collisions between the player and them.
*/
// TODO: Refactor 
void GameplayState::HandleCollisionForPlayer(int x, int y)
{
	m_pLevel->UpdateActors(x, y);

	vector<PlacableActor*> collidedActors = m_pLevel->CheckForCollisions(x, y);

	if (collidedActors.size() > 0)
	{
		for (auto& collidedActor : collidedActors)
		{
			if (collidedActor != nullptr && collidedActor->IsActive())
			{
				switch (collidedActor->GetType())
				{
				case ActorType::Enemy:
				{
					Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
					assert(collidedEnemy);
					AudioManager::GetInstance()->PlayLoseLivesSound();
					collidedEnemy->Remove();
					m_player.SetPosition(x, y);

					m_player.DecrementLives();
					if (m_player.GetLives() < 0)
					{
						//TODO: Go to game over screen
						AudioManager::GetInstance()->PlayLoseSound();
						m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
					}
					break;
				}
				case ActorType::Money:
				{
					Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
					assert(collidedMoney);
					AudioManager::GetInstance()->PlayMoneySound();
					collidedMoney->Remove();
					m_player.AddMoney(collidedMoney->GetWorth());
					m_player.SetPosition(x, y);
					break;
				}
				case ActorType::Key:
				{
					Key* collidedKey = dynamic_cast<Key*>(collidedActor);
					assert(collidedKey);
					if (!m_player.HasKey())
					{
						m_player.PickupKey(collidedKey);
						collidedKey->Remove();
						m_player.SetPosition(x, y);
						AudioManager::GetInstance()->PlayKeyPickupSound();
					}
					break;
				}
				case ActorType::Trap:
				{
					Trap* collidedTrap = dynamic_cast<Trap*>(collidedActor);
					assert(collidedTrap);
					if (!m_player.HasTrap())
					{
						m_player.PickUpTrap(collidedTrap);
						collidedTrap->Remove();
						m_player.SetPosition(x, y);
						AudioManager::GetInstance()->PlayTrapPickupSound();
					}
					break;
				}
				case ActorType::Door:
				{
					Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
					assert(collidedDoor);
					if (!collidedDoor->IsOpen())
					{
						if (m_player.HasKey(collidedDoor->GetColor()))
						{
							collidedDoor->Open();
							collidedDoor->Remove();
							m_player.UseKey();
							m_player.SetPosition(x, y);
							AudioManager::GetInstance()->PlayDoorOpenSound();
						}
						else
						{
							AudioManager::GetInstance()->PlayDoorClosedSound();
						}
					}
					else
					{
						m_player.SetPosition(x, y);
					}
					break;
				}
				case ActorType::Goal:
				{
					Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
					assert(collidedGoal);
					collidedGoal->Remove();
					m_player.SetPosition(x, y);
					m_didBeatLevel = true;
					break;
				}
				default:
					break;
				}
			}
		}
	}
	else if (m_pLevel->IsSpace(x, y)) // no collision
	{
		m_player.SetPosition(x, y);
	}
	else if (m_pLevel->IsWall(x, y))
	{
		// wall collision, do nothing
	}
}

/*
	Handles collision between player traps and enemies.
*/
void GameplayState::HandleCollisionForTrap(int x, int y)
{
	vector<PlacableActor*> collidedActors = m_pLevel->CheckForCollisions(x, y);

	for (auto& collidedActor : collidedActors)
	{
		if (collidedActor != nullptr && collidedActor->IsActive())
		{
			switch (collidedActor->GetType())
			{
			case ActorType::Enemy:
			{
				Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
				assert(collidedEnemy);
				AudioManager::GetInstance()->PlayEnemyDieSound();
				collidedEnemy->Remove();

				break;
			}
			default:
				break;
			}
		}
	}	
}

void GameplayState::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	// Set cursor position for player 
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	// Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
}

void GameplayState::DrawHUD(const HANDLE& console)
{
	cout << endl;

	// Top Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

	// Left Side border
	cout << Level::WAL;

	cout << " wasd-move " << Level::WAL << " z-drop key " << Level::WAL;

	cout << " $:" << m_player.GetMoney() << " " << Level::WAL;
	cout << " lives:" << m_player.GetLives() << " " << Level::WAL;
	cout << " key:";
	if (m_player.HasKey())
	{
		m_player.GetKey()->Draw();
	}
	else
	{
		cout << " ";
	}

	// RightSide border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = m_pLevel->GetWidth() - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	// horizontal Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}

	cout << endl;
	
	// Left Side border
	cout << Level::WAL;

	cout << " t-drop trap " << Level::WAL << " trap:";

	if (m_player.HasTrap())
	{
		m_player.GetTrap()->Draw();
	}
	else
	{
		cout << " ";
	}
	
	cout << " ";

	const int widthRemaining = 26;

	for (int i = 0; i < widthRemaining; i++)
	{
		cout << Level::WAL;
	}

	cout << Level::WAL << endl;

	// Bottom Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;
}