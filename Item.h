#pragma once
#include <string>
using namespace std;

class Item
{
private:
	string name;
	string message;

	bool canTakeIt;
	bool canBeOpened;
	bool opened;
	bool needCode;
	string code;

	bool theresAnItemInside;
	Item* itemInside;
	bool insideAnItem;
	Item* outsideItem;

public:
	Item();
	Item(string name, string message, bool canTakeIt);
	Item(string name, string message, bool canTakeIt, bool insideAnItem, Item* outsideItem);
	Item(string name, string message, bool canTakeIt, bool canBeOpened, bool opened, bool theresAnItemInside, Item* itemInside, bool needCode, string code);
	~Item();

	// Asking

	string getName() const;
	bool youCanTakeIt() const;
	bool youCanOpenIt() const;
	bool needCodeToOpen() const;
	Item* getItemInside() const;
	Item* getItemOutside() const;
	string readIt() const;
	string getMessage() const;
	bool haveAnItemInside() const;
	bool isOpened() const;
	bool isInsideAnItem() const;

	// Modifiers

	Item* takeItem();
	Item* takeOutsideItem();
	void putItem(Item* newItemInside);
	void putInsideOfAnItem(Item* newOutSideItem);
	void open();
	void close();

	// Codes

	bool checkCode(string code) const;

};