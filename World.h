#pragma once
#include <vector>
#include "Player.h"
#include "Creature.h"
#include <time.h>
#include "Utils.h"

class World
{
private:
	Player player;
	clock_t timeWhenYouEnter;
	bool creaturePresentInTheRoom;
	Utils utils;
	Creature orc1, orc2, dragon;
	Room dungeon, corridor, hall, library, aboveRoom, dragonCave, exit;
	Item paper, bone, knife, blade, vault, knifeCreature, bladeCreature, fireCreature;

public:
	World();
	~World();

	void Init();
	
	int Iteration(InputOrder io);
};