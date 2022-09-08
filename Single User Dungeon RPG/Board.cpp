#include "Board.h"
#include <iostream>

Board::Board() {}

Board::Board(const std::string& boardStringRep, int xDimen, int yDimen)
{
	Board::populateBoardUsingStringRep(boardStringRep, xDimen, yDimen);
	Board::x = xDimen;
	Board::y = yDimen;
}

void Board::populateBoardUsingStringRep(const std::string& boardStringRepresentation, int xDimen, int yDimen)
{
	int y = 0;
	while (y < yDimen * 20)
	{
		int x = 0;
		while (x < xDimen)
		{
			Board::setBoardTile(boardStringRepresentation[y + x], x, y / 20);
			x++;
		}
		y += 20;
	}
	std::cout << "Populating Board" << std::endl;
}

void Board::setBoardTile(char symbol, int x, int y)
{
	Board::board[x][y].tileType = TileTypeFactory::createTileType(symbol);
}

char Board::getBoardTileSymbol(int x, int y)
{
	return Board::board[x][y].getSymbol();
}


std::string Board::getBoardAsString(int playerX, int playerY, char playerSymbol)
{
	std::string result = "";
	for (int i = 0; i < Board::x; i++)
	{
		for (int j = 0; j < Board::y; j++)
		{
			if (playerX == j && playerY == i){
				std::string s(1, playerSymbol);
				result += s + " ";
			}
			else {
				std::string s(1, Board::getBoardTileSymbol(j, i));
				result += s + " ";
			}
		}
		result += "\n";
	}

	return result;
}

std::string Board::getBoardAsStringEnterableTiles(int playerX, int playerY, char playerSymbol)
{
	std::string result = "";
	std::cout << "boardx: " << Board::x;
	std::cout << "boardy: " << Board::y << "\n";
	for (int i = 0; i < Board::x; i++)
	{
		for (int j = 0; j < Board::y; j++)
		{
			if (playerX == j && playerY == i) {
				std::string s(1, playerSymbol);
				result += s + " ";
			}
			else {
				if (Board::getTile(j, i).tileType.isEnterable) {
					result += "Y ";
				}
				else {
					result += "N ";
				}
			}
		}
		result += "\n";
	}
	return result;
}

Tile Board::getTile(int x, int y)
{
	return Board::board[x][y];
}