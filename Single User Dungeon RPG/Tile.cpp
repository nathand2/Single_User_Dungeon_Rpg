#include "Tile.h"
#include <tuple>

enum Events
{
	none,
	potionDropEvent,
	damageEvent,
	dialogueEvent
};

Tile::Tile()
{
	Tile::x = -1;
	Tile::y = -1;
	Tile::tileType = TileTypeFactory::createTileType('.');
}

Tile::Tile(char symbol, int x, int y)
{
	Tile::x = x;
	Tile::y = y;
	Tile::tileType = TileTypeFactory::createTileType(symbol);

}


GenericTileType::GenericTileType(char symbol) {
	GenericTileType::symbol = symbol;
	GenericTileType::isEnterable = true;
	GenericTileType::event = Event::Event("The way is dark...\n", 0);
}

ObstacleTileType::ObstacleTileType(char symbol) {
	ObstacleTileType::symbol = symbol;
	ObstacleTileType::isEnterable = false;
	ObstacleTileType::event = Event::Event("", 0);
}

EventTileType::EventTileType(char symbol) {
	EventTileType::symbol = symbol;
	EventTileType::isEnterable = true;
	EventTileType::event = Event::Event("You stepped in some broken glass.\n", 5);
}

char Tile::getSymbol() {
	return Tile::tileType.symbol;
}




TileType TileTypeFactory::createTileType(char symbol)
{
	if (symbol == 'X') {
		return TileTypeFactory::createObstacleTileType(symbol);
	}
	else if (symbol == '?') {
		return TileTypeFactory::createEventTileType(symbol);
	}
	else {
		return TileTypeFactory::createGenericTileType(symbol);
	}
};
TileType TileTypeFactory::createGenericTileType(char symbol)
{
	return GenericTileType::GenericTileType(symbol);
};
TileType TileTypeFactory::createObstacleTileType(char symbol)
{
	return ObstacleTileType::ObstacleTileType(symbol);
};
TileType TileTypeFactory::createEventTileType(char symbol)
{
	return EventTileType::EventTileType(symbol);
};
