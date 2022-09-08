#pragma once
#include <string>
#include "Tile.h"

class Board
{
	static const int maxBoardSize = 40;
private:
	Tile board[maxBoardSize][maxBoardSize];


	void populateBoardUsingStringRep(const std::string& boardStringRepresentation, int xDimen, int yDimen);

public:
	int x;	// Width
	int y;	// Height
	Board();
	Board(const std::string& boardStringRep, int xDimen, int yDimen);
	void setBoardTile(char chr, int x, int y);
	char getBoardTileSymbol(int x, int y);
	std::string getBoardAsString(int playerX, int playerY, char playerSymbol);
	std::string getBoardAsStringEnterableTiles(int playerX, int playerY, char playerSymbol);
	Tile getTile(int x, int y);
};


