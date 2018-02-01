#include "stdafx.h"
#include "Inventory.h"
#include <stdio.h>

Inventory::Inventory() {}

//Using pointer
void Inventory::AddItem(Item * i)
{
	m_inventory.push_back(i);
}

void Inventory::DeleteItem()
{
	int size = static_cast<int>(m_inventory.size());
	int choice;

	std::cout << "Select an item to delete: " << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << i << ": " << m_inventory[i]->ReturnName() << std::endl;
	}

	std::cin >> choice;
	std::cout << "The " << m_inventory[choice]->ReturnName() << " has been deleted from your inventory." << std::endl;
	m_inventory.erase(m_inventory.begin() + choice);
}

void Inventory::ShowAllItems()
{
	if (m_inventory.size() <= 0)
		std::cout << "There are currently no items in your inventory!" << std::endl;
	else
	{
		for (unsigned int i = 0; i < m_inventory.size(); i++)
		{
			if (m_inventory[i]->item_type == "Consumable")
			{
				printf("\nName: %s\nDescription: %s\nValue: %d\nEffect: %f\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->ReturnDesc().c_str(), m_inventory[i]->ReturnValue(), m_inventory[i]->ReturnStat());
			}
			else if (m_inventory[i]->item_type == "Weapon")
			{
				printf("\nName: %s\nType: %s\nDescription: %s\nValue: %d\nDamage: %f\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->item_type.c_str(), m_inventory[i]->ReturnDesc().c_str(), m_inventory[i]->ReturnValue(), m_inventory[i]->ReturnStat());
			}
			else if (m_inventory[i]->item_type == "Armor")
			{
				printf("\nName: %s\nType: %s\nDescription: %s\nValue: %d\nDefense: %f\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->item_type.c_str(), m_inventory[i]->ReturnDesc().c_str(), m_inventory[i]->ReturnValue(), m_inventory[i]->ReturnStat());
			}
			else
			{
				printf("\nName: %s\nDescription: %s\nValue: %d\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->ReturnDesc().c_str(), m_inventory[i]->ReturnValue());
			}
		}
	}
}

void Inventory::ShowAllItemsClean()
{
	if (m_inventory.size() <= 0)
		std::cout << "There are currently no items in your inventory!" << std::endl;
	else
	{
		for (unsigned int i = 0; i < m_inventory.size(); i++)
		{
			if (m_inventory[i]->item_type == "Consumable")
			{
				printf("%s +%.2f <FX>\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->ReturnStat());
			}
			else if (m_inventory[i]->item_type == "Weapon")
			{
				printf("%s +%.2f <ATK>\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->ReturnStat());
			}
			else if (m_inventory[i]->item_type == "Armor")
			{
				printf("%s +%.2f <DEF>\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->ReturnStat());
			}
			else
			{
				printf("%s <VAL> %d\n", m_inventory[i]->ReturnName().c_str(), m_inventory[i]->ReturnValue());
			}
			if(i < m_inventory.size() - 1)
				std::cout << "//" << std::endl;
		}
	}
}

void Inventory::EquipShowItems()
{
	if (m_inventory.size() <= 0)
		std::cout << "There are currently no items in your inventory!" << std::endl;
	else
	{
		for (unsigned int i = 0; i < m_inventory.size(); i++)
		{
			std::cout << i << ". " << m_inventory[i]->ReturnName() << std::endl;
			if(i < m_inventory.size() - 1)
				std::cout << "//" << std::endl;
			//std::cout << "Stat - " << m_inventory[i]->ReturnStat() << " | Val " << m_inventory[i]->ReturnValue() << std::endl;
		}
	}
}

int Inventory::ReturnSize()
{
	return static_cast<int>(m_inventory.size());
}