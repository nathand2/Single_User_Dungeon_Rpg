#pragma once
#include <tuple>
#include <string>

class Player
{

public:
	int x;
	int y;

	std::string name;
	int health;
	int maxHealth;
	int defence;
	int dexterity;
	int attack;
	int stealth;

	Player();
	Player(int x, int y, std::string myName, int health, int defence, int dexterity, int attack, int stealth);
	~Player();

	std::string getPlayerAsString();
	void updateHealth(int modifierValue);

	void setHealth(int newHealth);
	int getHealth();

	void move(int targetX, int targetY);
	//void move(char direction, Board board, std::tuple<int, int> vector);
};

