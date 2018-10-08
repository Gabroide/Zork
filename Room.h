#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Creature.h"

using namespace std;


class Room
{
private:
	struct Door {
		string direction;
		string definition;
		Room* nextRoom;
		bool opened;
		string itemToOpen;
	};
	string name;
	string story;
	vector<Door> directions;
	list<Item*> listOfItemsInRoom;
	bool creaturePresent;
	Creature* creatureInTheRoom;

public:

	// Rooms
	Room();
	Room(string name);
	Room(string name, string story);
	Room(string name, string story, bool creaturePresent, Creature* creatureInTheRoom);
	~Room();

	// Asking
	string getName() const;
	bool isItemPresent(string itemName) const;
	bool isCreaturePresent() const;
	Creature* getCreature() const;
	void readRoom() const;
	Item* getItemByName(string itemName) const;

	// Modifying
	void creatureDies();
	void setDirection(string direction, string definition, Room* nextRoom, bool opened, string itemToOpen);
	void addItem(Item* item);
	void addCreature(Creature* creature);
	void removeItem(Item* item);
	Room* goTo(string direction);

};