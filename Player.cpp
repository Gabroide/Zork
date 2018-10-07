#include "Player.h"

Player::Player()
{
	equipedItem = NULL;
}

Player::Player(Room* actualRoom)
{
	this->actualRoom = actualRoom;
	equipedItem = NULL;
}

Player::~Player()
{
}


Room* Player::getActualRoom() const
{
	return actualRoom;
}

void Player::setActualRoom(Room* actualRoom)
{
	this->actualRoom = actualRoom;
}

void Player::addItem(Item* item)
{
	listOfInventory.push_back(item);
}

void Player::removeItem(Item* item)
{
	listOfInventory.remove(item);
}

void Player::readInventory() const
{
	if (listOfInventory.size() == 0)
		cout << "Bag is empty. What can Zork take from an empty bag Master?" << endl;
	else
	{
		cout << "The bag has something. Zork is provided with:" << endl;
		for (std::list<Item*>::const_iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
		{
			cout << " " << (*it)->getName() << endl;
		}
	}
}

bool Player::isItemInTheInventory(string itemName) const
{
	for (std::list<Item*>::const_iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
	{
		if ((*it)->getName() == itemName)
			return true;
	}
	return false;
}

void Player::readItem(string itemName) const
{
	for (std::list<Item*>::const_iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
	{
		if ((*it)->getName() == itemName)
		{
			cout << " " << (*it)->readIt() << endl;
			return;
		}
	}
	cout << "Zork hasn't that thing in the bag. Has it the Master?" << endl;
}


void Player::equipItem(const string itemName)
{
	if (itemName != "blade" && itemName != "knife") cout << "Zork cannot use it." << endl;
	else {
		for (std::list<Item*>::iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
		{
			if ((*it)->getName() == itemName)
			{
				equipedItem = (*it);
				cout << "Zork is using a " << itemName << "." << endl;
				return;
			}
		}
		cout << "Zork cannot find that thing at bag." << endl;
	}
}

void Player::unequipItem()
{
	if (equipedItem == NULL)
		cout << "Zork can only fight with his bare hands. Zork needs a weapon!" << endl;
	else
	{
		cout << " " << equipedItem->getName() << " unequiped." << endl;
		equipedItem = NULL;
	}
}

Item* Player::getItemEquiped() const
{
	return equipedItem;
}

Item* Player::getItemByName(string itemName) const
{
	for (std::list<Item*>::const_iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
	{
		if ((*it)->getName() == itemName)
			return (*it);
	}
	return NULL;
}