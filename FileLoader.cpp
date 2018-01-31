#include "stdafx.h"
#include "FileLoader.h"

FileLoader::FileLoader() {}

std::vector<Item*> FileLoader::LoadPlayerItems()
{
	struct LoadItem
	{
		int ID;
		bool equipped;
	};

	if (std::ifstream("PlayerInventory.txt"))
	{

		std::ifstream itemDefIn("ItemDefs.txt");
		std::ifstream invSave("PlayerInventory.txt");

		std::string invID, invEquipped, ID, typeID, name, desc, value, stat, armorSlot;
		std::vector<LoadItem> playerInv;
		//Read player inventory file
		while (std::getline(invSave, invID, ','))
		{
			std::getline(invSave, invEquipped);
			LoadItem item;
			item.ID = std::stoi(invID);
			item.equipped = std::stoi(invEquipped);
			playerInv.push_back(item);
		}

		while (std::getline(itemDefIn, ID, ','))
		{
			std::getline(itemDefIn, typeID, ',');
			std::getline(itemDefIn, name, ',');
			std::getline(itemDefIn, desc, ',');
			std::getline(itemDefIn, stat, ',');
			std::getline(itemDefIn, value, ',');
			std::getline(itemDefIn, armorSlot);

			for (int i = 0; i < playerInv.size(); i++)
			{
				//Debug to show what's being compared
				/*std::cout << "PlayerInv.txt: " << playerInv[i] << std::endl;
				std::cout << "ItemDefs.txt: " << ID << std::endl << std::endl;*/
				if (playerInv[i].ID == std::stoi(ID))
				{
					switch (std::stoi(typeID))
					{
					case 0:
					{
						Item *armor = new Armor(std::stoi(ID), name, desc, std::stod(stat), std::stoi(value));
						armor->SetEquippedSlot(std::stoi(armorSlot));
						armor->SetEquipped(playerInv[i].equipped);
						m_items.push_back(armor);
					}
					break;
					case 1:
					{
						Item *weapon = new Weapon(std::stoi(ID), name, desc, std::stod(stat), std::stoi(value));
						weapon->SetEquippedSlot(std::stoi(armorSlot));
						weapon->SetEquipped(playerInv[i].equipped);
						m_items.push_back(weapon);
					}
					break;
					default:
						break;
					}
				}
			}
		}
	}

	if (m_items.size() <= 0)
	{
		std::cout << "File: FileLoader.cpp, LoadPlayerItems()" << std::endl;
		Item *weapon = new Weapon(999, "Debug", "You should'nt be seeing this", 20.0, 10);
		m_items.push_back(weapon);
		return m_items;
	}
	return m_items;
}

Entity* FileLoader::LoadSave()
{
	if (std::fstream("PlayerSave.txt"))
	{
		std::cout << "Save File Detected..." << std::endl;

		std::ifstream infile("PlayerSave.txt");
		std::ifstream heroDef("HeroDef.txt");
		std::string ID, name, heroType, health, maxh, attack, maxa, magic, maxmag, mana, maxmana, IDCheck;

		if (!infile)
			std::cout << "Error loading file" << std::endl;
		else
		{
			while (std::getline(infile, ID, ','))
			{
				std::getline(infile, name);
			}
		}

		if (!heroDef)
			std::cout << "Error loading HeroDef.txt!" << std::endl;
		else
		{
			while (std::getline(heroDef, IDCheck, ','))
			{
				std::getline(heroDef, heroType, ',');
				std::getline(heroDef, health, ',');
				std::getline(heroDef, maxh, ',');
				std::getline(heroDef, attack, ',');
				std::getline(heroDef, maxa, ',');
				std::getline(heroDef, magic, ',');
				std::getline(heroDef, maxmag, ',');
				std::getline(heroDef, mana, ',');
				std::getline(heroDef, maxmana);

				if (std::stoi(ID) == std::stoi(IDCheck))
				{
					switch (std::stoi(ID))
					{
					case HeroKey::Warrior:
					{
						Entity * Hero = new Warrior(name, std::stod(health), std::stod(maxh), std::stod(attack), std::stod(maxa), std::stod(magic), std::stod(maxmag), std::stod(mana), std::stod(maxmana));
						Hero->SetID(HeroKey::Warrior);
						m_ent.push_back(Hero);
					}
						break;
					case HeroKey::Rogue:
					{
						Entity * Hero = new Rogue(name, std::stod(health), std::stod(maxh), std::stod(attack), std::stod(maxa), std::stod(magic), std::stod(maxmag), std::stod(mana), std::stod(maxmana));
						Hero->SetID(HeroKey::Rogue);
						m_ent.push_back(Hero);
					}
						break;
					case HeroKey::Wizard:
					{
						Entity * Hero = new Wizard(name, std::stod(health), std::stod(maxh), std::stod(attack), std::stod(maxa), std::stod(magic), std::stod(maxmag), std::stod(mana), std::stod(maxmana));
						Hero->SetID(HeroKey::Wizard);
						m_ent.push_back(Hero);
					}
						break;
					default:
						break;
					}
				}

			}
		}
	}
	else
	{
		m_ent.push_back(CreateSave());
	}
	//std::cout << m_ent[0]->ReturnName();
	return m_ent[0];
}

