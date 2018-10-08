#include "World.h"

World::World()
{
}

World::~World()
{
}
void World::Init()
{
	// Player
	player = Player();

	// Creatures
	orc1 = Creature();
	orc2 = Creature();
	dragon = Creature();

	// Rooms
 	dungeon = Room("dungeon", "Zork is going to use the night to scape from this dungeon.");
	corridor = Room("corridor", "You're in a corridor. There are a lot of jails around you and the guard is on the floor drunk. Better run than fight.");
	hall = Room("hall", "Zork is in a stance full of doors and a lot of feetprints. Orcs cross this stance all time.");
	library = Room("library", "Zork is afraid! Zork doesn't like books and I'm surronded of them! HELP!.");
	aboveRoom = Room("hiden room", "Zork is a darkness room above the corridor. There's light up here.");
	dragonCave = Room("dragon's cave", "Zork can see the light throght that door. But first Zork has to kill NightDead.");
	exit = Room("freedome", "Sun is shining, birds singing,... Do you think is a fairytale story? It is f**king cold here! Zork is thinking about coming back to the dungeon and scape later, once this cold rain stops.");

	// Items
	bone = Item("bone", "Zork can useit to smash some orcs' heads", true);
	knife = Item("knife", "Zork can throw me to an enemy but... Zork hasn't practise for long time you can miss the hit.", true);
	blade = Item("blade", "Yeah! Orcs' Widow! The best blade on Earth.", true);
	paper = Item("map", "Isthe map of the caves. It says the exit is at the east. It also says Zork has to cross NightDead chambre in his way.", true);
	vault = Item("vault", "Code (XX-XX-XX) to open the vault. Clue: 01-02-03-05-...", false, true, false, true, &paper, true, "07-11-13");
	key = Item("key", "A rusted old kay. Time ago you where able to read the inscription.", true);
	book = Item("book", "A gnawed old book. It used to have papers but now... Zork only can see a weird lock. Code (X.X.X.). Clue: Tolkien", false, true, false, true, &key, true, "J.R.R.");
	air = Item("air", "This vault has... AIR! Zork'll kill all orcs on the Easth!.", false);
	vault1 = Item("vault", "A small vault, it seams it has something inside. Code (XXXX). Clue: 11-09.", false, true, false, true, &air, true, "1714");
	knifeCreature = Item("knife", "A small knofe to throw.", true);
	bladeCreature = Item("blade", "That blade is quite... Big", true);
	fireCreature = Item("fire", "NightDead can breath and throw fire!", false);

	paper.putInsideOfAnItem(&vault);
	key.putInsideOfAnItem(&book);
	air.putInsideOfAnItem(&vault1);


	// Items in rooms

	dungeon.setDirection("south", "a door", &corridor, true, "");
	corridor.setDirection("north", "a door", &dungeon, true, "");

	corridor.setDirection("south", "a door", &hall, true, "");
	hall.setDirection("north", "a door", &corridor, true, "");

	hall.setDirection("up", "stairs", &aboveRoom, true, "");
	aboveRoom.setDirection("down", "stairs", &hall, true, "");

	hall.setDirection("west", "a door", &dragonCave, true, "");
	dragonCave.setDirection("east", "a door", &hall, true, "");

	hall.setDirection("east", "a door", &library, true, "");
	library.setDirection("west", "a door", &hall, true, "");

	dragonCave.setDirection("west", "a door", &exit, true, "");

	orc1.setItemEquiped(&knifeCreature);
	orc2.setItemEquiped(&bladeCreature);
	dragon.setItemEquiped(&fireCreature);

	dungeon.addItem(&paper);
	dungeon.addItem(&bone);
	dungeon.addItem(&vault);
	aboveRoom.addItem(&blade);
	library.addItem(&book);
	library.addItem(&knife);

	hall.addCreature(&orc1);
	library.addCreature(&orc2);
	dragonCave.addCreature(&dragon);

	// Zork
	player.setActualRoom(&dungeon);

	startingTime = 0;
	creaturePresentInTheRoom = false;

	player.getActualRoom()->readRoom();
}

