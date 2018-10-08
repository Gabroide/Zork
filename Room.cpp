#include "Room.h"

Room::Room()
{
	name = "uknown";
	story = "";
	creaturePresent = false;
	creatureInTheRoom = NULL;
}

Room::Room(string name)
{
	this->name = name;
	story = "";
	creaturePresent = false;
	creatureInTheRoom = NULL;
}

Room::Room(string name, string story)
{
	this->name = name;
	this->story = story;
	creaturePresent = false;
	creatureInTheRoom = NULL;
}

Room::Room(string name, string story, bool creaturePresent, Creature* creaureInTheRoom)
{
	this->name = name;
	this->story = story;
	this->creaturePresent = creaturePresent;
	this->creatureInTheRoom = creatureInTheRoom;
}

Room::~Room()
{
}

string Room::getName() const
{
	return name;
}

void Room::setDirection(string direction, string definition, Room* nextRoom, bool opened, string itemToOpen)
{
	Door door = { direction, definition, nextRoom, opened, itemToOpen };
	directions.push_back(door);
}

Room* Room::goTo(string direction)
{
	for (int i = 0; i < directions.size(); ++i)
	{
		if (direction == directions[i].direction)
		{
			return directions[i].nextRoom;
		}
	}
	return NULL;
}

void Room::readRoom() const
{
	cout << "<-- " << story << endl;
	for (int i = 0; i < directions.size(); ++i)
	{
		if (directions[i].direction == "up" || directions[i].direction == "down")
			cout << "<-- You can see " << directions[i].definition << " going " << directions[i].direction << ". ";
		else
			cout << "<-- At the " << directions[i].direction << " you can see " << directions[i].definition << ". ";
		if (!directions[i].opened)
			cout << "It seems that the door is closed.";
		cout << endl;
	}
	if (!listOfItemsInRoom.empty())
	{
		cout << "Zoork sees " << endl;
		for (std::list<Item*>::const_iterator it = listOfItemsInRoom.begin(); it != listOfItemsInRoom.end(); ++it)
		{
			if ((*it)->isInsideAnItem())
				cout << " " << (*it)->getName() << " is inside a " << (*it)->getItemOutside()->getName() << endl;
			else if ((*it)->youCanOpenIt() && (*it)->isOpened())
				cout << "Zork found opened a " << (*it)->getName() << endl;
			else if ((*it)->youCanOpenIt() && !(*it)->isOpened())
				cout << " A " << (*it)->getName() << " closed." << endl;
			else
				cout << " A " << (*it)->getName() << endl;
		}
		cout << endl;
	}
	if (creaturePresent)
	{
		cout << " Zork can smell can something! Zorc must be quite to kill that creture." << endl;
		if (creatureInTheRoom->getItemEquiped()->getName() == "knife")
		{
			cout << " The orc has a knfe! Zork don't believe orcs can use knifes." << endl;
		}
		if (creatureInTheRoom->getItemEquiped()->getName() == "blade")
		{
			cout << " The orc has a blade! But a bladeis just a long knife in the darkness..." << endl;
		}
	}
}

void Room::addItem(Item* item)
{
	listOfItemsInRoom.push_back(item);
}

void Room::removeItem(Item* item)
{
	listOfItemsInRoom.remove(item);
}

bool Room::isItemPresent(string itemName) const
{
	for (std::list<Item*>::const_iterator it = listOfItemsInRoom.begin(); it != listOfItemsInRoom.end(); ++it)
	{
		if ((*it)->getName() == itemName)
			return true;
	}
	return false;
}

void Room::addCreature(Creature* creature)
{
	creaturePresent = true;
	creatureInTheRoom = creature;
}

void Room::creatureDies()
{
	listOfItemsInRoom.push_back(creatureInTheRoom->getItemEquiped());
	creaturePresent = false;
	creatureInTheRoom = NULL;
}

bool Room::isCreaturePresent() const
{
	return creaturePresent;
}

Creature* Room::getCreature() const
{
	return creatureInTheRoom;
}

Item* Room::getItemByName(string itemName) const
{
	for (std::list<Item*>::const_iterator it = listOfItemsInRoom.begin(); it != listOfItemsInRoom.end(); ++it)
	{
		if ((*it)->getName() == itemName)
			return (*it);
	}
	return NULL;
}