Item* FileLoader::CreateObject(int id)
{
	Item *item[1];

	if (std::ifstream("ItemDefs.txt"))
	{
		std::ifstream itemDef("itemDefs.txt");

		std::string ID, typeID, name, desc, value, stat, armorSlot;

		while (std::getline(itemDef, ID, ','))
		{
			std::getline(itemDef, typeID, ',');
			std::getline(itemDef, name, ',');
			std::getline(itemDef, desc, ',');
			std::getline(itemDef, stat, ',');
			std::getline(itemDef, value, ',');
			std::getline(itemDef, armorSlot);

			if (id == std::stoi(ID))
			{
				switch (std::stoi(typeID))
				{
				case 0:
				{
					Item *armor = new Armor(std::stoi(ID), name, desc, std::stod(stat), std::stoi(value));
					armor->SetEquippedSlot(std::stoi(armorSlot));
					armor->SetEquipped(false);
					item[0] = armor;
				}
				break;
				case 1:
				{
					Item *weapon = new Weapon(std::stoi(ID), name, desc, std::stod(stat), std::stoi(value));
					weapon->SetEquippedSlot(std::stoi(armorSlot));
					weapon->SetEquipped(false);
					item[0] = weapon;
				}
				break;
				default:
					break;
				}
			}
		}
	}
	return item[0];
}

Location FileLoader::LoadLocation(int id)
{
	Location l;

	if (std::ifstream("Locations.txt"))
	{
		std::ifstream loc("Locations.txt");

		std::string ID, name, desc;

		while (std::getline(loc, ID, ','))
		{
			std::getline(loc, name, ',');
			std::getline(loc, desc);

			if (id == std::stoi(ID))
			{
				l.ID = id;
				l.name = name;
				l.description = desc;
			}
		}
	}
	return l;
}

Enemy FileLoader::CreateEnemy(int id)
{
	if (std::ifstream("EnemyDef.txt"))
	{
		std::ifstream enemyDef("EnemyDef.txt");

		std::string ID, name, minH, minA;

		while (std::getline(enemyDef, ID, ','))
		{
			std::getline(enemyDef, name, ',');
			std::getline(enemyDef, minH, ',');
			std::getline(enemyDef, minA);

			if (id == std::stoi(ID))
			{
				Enemy e;
				e.name = name;
				e.attack = std::stod(minA);
				e.health = std::stod(minH);

				return e;
			}
		}
	}
	else
	{
		Enemy e;
		e.attack = 5.0;
		e.health = 5.0;
		e.name = "Monster";

		return e;
	}
}

Entity* FileLoader::CreateSave()
{
	std::ofstream outfile;
	std::string name;

	std::cout << "Creating new save now..." << std::endl;
	std::cout << "What is your name?" << std::endl << "> ";

	std::cin >> name;

	system("cls");

	outfile.open("PlayerSave.txt");

	std::cout << "Alright, " << name << ", what are you?" << std::endl;
	std::cout << "1 - Warrior: Ferocious, brute, and unyielding." << std::endl;
	std::cout << "2 - Rogue: Crafty, cunning, and witty." << std::endl;
	std::cout << "3 - Wizard: Intelligent, all-knowing, and good and stuff." << std::endl;

	HeroIndex index;
	HeroIndex saveIndex;
	std::cin >> index;

	switch (index)
	{
	case HeroKey::Warrior:
	{
		Entity *hero = new Warrior(name, 10.0, 10.0, 12.0, 12.0, 3.0, 3.0, 3.0, 3.0);
		m_ent.push_back(hero);
		saveIndex = HeroKey::Warrior;
	}
	break;

	case HeroKey::Rogue:
	{
		Entity *hero = new Rogue(name, 9.0, 9.0, 8.0, 8.0, 6.0, 6.0, 7.0, 7.0);
		m_ent.push_back(hero);
		saveIndex = HeroKey::Rogue;
	}
	break;

	case HeroKey::Wizard:
	{
		Entity *hero = new Wizard(name, 9.0, 9.0, 5.0, 5.0, 13.0, 13.0, 12.0, 12.0);
		m_ent.push_back(hero);
		saveIndex = HeroKey::Wizard;
	}
	break;
	default:
		break;
	}

	outfile << saveIndex << ',' << name;

	std::cout << "File written to." << std::endl;

	m_ent[0]->inventory.AddItem(CreateObject(100));
	m_ent[0]->inventory.AddItem(CreateObject(200));

	//m_ent[0]->inventory.ShowAllItems();

	return m_ent[0];
}