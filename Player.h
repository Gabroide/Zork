#pragma once

#include "Entity.h"
#include "Room.h"

class Player : public Entity
{
private:
	list<Item*> listOfInventory;
	Room* actualRoom;

public:

	// Player
	Player();
	Player(Room* actualRoom);
	~Player();

	// Asking
	Room* getActualRoom() const;
	bool isItemInTheInventory(string itemName) const;
	Item* getItemEquiped() const;
	Item* getItemByName(string itemName) const;
	void readItem(string itemName) const;
	void readInventory() const;

	// Modifying
	void setActualRoom(Room* actualRoom);
	void addItem(Item* item);
	void removeItem(Item* item);
	void equipItem(string itemName);
	void unequipItem();

};