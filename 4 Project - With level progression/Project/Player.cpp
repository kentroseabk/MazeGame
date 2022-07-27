#include <iostream>

#include "Player.h"
#include "Key.h"
#include "Trap.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player()
	: PlacableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberOfLives)
{

}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

bool Player::HasTrap()
{
	return m_pTrap != nullptr;
}

void Player::DropTrap()
{
	if (m_pTrap)
	{
		AudioManager::GetInstance()->PlayTrapDropSound();
		m_pTrap->Place(m_pPosition->x, m_pPosition->y);
		m_pTrap = nullptr;
	}
}

void Player::PickUpTrap(Trap* trap)
{
	m_pTrap = trap;
}

void Player::Draw()
{
	cout << "@";
}

void Player::Reset()
{
	m_pTrap = nullptr;
}
