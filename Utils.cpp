#include "Utils.h"

Utils::Utils()
{

}

Utils::~Utils()
{

}

bool Utils::playerWinsOrLoses(string action, Item* playerItem, Item* creatureItem, clock_t timeAtRoom) const
{
	if (timeAtRoom >= 10000)
	{
		if (creatureItem->getName() == "fire")
		{
			cout << " NighDead is devouring Zork.. After it he will be hungry. you'ld RUN!!." << endl;
		}
		else if (creatureItem->getName() == "blade")
		{
			cout << " Orc stabed you with his blade." << endl;
		}
		else
		{
			cout << " The orc has throw you his knife." << endl;
		}
	return false;
	}

	else if (playerItem == NULL)
	{
		cout << " Zork has no weapon. Zork's hands are lke a treasure, I won't use them against orcs." << endl;
		if (creatureItem->getName() == "fire")
		{
			cout << " Can you smell Zork's burnt flesh? NightDead has burnt Zork." << endl;
		}
		else if (creatureItem->getName() == "blade")
		{
			cout << " The orc has stabbed with his blade." << endl;
		}
		else
		{
			cout << " The orc has stabbed Zorc." << endl;
		}
		return false;
	}

	else if (playerItem->getName() == "bone")
	{
		if (action == "throw")
		{
			cout << " Throw a bonw? May be Zork will kill the orc beacause he won't be able to stop laughing" << endl;
			srand(time(NULL));
			if ((rand() % 10 + 0.5) <= 5)
			{
				cout << " Incredible! Zork has throw the bone to his head and the orc was without helmet." << endl;
				return true;
			}
			else
			{
				cout << " The orc has catch the bone with his hand smiling. Now he is coming to kill Zork with his weapon." << endl;
				return false;
			}
		}
	}

	else if (playerItem->getName() == "knife")
	{
		if (action == "throw")
		{
			cout << " Zork throwed the knive to the creature..." << endl;
			srand(time(NULL));
			if ((rand() % 10 + 1) <= 5)
			{
				cout << " Zork's a great knife launcher! The orc has been killed." << endl;
				return true;
			}
			else
			{
				cout << " Zork needs to practice more with knifes... Now the orc is quite angry and is running towards Zork to kill him." << endl;
				return false;
			}
		}
		else
		{
			if (creatureItem->getName() == "fire")
			{
				cout << " Zork knife is very short, NightDead is a dragon!!!" << endl;
				return false;
			}
			else if (creatureItem->getName() == "blade")
			{
				cout << " Zork knife is very short, the orc's blade is longer..." << endl;
				return false;
			}
			else
			{
				cout << "Zork walks in silence and stab cut creature's neck" << endl;
				return true;
			}
		}
		return false;
	}
	else
	{
		if (action == "throw")
		{
			cout << " Ha? Zorks knows how to throw knifes, but blades..." << endl;
			if (creatureItem->getName() == "fire")
			{
				cout << " NightDead burnt Zork!" << endl;
			}
			else if (creatureItem->getName() == "blade")
			{
				cout << " The orc has killed Zork with a blade." << endl;
			}
			else
			{
				cout << " Orc stabs Zork with a knife." << endl;
			}
			return false;
		}
		else
		{
			cout << " Zork'd use the blade. Zork's a great fighter with Orc's Widow." << endl;
			return true;
		}
	}
}

InputOrder Utils::selectEnum(string s) const
{
	if (s == "go")
		return InputOrder::GO;

	else if (s == "take")
		return InputOrder::TAKE;

	else if (s == "drop")
		return InputOrder::DROP;

	else if (s == "inventory")
		return InputOrder::INVENTORY;

	else if (s == "exit")
		return InputOrder::EXIT;

	else if (s == "watch")
		return InputOrder::WATCH;

	else if (s == "read" || s == "examine")
		return InputOrder::READ;

	else if (s == "open")
		return InputOrder::OPEN;

	else if (s == "close")
		return InputOrder::CLOSE;

	else if (s == "equip")
		return InputOrder::EQUIP;

	else if (s == "unequip")
		return InputOrder::UNEQUIP;

	else if (s == "attack")
		return InputOrder::ATTACK;

	else if (s == "throw")
		return InputOrder::THROW;

	else if (s == "leave")
		return InputOrder::LEAVE;

	else
		return InputOrder::UNKNOWN;
}