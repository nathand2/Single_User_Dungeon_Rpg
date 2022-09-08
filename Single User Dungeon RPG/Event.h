#pragma once
#include <string>
class Event
{
public:
	std::string dialogue;
	int damage;
	std::string item;

	Event();
	Event(std::string dialogue, int damage);
};

