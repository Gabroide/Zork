#include "Creature.h"

Creature::Creature()
{
	equipedItem = NULL;
}

Creature::Creature(Item* itemEquiped)
{
	this->itemEquiped = itemEquiped;
}

Creature::~Creature()
{
}

Item* Creature::getItemEquiped() const
{
	return itemEquiped;
}

void Creature::setItemEquiped(Item* itemEquiped)
{
	this->itemEquiped = itemEquiped;
}
