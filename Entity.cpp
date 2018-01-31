#include "stdafx.h"
#include "Entity.h"

Entity::Entity(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman)
	:name(n)
	, health(h)
	, max_health(mh)
	, attack(a)
	, max_attack(ma)
	, magic(m)
	, max_magic(mm)
	, mana(man)
	, max_mana(maxman)
{ }

void Entity::SetID(int i)
{
	ID = i;
}

std::string Entity::ReturnName()
{
	return name;
}

std::string Entity::ReturnClass()
{
	return classType;
}

int Entity::ReturnState()
{
	return state;
}

int Entity::ReturnLocation()
{
	return location;
}

double Entity::ReturnHealth()
{
	return health;
}

double Entity::ReturnMaxHealth()
{
	return max_health;
}

double Entity::ReturnAttack()
{
	return attack;
}

double Entity::ReturnMaxAttack()
{
	return max_attack;
}

double Entity::ReturnMagic()
{
	return magic;
}

double Entity::ReturnMaxMagic()
{
	return max_magic;
}

double Entity::ReturnMana()
{
	return mana;
}

double Entity::ReturnMaxMana()
{
	return max_mana;
}

void Entity::RechargeMana()
{
	mana = mana + (0.20 * max_mana);

	if (mana > max_mana)
	{
		mana = max_mana;
	}
}

void Entity::Heal()
{
	if ((mana > 4.0) && (health < max_health))
	{
		health = health + (0.15 * max_health);

		if (health > max_health)
		{
			health = max_health;
		}
	}
}

void Entity::TakeDamage(double d)
{
	double damageToTake = d - (d * (defense * 0.1));
	health -=  damageToTake;
}

void Entity::SetDefense(double d)
{
	defense = d;
}

double Entity::ReturnDefense()
{
	return defense;
}

void Entity::SetState(int p_state)
{
	state = p_state;
}

void Entity::SetLocation(int p_location)
{
	location = p_location;
}

void Entity::Travel()
{
	UIManager ui;
	int choice;

	if (location == Locations::Home)
	{
		ui.OutputText("Travel // Location - Home");
		ui.OutputText("=========================");
		ui.OutputText("1 - Small Dungeon");
		ui.OutputText("2 - Large Dungeon");
		ui.OutputText("3 - Abyss");
		ui.OutputText("4 - Stay Put");

		std::cout << "> ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			ui.OutputText("You make the trek to the Small Dungeon.");
			location = Locations::SmallDungeon;
			SetDungeonLevel(0);
			break;
		case 2:
			ui.OutputText("You make the trek to the Large Dungeon.");
			location = Locations::LargeDungeon;
			SetDungeonLevel(0);
			break;
		case 3:
			ui.OutputText("You make the trek to the Abyss...");
			location = Locations::Abyss;
			SetDungeonLevel(0);
			break;
		case 4:
			ui.OutputText("You decide to stay home. You'll be ready soon enough");
			location = Locations::Home;
			break;
		default:
			ui.OutputText("Incorrect input.");
			break;
		}
	}
	else
	{
		std::cout << "Travel // Location - Level " << ReturnDungeonLevel() << std::endl;
		ui.OutputText("=============================");
		ui.OutputText("Advance to next room?\n\n1 - Yes\n2 - No");
		std::cout << "> ";
		std::cin >> choice;
		if (choice == 1)
		{
			ui.OutputText("You press forward...");
			IncrementDungeonLevel();

			if (ReturnDungeonLevel() >= 10)
			{
				state == States::Idle;
				location = Locations::Home;
				ui.OutputText("You clear the dungeon triumphantly!");
			}

			state = States::Battle;
		}
		else
		{
			ui.OutputText("You stay and collect yourself.");
			state = States::Idle;
		}
	}	
}

void Entity::ResetStats()
{
	UIManager ui;

	health = max_health;
	attack = max_attack;
	magic = max_magic;
	mana = max_mana;

	ui.OutputText("You lie down and rest for a bit...");
	ui.OutputText("Strength returns to you.");
}

