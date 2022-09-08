#include <iostream>
#include <unordered_map>

#include "Player.h"
#include "Board.h"

#define LOG(x) std::cout << x << std::endl

enum Commands {
	QUIT,
	W,
	A,
	S,
	D,
	HELP
};


class Game
{
	std::unordered_map<char, std::tuple<int, int>> vectors = {
		{'W', std::make_tuple(0, -1)},
		{'A', std::make_tuple(-1, 0)},
		{'S', std::make_tuple(0, 1)},
		{'D', std::make_tuple(1, 0)}
	};
public:

	const std::string boardOne = "....?............../....................XXXXXXX......XXXXXXX......X......X............X......X................................X......X............X......X.....?XXXXXXX......XXXXXXX......X......X............X......X................................X......X.......?....X......X......XXXXXXX......XXXXXXX.....?X......X....?.......X......X................................X......X............X.....?X......";
	int playerOriginX = 0;
	int playerOriginY = 19;
	char playerSymbol = '&';
	Board board;
	Player player;
	Player* playerPointer;
	int encounterChance = 15; // (Chance/100) Ex: 15/100
	int damageChanceOnRun = 20; // 20% Chance of 1d4 damage on run
	int monsterBaseHealth = 5;


	Game()
	{
		board = Board(boardOne, 20, 20);

		std::string name;
		std::cout << "What is your name adventurer?:";
		std::cin >> name;
		 
		player = Player(playerOriginX, playerOriginY, name, 20, 0, 0, 6, 0);
		playerPointer = &player;

		std::cout << board.getBoardAsString(player.x, player.y, playerSymbol) << std::endl;

		std::srand((unsigned)std::time(0)); //use current time as seed for random generator. Used in encouters.
	}

	// Returns whether move to target tile is valid.
	bool isValidMove(int targetX, int targetY) {

		std::cout << "Target: " << targetX << ", " << targetY << "\n";

		if (targetX < 0 || targetX >= board.x) {

			std::cout << "Invalid Move (x vector). " << "\n";
			return false;
		}
		else if (targetY < 0 || targetY >= board.y) {
			std::cout << "Invalid Move (x vector). " << "\n";
			return false;
		}
		if (!board.getTile(targetX, targetY).tileType.isEnterable) {
			std::cout << "Invalid Move (Non-enterable tile). " << "\n";
			return false;
		}
		std::cout << "Move Is valid!" << std::endl;
		return true;
	}

	// Rolls a die. 
	int rollDie(int rolls, int faces) {
		int count = 0;
		int total = 0;
		while (count < rolls) {
			total += (std::rand() % faces) + 1; // (1, faces)
			count++;
		}
		return total;
	}

	// Prompt user to continue.
	void promptUserToContinue() {
		system("pause");	// Pause may only work on Windows. Not linux systems.
		std::cout << '\n' << "Press a key to continue..." << std::endl;
	}

	// Determines chance event of happening.
	// chanceOfEvent < 100.
	bool determineChanceEvent(int chanceOfEvent) {
		int randomVariable = std::rand() % 100; // (0, 100]
		std::cout << "Random Variable:" << randomVariable << std::endl;
		return randomVariable < chanceOfEvent;
	}

	// Determines encouter event.
	bool determineEncounter() {
		return determineChanceEvent(encounterChance);
	}

	// Attempt to run during an encounter.
	void attemptRun() {
		if (determineChanceEvent(damageChanceOnRun)) {

			int damage = rollDie(1, 4); // 1d4 damage on flee
			player.updateHealth(-damage);
			std::cout << "\nYou were struck in the back while running. You took " << damage << " damage." << std::endl;
		}
		else {
			std::cout << "\nYou ran away scot-free!" << std::endl;
		}
		promptUserToContinue();
	}

	// Attack round
	void attackRound(Player* attacker, Player* defender) {
		int damage = rollDie(1, (*attacker).attack);
		(*defender).updateHealth(-damage);
		//(*defender).setHealth((*defender).getHealth() - damage);
		std::cout << (*attacker).name << " hit " << (*defender).name << " for " << damage << " damage!" << std::endl;
	}

