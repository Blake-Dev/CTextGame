#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Items.h"

class Inventory
{
public:
	Inventory();

	void AddItem(Item * i);
	void DeleteItem();
	void ShowAllItems();
	void EquipShowItems();
	int ReturnSize();

	std::vector<Item*> m_inventory;
};