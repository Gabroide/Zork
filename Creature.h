#pragma once

#include "Entity.h"

class Creature : public Entity
{
private:
	Item* itemEquiped;
public:
	Creature();
	Creature(Item* itemEquiped);
	~Creature();

	Item* getItemEquiped() const;
	void setItemEquiped(Item* itemEquiped);
};