#include "Player.h"
#include "Board.h"
#include <iostream>


Player::Player() {}

Player::Player(int x, int y, std::string name, int health, int defence, int dexterity, int attack, int stealth)
{
	Player::x = x;
	Player::y = y;
	Player::name = name;
	Player::health = health;
	Player::maxHealth = health;
	Player::defence = defence;
	Player::dexterity = dexterity;
	Player::attack = attack;
	Player::stealth = stealth;


	
}
Player::~Player()
{
	std::cout << "Player: " << Player::name << " has been deconstructed" << std::endl;
}
std::string Player::getPlayerAsString() {
		return "Name: " + std::string(Player::name) +
			" x: " + std::to_string(Player::x) +
			" y: " + std::to_string(Player::y) +
			" Health: " + std::to_string(Player::health) +
			" defence: " + std::to_string(Player::defence) +
			" dexterity: " + std::to_string(Player::dexterity) +
			" attack: " + std::to_string(Player::attack) +
			" stealth: " + std::to_string(Player::stealth);
}
void Player::updateHealth(int modifierValue) {
	Player::health += modifierValue;
	if (Player::health < 0) {
		Player::health = 0;
	}
	else if (Player::health > Player::maxHealth) {
		Player::health = Player::maxHealth;
	}
 }

void Player::setHealth(int newHealth)
{
	Player::health = newHealth;
}

int Player::getHealth()
{
	return Player::health;
}

void Player::move(int targetX, int targetY)
{
	Player::x = targetX;
	Player::y = targetY;
}




//void Player::move(char direction, Board board, std::tuple<int, int> vector) {
//	/*if (board.getTile(std::get<0>(vector), std::get<1>(vector)).isEnterable)
//	{
//		Player::x = Player::x + std::get<0>(vector);
//		Player::y+= Player::y + std::get<1>(vector);
//	}*/
//
//}