void Entity::ReturnHome()
{
	UIManager ui;
	int choice;

	ui.OutputText("The journey has proved to be too difficult...");
	ui.OutputText("Return home without any spoils? 1 - Yes | 2 - No");
	std::cout << "> ";
	std::cin >> choice;

	if (choice == 1)
	{
		ui.OutputText("You begin the journey back home. You fought the best you could...");
		location = Locations::Home;
	}
	else
		ui.OutputText("Let them come.");
}

void Entity::IncrementDungeonLevel()
{
	currentDungeonLevel++;
	if (currentDungeonLevel > 10)
		currentDungeonLevel = 10;
}
void Entity::SetDungeonLevel(int lvl)
{
	currentDungeonLevel = lvl;
}
int Entity::ReturnDungeonLevel()
{
	return currentDungeonLevel;
}

void Entity::AddGold(int g)
{
	gold += g;
}

void Entity::RemoveGold(int g)
{
	gold -= g;
	
	if (gold < 0)
		gold = 0;
}

int Entity::ReturnGold()
{
	return gold;
}

void Entity::PrintStats()
{
	std::cout << ' ' << ReturnName() << " // " << ReturnClass() << std::endl;
	std::cout << std::setfill('=') << std::setw(18) << '=' << std::setfill(' ') << std::endl;

	std::cout << std::left << std::setw(1) << "HP: " << ReturnHealth() << "/" << ReturnMaxHealth() << std::setw(2) << ' ';
	std::cout << std::left << std::setw(1) << "MP: " << ReturnMana() << "/" << ReturnMaxMana() << std::endl;

	std::cout << std::left << std::setw(1) << "ATK: " << std::setw(4) << ReturnAttack() << std::setw(2) << ' ';
	std::cout << std::left << std::setw(1) << "DEF: " << ReturnDefense() << std::endl;

	std::cout << std::left << "Gold: " << ReturnGold() << std::endl;

	std::cout << std::setfill('=') << std::setw(18) << '=' << std::setfill(' ') << std::endl;
}

void Entity::EquippedItemInfo(int id)
{
	switch (id)
	{
	case ArmorID::NotArmor:
		if(currentlyEquipped[ArmorID::NotArmor] != NULL)
			std::cout << std::left << std::setw(8) << "Weapon: " << "+" << currentlyEquipped[ArmorID::NotArmor]->ReturnStat() << " " << currentlyEquipped[ArmorID::NotArmor]->ReturnName() << std::endl;
		else
			std::cout << std::left << std::setw(7) << "Weapon:" << std::setw(1) << ' ' << "-empty-" << std::endl;
		break;
	case ArmorID::Head:
		if (currentlyEquipped[ArmorID::Head] != NULL)
			std::cout << std::left << std::setw(8) << "Helm: " << "+" << currentlyEquipped[ArmorID::Head]->ReturnStat() << " " << currentlyEquipped[ArmorID::Head]->ReturnName() << std::endl;
		else
			std::cout << std::left << std::setw(7) << "Helm:" << std::setw(1) << ' ' << "-empty-" << std::endl;
		break;
	case ArmorID::Arms:
		if (currentlyEquipped[ArmorID::Arms] != NULL)
			std::cout << std::left << std::setw(8) << "Arms: " << "+" << currentlyEquipped[ArmorID::Arms]->ReturnStat() << " " << currentlyEquipped[ArmorID::Arms]->ReturnName() << std::endl;
		else
			std::cout << std::left << std::setw(7) << "Arms:" << std::setw(1) << ' ' << "-empty-" << std::endl;
		break;
	case ArmorID::Chest:
		if (currentlyEquipped[ArmorID::Chest] != NULL)
			std::cout << std::left << std::setw(8) << "Chest: " << "+" << currentlyEquipped[ArmorID::Chest]->ReturnStat() << " " << currentlyEquipped[ArmorID::Chest]->ReturnName() << std::endl;
		else
			std::cout << std::left << std::setw(7) << "Chest:" << std::setw(1) << ' ' << "-empty-" << std::endl;
		break;
	case ArmorID::Legs:
		if (currentlyEquipped[ArmorID::Legs] != NULL)
			std::cout << std::left << std::setw(8) << "Legs: " << "+" << currentlyEquipped[ArmorID::Legs]->ReturnStat() << " " << currentlyEquipped[ArmorID::Legs]->ReturnName() << std::endl;
		else
			std::cout << std::left << std::setw(7) << "Legs:" << std::setw(1) << ' ' << "-empty-" << std::endl;
		break;
	case ArmorID::Shield:
		if (currentlyEquipped[ArmorID::Shield] != NULL)
			std::cout << std::left << std::setw(8) << "Shield: " << "+" << currentlyEquipped[ArmorID::Shield]->ReturnStat() << " " << currentlyEquipped[ArmorID::Shield]->ReturnName() << std::endl;
		else
			std::cout << std::left << std::setw(7) << "Shield:" << std::setw(1) << ' ' << "-empty-" << std::endl;
		break;
	default:
		std::cout << "Debug" << std::endl;
		break;
	}
}

