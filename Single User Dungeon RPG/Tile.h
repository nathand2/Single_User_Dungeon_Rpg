#pragma once

#include "Event.h"

enum Events;

// Base TyleType Class
class TileType
{
public:
	char symbol;
	bool isEnterable;
	Event event;
};

class GenericTileType: public TileType
{
public:
	GenericTileType();
	GenericTileType(char symbol);
};

class ObstacleTileType : public TileType
{
public:
	ObstacleTileType();
	ObstacleTileType(char symbol);
};

class EventTileType : public TileType
{
public:
	EventTileType();
	EventTileType(char symbol);
};


class TileTypeFactory
{
public:
	static TileType createTileType(char symbol);
	static TileType createGenericTileType(char symbol);
	static TileType createObstacleTileType(char symbol);
	static TileType createEventTileType(char symbol);
};

class Tile
{
private:
	int x;
	int y;
	//char symbol;
public:

	//bool isEnterable;
	TileType tileType;
	Tile();
	Tile(char symbol, int x, int y);
	char getSymbol();
};

