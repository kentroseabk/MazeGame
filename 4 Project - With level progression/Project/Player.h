#pragma once
#include "PlacableActor.h"

class Key;
class Trap;

class Player : public PlacableActor
{
public:
	Player();

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }

	bool HasTrap();
	void DropTrap();
	void PickUpTrap(Trap* trap);
	Trap* GetTrap() { return m_pTrap; }

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;

	void Reset();

private:
	Key* m_pCurrentKey;
	Trap* m_pTrap;
	int m_money;
	int m_lives;
};