	// Fight during encounter with Goblin.
	void fight() {
		std::cout << "\nFighting the enemy" << std::endl;

		Player* attacker1;
		Player* attacker2;

		Player goblin = Player(-1, -1, "Goblin", monsterBaseHealth, 0, 0, 6, 0);

		// Determine initiative.
		if (determineChanceEvent(50)) {
			attacker1 = playerPointer;
			//Player temp = Player(-1, -1, "Goblin", monsterBaseHealth, 0, 0, 6, 0);
			attacker2 = &goblin;
		}
		else {
			//Player temp = Player(-1, -1, "Goblin", monsterBaseHealth, 0, 0, 6, 0);
			attacker1 = &goblin;
			attacker2 = playerPointer;
		}

		int currentAttacker = 1;
		int count = 0;
		while ((*attacker1).health > 0 && (*attacker2).health > 0 && count < 50) {

			std::cout << (*attacker1).getPlayerAsString() << std::endl;
			std::cout << (*attacker2).getPlayerAsString() << std::endl;
			if (currentAttacker == 1) {
				attackRound(attacker1, attacker2);
				currentAttacker = 2;
			}
			else {
				attackRound(attacker2, attacker1);
				currentAttacker = 1;
			}
			count++;
		}
		if ((*attacker1).health == 0) {
			std::cout << (*attacker1).name << " has fainted!" << std::endl;
		}
		else {
			std::cout << (*attacker2).name << " has fainted!" << std::endl;
		}

		std::cout << (*attacker1).getPlayerAsString() << std::endl;
		std::cout << (*attacker2).getPlayerAsString() << std::endl;
		promptUserToContinue();
	}

	// Encouter an enemy.
	void encounter() {
		std::cout << "Encountered an enemy!" << std::endl;
		

		std::string input;
		while (input != "QUIT") {
			std::cout << "\nDo you want to FIGHT(enter 'fight' or 1) or RUN(enter 'run' or 2)?: ";
			std::cin >> input;
			if (input == "fight" || input == "1") {
				std::cout << "\nAttempt to Fight." << std::endl;
				fight();
				return;
			}
			else if (input == "run" || input == "2") {
				std::cout << "\nAttempt to Run." << std::endl;
				attemptRun();
				return;
			}
			else {
				std::cout << "Invalid Input." << std::endl;
			}
		}
	}

	// Processes player move.
	void processPlayerMove(std::tuple<int, int> vector)
	{
		std::cout << "X: " << std::get<0>(vector) << "\n";
		std::cout << "Y: " << std::get<1>(vector) << "\n";
		int targetX = player.x + std::get<0>(vector);
		int targetY = player.y + std::get<1>(vector);

		// Return if not valid move.
		if (!isValidMove(targetX, targetY)) {
			return;
		}

		player.move(targetX, targetY);
		if (determineEncounter()) {
			encounter();
		}
		else {
			player.updateHealth(2); // Heal player after move with no encounter.
		}
	}

	// Checks whether player is on an exit tile
	bool checkIfPlayerOnExit() {
		return board.getTile(player.x, player.y).getSymbol() == '/';
	}


	// Starts the main game loop.
	void startGameLoop() {
		std::string input;

		while (input != "QUIT") {

			// Exit Game when you die.
			if (player.health == 0) {
				std::cout << player.name << " has fainted.\nThanks for playing! Exiting the program now. " << std::endl;
				return;
			}

			if (checkIfPlayerOnExit()) {
				std::cout << player.name << " has escaped the dungeon. Thanks for playing! Exiting the program now." << std::endl;
				return;
			}

			std::cout << "\nWhat would you like to do " << player.name << "? (Enter HELP for help):";
			std::cin >> input;
			if (input == "quit" || input == "Q" || input == "q") {
				std::cout << "\nThanks for playing! Exiting the program now. " << std::endl;
				break;
			}
			else if (input == "status") {
				std::cout << player.getPlayerAsString() << std::endl;
			}
			else if (input == "help" || input == "HELP") {
				std::cout << "Help Menu:" << "\n" <<
					"w/W : move up" << "\n"
					"a/A : move left" << "\n"
					"s/S : move down" << "\n"
					"d/D : move right" << "\n"
					"q/Q/quit : quits the game" << "\n"
					"help : shows help menu" << "\n"
					<< std::endl;
				promptUserToContinue();
			}
			else if (std::toupper(input[0]) == 'W' || std::toupper(input[0]) == 'A' || std::toupper(input[0]) == 'S' || std::toupper(input[0]) == 'D') {
				std::cout << "Move" << std::endl;
				std::tuple<int, int> vector = vectors.at(std::toupper(input[0]));
				processPlayerMove(vector);
			}
			else {
				std::cout << "Invalid Input." << std::endl;
			}

			std::cout << board.getBoardAsString(player.x, player.y, playerSymbol) << std::endl;
			std::cout << player.getPlayerAsString() << std::endl;
		}
	}
};


int main()
{

	std::cout << "Start Game!" << std::endl;
	Game game = Game();
	game.startGameLoop();
}
