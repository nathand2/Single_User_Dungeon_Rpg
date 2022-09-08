#include "Event.h"

Event::Event()
{
}

Event::Event(std::string dialogue, int damage)
{
	Event::dialogue = dialogue;
	Event::damage = damage;
}