int World::Iteration(InputOrder io)
{
	string input;

	switch (io)
	{
	case InputOrder::EXIT:
		return 2;
		break;

	case InputOrder::GO:

		cin >> input;
		if (creaturePresentInTheRoom)
		{
			cout << "Zork should first kill the orc!" << endl;
		}
		else if (player.getActualRoom()->goTo(input) != NULL)
		{
			player.setActualRoom(player.getActualRoom()->goTo(input));
			player.getActualRoom()->readRoom();

			if (player.getActualRoom()->getName() == "freedome")
			{
				cout << "If you want to jail Zork again enter: restart" << endl;
				cout << "But if you want to leave Zork seking other adventures enter: end." << endl;
				while (1)
				{
					cin >> input;
					if (input == "restart")
						return 1;
					else if (input == "end")
						return 2;
				}
			}
			if (player.getActualRoom()->isCreaturePresent())
			{
				creaturePresentInTheRoom = true;
				startingTime = clock();
			}
			else
			{
				creaturePresentInTheRoom = false;
			}
		}
		else {
			cout << "Zork would need a hammer to demolish that wall!" << endl;
		}
		break;

	case InputOrder::TAKE:
		cin >> input;
		if (creaturePresentInTheRoom)
		{
			cout << "Zork prefers to kill before the orc" << endl;
		}
		else if (player.getActualRoom()->isItemPresent(input))
		{
			Item* itemYouWantToTake = player.getActualRoom()->getItemByName(input);

			if (itemYouWantToTake->youCanTakeIt())
			{
				if (player.isItemInTheInventory(itemYouWantToTake->getName()))
					cout << "Zork doesn't need it. The bag is quite heavy and Zork already has one.." << endl;
				else
				{
					if (itemYouWantToTake->isInsideAnItem()) {
						itemYouWantToTake->getItemOutside()->takeItem();
						itemYouWantToTake->takeOutsideItem();
					}
					player.getActualRoom()->removeItem(itemYouWantToTake);
					player.addItem(itemYouWantToTake);
					cout << " " << input << " taken" << endl;
				}
			}
			else
			{
				cout << "Zork is not enough strong form that." << endl;
			}
		}
		else
		{
			cout << "Yeah! You must be kiding Zork! Zork cannot see that." << endl;
		}
		break;

	case InputOrder::DROP:
		cin >> input;
		if (creaturePresentInTheRoom)
		{
			cout << "Zork prefers to kill he orc first." << endl;
		}
		else if ((player.isItemInTheInventory(input) && player.getItemEquiped() == NULL) ||
			(player.isItemInTheInventory(input) && player.getItemEquiped()->getName() != input))
		{
			Item* itemYouWantToTake = player.getItemByName(input);

			player.removeItem(itemYouWantToTake);
			player.getActualRoom()->addItem(itemYouWantToTake);
			cout << " " << input << " droped" << endl;
		}
		else if (player.getItemEquiped() == NULL || player.getItemEquiped()->getName() != input)
		{
			cout << "Zork cannot find that in the bag." << endl;
		}
		else
		{
			cout << "Eh! Zork needs it!." << endl;
		}
		break;

	case InputOrder::INVENTORY:
		player.readInventory();
		cout << endl;
		break;

	case InputOrder::WATCH:
		player.getActualRoom()->readRoom();
		break;

	case InputOrder::READ:
		cin >> input;
		player.readItem(input);
		cout << endl;
		break;

	case InputOrder::OPEN:
		cin >> input;
		if (creaturePresentInTheRoom)
		{
			cout << "Zork prefers to kill first the orc." << endl;
		}
		else if (player.getActualRoom()->isItemPresent(input))
		{
			Item* itemYouWantToOpen = player.getActualRoom()->getItemByName(input);

			if (itemYouWantToOpen->isOpened())
			{
				cout << "Do you know is already opened? Don't make Zork to work twice." << endl;
			}
			else
			{
				bool opened = false;
				if (itemYouWantToOpen->needCodeToOpen())
				{
					cout << itemYouWantToOpen->getMessage() << endl;
					string codeByUser;
					cin >> codeByUser;
					if (itemYouWantToOpen->checkCode(codeByUser))
					{
						opened = true;
					}
				}
				else
				{
					opened = true;
				}
				if (opened)
				{
					itemYouWantToOpen->open();
					if (itemYouWantToOpen->haveAnItemInside())
					{
						player.getActualRoom()->addItem(itemYouWantToOpen->getItemInside());
						cout << " " << input << " opened. Inside Zork has found " << itemYouWantToOpen->getItemInside()->getName() << "." << endl;
					}
					else
					{
						cout << " " << input << " opened. Zork has found... AIR!." << endl;
					}
				}
				else {
					cout << "Zork has to think more about this code..." << endl;
				}
			}
		}
		else
		{
			cout << "Zork cannot open here, there're to much eyes around Zork." << endl;
		}
		cout << endl;
		break;

	case InputOrder::CLOSE:
		cin >> input;
		if (creaturePresentInTheRoom)
		{
			cout << "Zorc preferst to kill the orc first." << endl;
		}
		else if (player.getActualRoom()->isItemPresent(input))
		{
			Item* itemYouWantToClose = player.getActualRoom()->getItemByName(input);

			if (!itemYouWantToClose->youCanOpenIt())
				cout << "Zork cannot do hat with his." << endl;
			else if (!itemYouWantToClose->isOpened())
				cout << "It's closed! Why do you want to make Zork to work twice?" << endl;
			else
			{
				if (itemYouWantToClose->haveAnItemInside())
				{
					player.getActualRoom()->removeItem(itemYouWantToClose->getItemInside());
				}
				itemYouWantToClose->close();
				cout << " " << itemYouWantToClose->getName() << " closed." << endl;
			}
		}
		else
			cout << "That is not here! Zork cannot imagine how to close if it isn't here..." << endl;
		cout << endl;
		break;

	case InputOrder::EQUIP:
		cin >> input;
		player.equipItem(input);
		cout << endl;
		break;

	case InputOrder::UNEQUIP:
		player.unequipItem();
		cout << endl;
		break;

	case InputOrder::ATTACK:
		if (creaturePresentInTheRoom)
		{
			if (utils.playerWinsOrLoses("attack", player.getItemEquiped(), player.getActualRoom()->getCreature()->getItemEquiped(), clock() - startingTime)) {
				Item* dropItem = player.getActualRoom()->getCreature()->getItemEquiped();
				creaturePresentInTheRoom = false;
				player.getActualRoom()->creatureDies();
				cout << "Yeah! Zork has killed him. Give me time to score a point in my arm." << endl;
				cout << "Counting Zork's scars you can know the number of orcs killed by Zork. Now is 1, 2, 3, 4, 5,.. a lot!" << endl;
				cout << "Zork can only count till 5." << endl;
				cout << "This orc had a " << dropItem->getName() << "." << endl;
			}
			else
			{
				cout << "Zork can feel how the blood is flooding the ground..." << endl;
				cout << "Zork has passed away. If you want him to rebirth as a Fenix, enter: restart." << endl;
				cout << "If you want Zork buried (zombies are stinky), enter: end." << endl;
				while (1)
				{
					cin >> input;
					if (input == "restart")
						return 1;
					else if (input == "end")
						return 2;
				}
			}
		}
		else
		{
			cout << "Zork wants to kill all orcs, but.. there is no orcs here..." << endl;
		}
		cout << endl;
		break;

	case InputOrder::THROW:
		if (creaturePresentInTheRoom)
		{
			if (utils.playerWinsOrLoses("throw", player.getItemEquiped(), player.getActualRoom()->getCreature()->getItemEquiped(), clock() - startingTime)) {
				Item* dropItem = player.getActualRoom()->getCreature()->getItemEquiped();
				creaturePresentInTheRoom = false;
				player.getActualRoom()->creatureDies();
				cout << "Yeah! One orc less" << endl;
				cout << "This orc had a " << dropItem->getName() << "." << endl;
			}
			else
			{
				cout << "Zork can feell his blood flodding the ground..." << endl;
				cout << "If Zork has to reborn enter: restart." << endl;
				cout << "If the dead tings must be buried... enter: end." << endl;
				while (1)
				{
					cin >> input;
					if (input == "restart")
						return 1;
					else if (input == "end")
						return 2;
				}
			}
		}
		else
		{
			cout << "Zork loves killing orcs, but... Zork cannot find an orc here." << endl;
		}
		cout << endl;
		break;

	case InputOrder::LEAVE:
		cin >> input;
		if (creaturePresentInTheRoom)
		{
			cin >> input; cin >> input;
			cout << "Zork prefers to kill the orch before." << endl;
		}
		else if ((player.isItemInTheInventory(input) && player.getItemEquiped() == NULL) ||
			(player.isItemInTheInventory(input) && player.getItemEquiped()->getName() != input))
		{
			Item* itemToLeave = player.getItemByName(input);
			cin >> input;
			if (input == "inside")
			{
				cin >> input;
				Item* itemWhereLeave = player.getActualRoom()->getItemByName(input);

				if (!itemWhereLeave->youCanOpenIt())
					cout << "Ha? Is that possible? You can not leave that inside " << itemWhereLeave->getName() << endl;
				else if (!itemWhereLeave->isOpened())
					cout << " " << itemWhereLeave->getName() << " is closed." << endl;
				else if (itemWhereLeave->haveAnItemInside())
					cout << " " << itemWhereLeave->getName() << " is full." << endl;
				else
				{
					itemToLeave->putInsideOfAnItem(itemWhereLeave);
					itemWhereLeave->putItem(itemToLeave);
					player.getActualRoom()->addItem(itemToLeave);
					player.removeItem(itemToLeave);
					cout << "Zork has putted " << itemToLeave->getName() << " inside " << itemWhereLeave->getName() << endl;
				}
			}
		}
		else if (player.getItemEquiped() == NULL || player.getItemEquiped()->getName() != input)
		{
			cin >> input; cin >> input;
			cout << "Zork cannot find that thing in the bag." << endl;
		}
		else
		{
			cin >> input; cin >> input;
			cout << "Eh! Zork needs it!" << endl;
		}
		cout << endl;
		break;

	default:
		cin >> input;
		cout << "Zork cannot undersand you... Zork will have to study your lenguage." << endl;
		cout << endl;
		break;

	}

	return 0;
}