void Entity::PrintEquipped()
{
	std::cout << " Equipped" << std::endl;
	std::cout << std::setfill('=') << std::setw(18) << '=' << std::setfill(' ') << std::endl;
	EquippedItemInfo(ArmorID::NotArmor);
	EquippedItemInfo(ArmorID::Head);
	EquippedItemInfo(ArmorID::Arms);
	EquippedItemInfo(ArmorID::Chest);
	EquippedItemInfo(ArmorID::Legs);
	EquippedItemInfo(ArmorID::Shield);
}

void Entity::Equip()
{
	int choice;
	int armorSlot;
	bool exitEquip = false;

	while (!exitEquip)
	{
		std::cout << "-1 to exit" << std::endl;
		inventory.EquipShowItems();
		std::cin >> choice;

		if (choice == -1)
		{
			exitEquip = true;
			std::cout << "Exiting now..." << std::endl;
			break;
		}
		if ((choice < inventory.m_inventory.size()) && (choice > -1))
		{

			armorSlot = inventory.m_inventory[choice]->ReturnEquippedSlot();
			//std::cout << "armorSlot: " << armorSlot << std::endl;

			switch (armorSlot)
			{
			case ArmorID::NotArmor:
				if (currentlyEquipped[ArmorID::NotArmor] == NULL)
				{
					currentlyEquipped[ArmorID::NotArmor] = inventory.m_inventory[choice];

					attack += currentlyEquipped[ArmorID::NotArmor]->ReturnStat();

					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);
					std::cout << currentlyEquipped[ArmorID::NotArmor]->ReturnName() << " has been equipped." << std::endl;
				}
				else
				{
					std::cout << currentlyEquipped[ArmorID::NotArmor]->ReturnName() << " has been unequipped." << std::endl;
					attack -= currentlyEquipped[ArmorID::NotArmor]->ReturnStat();
					inventory.m_inventory.push_back(currentlyEquipped[ArmorID::NotArmor]);
					currentlyEquipped[ArmorID::NotArmor] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);
					//Add and subtract stat values from player

					attack += currentlyEquipped[ArmorID::NotArmor]->ReturnStat();
					std::cout << currentlyEquipped[ArmorID::NotArmor]->ReturnName() << " has been equipped." << std::endl;
				}
				break;
			case ArmorID::Head:
				if (currentlyEquipped[ArmorID::Head] == NULL)
				{
					currentlyEquipped[ArmorID::Head] = inventory.m_inventory[choice];

					defense += currentlyEquipped[ArmorID::Head]->ReturnStat();;

					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);
					std::cout << currentlyEquipped[ArmorID::Head]->ReturnName() << " has been equipped." << std::endl;
				}
				else
				{
					std::cout << currentlyEquipped[ArmorID::Head]->ReturnName() << " has been unequipped." << std::endl;
					defense -= currentlyEquipped[ArmorID::Head]->ReturnStat();
					inventory.m_inventory.push_back(currentlyEquipped[ArmorID::Head]);
					currentlyEquipped[ArmorID::Head] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Head]->ReturnStat();
					std::cout << currentlyEquipped[ArmorID::Head]->ReturnName() << " has been equipped." << std::endl;
				}
				break;
			case ArmorID::Arms:
				if (currentlyEquipped[ArmorID::Arms] == NULL)
				{
					currentlyEquipped[ArmorID::Arms] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Arms]->ReturnStat();

					std::cout << currentlyEquipped[ArmorID::Arms]->ReturnName() << " has been equipped." << std::endl;
				}
				else
				{
					std::cout << currentlyEquipped[ArmorID::Arms]->ReturnName() << " has been unequipped." << std::endl;
					defense -= currentlyEquipped[ArmorID::Arms]->ReturnStat();
					inventory.m_inventory.push_back(currentlyEquipped[ArmorID::Arms]);
					currentlyEquipped[ArmorID::Arms] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Arms]->ReturnStat();
					std::cout << currentlyEquipped[ArmorID::Arms]->ReturnName() << " has been equipped." << std::endl;
				}
				break;
			case ArmorID::Chest:
				if (currentlyEquipped[ArmorID::Chest] == NULL)
				{
					currentlyEquipped[ArmorID::Chest] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Chest]->ReturnStat();

					std::cout << currentlyEquipped[ArmorID::Chest]->ReturnName() << " has been equipped." << std::endl;
				}
				else
				{
					std::cout << currentlyEquipped[ArmorID::Chest]->ReturnName() << " has been unequipped." << std::endl;
					defense -= currentlyEquipped[ArmorID::Chest]->ReturnStat();
					inventory.m_inventory.push_back(currentlyEquipped[ArmorID::Chest]);
					currentlyEquipped[ArmorID::Chest] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Chest]->ReturnStat();
					std::cout << currentlyEquipped[ArmorID::Chest]->ReturnName() << " has been equipped." << std::endl;
				}
				break;
			case ArmorID::Legs:
				if (currentlyEquipped[ArmorID::Legs] == NULL)
				{
					currentlyEquipped[ArmorID::Legs] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Legs]->ReturnStat();

					std::cout << currentlyEquipped[ArmorID::Legs]->ReturnName() << " has been equipped." << std::endl;
				}
				else
				{
					std::cout << currentlyEquipped[ArmorID::Legs]->ReturnName() << " has been unequipped." << std::endl;
					defense -= currentlyEquipped[ArmorID::Legs]->ReturnStat();
					inventory.m_inventory.push_back(currentlyEquipped[ArmorID::Legs]);
					currentlyEquipped[ArmorID::Legs] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Legs]->ReturnStat();
					std::cout << currentlyEquipped[ArmorID::Legs]->ReturnName() << " has been equipped." << std::endl;
				}
				break;
			case ArmorID::Shield:
				if (currentlyEquipped[ArmorID::Shield] == NULL)
				{
					currentlyEquipped[ArmorID::Shield] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Shield]->ReturnStat();

					std::cout << currentlyEquipped[ArmorID::Shield]->ReturnName() << " has been equipped." << std::endl;
				}
				else
				{
					std::cout << currentlyEquipped[ArmorID::Shield]->ReturnName() << " has been unequipped." << std::endl;
					defense -= currentlyEquipped[ArmorID::Shield]->ReturnStat();
					inventory.m_inventory.push_back(currentlyEquipped[ArmorID::Shield]);
					currentlyEquipped[ArmorID::Shield] = inventory.m_inventory[choice];
					inventory.m_inventory.erase(inventory.m_inventory.begin() + choice);

					defense += currentlyEquipped[ArmorID::Shield]->ReturnStat();
					std::cout << currentlyEquipped[ArmorID::Shield]->ReturnName() << " has been equipped." << std::endl;
				}
				break;
			default:
				std::cout << "Whoopsies" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "You did not choose a valid value." << std::endl;
		}
	}
}

Warrior::Warrior(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman) : Entity(n, h, mh, a, ma, m, mm, man, maxman)
{
	name = n;
	health = h;
	max_health = mh;
	attack = a;
	max_attack = ma;
	magic = m;
	max_magic = mm;
	mana = man;
	max_mana = maxman;
	classType = "Warrior";
}

Rogue::Rogue(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman) : Entity(n, h, mh, a, ma, m, mm, man, maxman)
{
	name = n;
	health = h;
	max_health = mh;
	attack = a;
	max_attack = ma;
	magic = m;
	max_magic = mm;
	mana = man;
	max_mana = maxman;
	classType = "Rogue";
}

Wizard::Wizard(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman) : Entity(n, h, mh, a, ma, m, mm, man, maxman)
{
	name = n;
	health = h;
	max_health = mh;
	attack = a;
	max_attack = ma;
	magic = m;
	max_magic = mm;
	mana = man;
	max_mana = maxman;
	classType = "Wizard";
}