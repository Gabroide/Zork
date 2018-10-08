#include <iostream>
#include <string>
#include "World.h"

using namespace std;

int main()
{
	// First message
	cout << " I'm Zork! The orcs destruction." << endl;
	cout << " I've been jailed by that dirty rats." << endl;
	cout << " but what they don't know is that I've allowed them to jail me" << endl;
	cout << " If not... that green, stinky creatures would never jail me." << endl;
	cout << " Please, help me to scape from here and kill NightDead!" << endl;
	cout << endl;
	cout << endl;


	// Starting the world
	Utils utils;
	World world;
	world.Init();

	string input;

	while (1) {
		cin >> input;

		// Game loop
		int instruction = world.Iteration(utils.selectEnum(input));

		// End game
		if (instruction == 2)
		{
			return 0;
		}


		// Restart game because the player is dead
		else if (instruction == 1)
		{
			cout << endl;
			cout << endl;
			cout << " OH NO!!! Zork is dead! It will be a party tonight at Hell" << endl;
			cout << " Restarting the game" << endl;
			cout << endl;
			world.Init();
		}
	}
}