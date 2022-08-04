#pragma once
#include <string>
#include <vector>

class PlacableActor;
enum class ActorType;
class Trap;

class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;

	std::vector<PlacableActor*> m_pActors;

public:
	Level();
	~Level();

	bool Load(std::string levelName, int* playerX, int* playerY);
	void Draw();
	void UpdateActors();
	std::vector<PlacableActor*> CheckForCollisions(int x, int y);

	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);

	Trap* GetTrap();

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width;  }

	static constexpr char WAL = (char)219;

private:
	bool ConvertLevel(int* playerX, int* playerY);
	int GetIndexFromCoordinates(int x, int y);
	bool IsValidCollision(int x, int y, PlacableActor* actor);

};