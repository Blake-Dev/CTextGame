#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	playing = true;
}

void Game::LoadSave()
{
	FileLoader file;

	m_ent.push_back(file.LoadSave());
	m_ent[0]->inventory.m_inventory = file.LoadPlayerItems();
	SetLocation();

	std::cout << "Player loaded..." << std::endl << std::endl;

	m_ent[0]->PrintStats();

	//Item * i = new Weapon(100, "Wooden Sword", "A splintering wood sword. Good for smacking.", 2.0, 1);
	//Item * j = new Weapon(101, "Iron Sword", "A dull looking iron sword. Wouldn't want to get slashed by that.", 4.0, 5);
	//m_ent[0]->inventory.AddItem(i);
	//m_ent[0]->inventory.AddItem(j);
	//

	//
	//m_ent[0]->inventory.AddItem(file.CreateObject(208));
	////m_ent[0]->inventory.ShowAllItems();
	
	//Save();
	
	/*
	std::cout << currentLocation.name << std::endl << currentLocation.description << std::endl;
	*/
}

void Game::Save()
{
	if (m_ent[0]->inventory.ReturnSize() > 0)
	{
		std::ofstream outInv("PlayerInventory.txt");

		for (int i = 0; i < m_ent[0]->inventory.ReturnSize(); i++)
		{
			/*if (i != m_ent[0]->inventory.ReturnSize() - 1)
			{
				outInv << m_ent[0]->inventory.m_inventory[i]->ReturnID() << ',';
			}
			else
				outInv << m_ent[0]->inventory.m_inventory[i]->ReturnID();*/
			outInv << m_ent[0]->inventory.m_inventory[i]->ReturnID() << ',' << m_ent[0]->inventory.m_inventory[i]->Equipped() << std::endl;
		}
	}
}

bool Game::Playing()
{
	return playing;
}

int Game::CheckPlayerState()
{
	return m_ent[0]->ReturnState();
}

void Game::ProcessInput(int state, int choice)
{
	if ((state == States::Idle) && (currentLocation.ID == Locations::Home))
	{
		switch (choice)
		{
		case 1:
			//Travel
			m_ent[0]->Travel();
			break;
		case 2:
			//Inventory
			m_ent[0]->inventory.ShowAllItems();
			break;
		case 3:
			//Rest
			m_ent[0]->ResetStats();
			break;
		case 4:
			//Stats
			m_ent[0]->PrintStats();
			m_ent[0]->PrintEquipped();
			break;
		case 5:
			m_ent[0]->Equip();
			break;
		default:
			std::cout << "Incorrect input." << std::endl;
		}
	}
	else if ((state == States::Idle) && (currentLocation.ID != Locations::Home))
	{
		switch (choice)
		{
		case 1:
			//Travel
			m_ent[0]->Travel();
			break;
		case 2:
			//Inventory
			m_ent[0]->inventory.ShowAllItems();
			break;
		case 3:
			//Escape
			m_ent[0]->ReturnHome();
			break;
		case 4:
			//Stats
			m_ent[0]->PrintStats();
			break;
		default:
			std::cout << "Incorrect input." << std::endl;
		}
	}
	else if (state == States::Battle)
	{

	}
}

void Game::SetLocation()
{
	FileLoader file;

	currentLocation = file.LoadLocation(m_ent[0]->ReturnLocation());
}

//Belongs in LoadSave()
//if (std::ifstream("player.txt"))
//{
//	std::ifstream infile;
//	infile.open("player.txt");
//
//	std::string name;
//	//std::string h, mh, a, ma, m, mm, man, maxman;
//	std::string health, maxh, attack, maxa, magic, maxmag, mana, maxmana;
//
//	if (!infile)
//		std::cout << "Error loading file" << std::endl;
//	else
//	{
//		while (std::getline(infile, name, ','))
//		{
//			std::getline(infile, health, ',');
//			std::getline(infile, maxh, ',');
//			std::getline(infile, attack, ',');
//			std::getline(infile, maxa, ',');
//			std::getline(infile, magic, ',');
//			std::getline(infile, maxmag, ',');
//			std::getline(infile, mana, ',');
//			std::getline(infile, maxmana);
//		}
//	}
//
//	Entity load(name, std::stod(health), std::stod(maxh), std::stod(attack), std::stod(maxa), std::stod(magic), std::stod(maxmag), std::stod(mana), std::stod(maxmana));
//
//	std::cout << "Welcome back, " << name << std::endl;
//	std::cout << "Stats\nHealth: " << load.ReturnHealth() << std::endl << "Attack: " << load.ReturnAttack() << std::endl;
//	std::cout << "Magic: " << load.ReturnMagic() << std::endl << "Mana: " << load.ReturnMana() << std::endl;
//}
//else
//{
//	Entity* load[1];
//	//Entities Class;
//
//	std::ofstream outfile;
//	std::string name;
//
//	std::cout << "No save file found. Creating new save now..." << std::endl;
//	std::cout << "What is your name?" << std::endl << "> ";
//
//	std::cin >> name;
//
//	outfile.open("player.txt");
//
//	std::cout << "Alright, " << name << ", what are you?" << std::endl;
//	std::cout << "1 - Warrior: Ferocious, brute, and unyielding." << std::endl;
//	std::cout << "2 - Rogue: Crafty, cunning, and witty." << std::endl;
//	std::cout << "3 - Wizard: Intelligent, all-knowing, and good and stuff." << std::endl;
//
//	HeroIndex index;
//	std::cin >> index;
//
//	switch (index)
//	{
//	case HeroKey::Warrior:
//		load[0] = new Entity(name, 10.0, 10.0, 12.0, 12.0, 3.0, 3.0, 3.0, 3.0);
//		load[0]->SetClass(HeroKey::Warrior);
//		break;
//
//	case HeroKey::Rogue:
//		load[0] = new Entity(name, 9.0, 9.0, 8.0, 8.0, 6.0, 6.0, 7.0, 7.0);
//		load[0]->SetClass(HeroKey::Rogue);
//		break;
//
//	case HeroKey::Wizard:
//		load[0] = new Entity(name, 9.0, 9.0, 5.0, 5.0, 13.0, 13.0, 12.0, 12.0);
//		load[0]->SetClass(HeroKey::Wizard);
//		break;
//	}
//
//	//std::cout << "Stats" << std::endl << "Name: " << load.ReturnName() << std::endl << "Health: " << load.ReturnHealth() << std::endl << "Attack: " << load.ReturnAttack() << std::endl;
//
//	outfile << load[0]->ReturnName() << ',' << load[0]->ReturnHealth() << ',' << load[0]->ReturnMaxHealth() << ','
//		<< load[0]->ReturnAttack() << ',' << load[0]->ReturnMaxAttack() << ',' << load[0]->ReturnMagic() << ','
//		<< load[0]->ReturnMaxMagic() << ',' << load[0]->ReturnMana() << ',' << load[0]->ReturnMaxMana();
//	std::cout << "File written to." << std::endl;
//}