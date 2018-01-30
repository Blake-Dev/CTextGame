#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	//playing = true;
	LoadSave();
	MainMenu();
}

void Game::LoadSave()
{
	FileLoader file;

	m_ent.push_back(file.LoadSave());
	m_ent[0]->inventory.m_inventory = file.LoadPlayerItems();
	SetLocation();

	std::cout << "File save detected..." << std::endl << std::endl;

	//m_ent[0]->PrintStats();

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

void Game::MainMenu()
{
	// Menu seen by user when game first starts

	int input;
	bool done = false;
	std::cout << "Main Menu\n---------\n1. Play Game\n2. New Game\n3. Game Stats" << std::endl;
	std::cin >> input;

	while (!done)
	{
		switch (input)
		{
		case 1:
			std::cout << "Starting game..." << std::endl;
			done = true;
			break;
		case 2:
			char newGame;
			std::cout << "Create a new game save?\n\nAll previous data will be lost\n(y/n) ";
			std::cin >> newGame;
			if (toupper(newGame) == 'Y')
			{
				//create a new game
				FileLoader file;

				m_ent.push_back(file.CreateSave());
				m_ent[0]->inventory.m_inventory = file.LoadPlayerItems();
				SetLocation();
				done = true;
			}
			break;
		case 3:
			std::cout << "Game Stats go here." << std::endl;
			break;
		default:
			std::cout << "Incorrect input" << std::endl;
			break;
		}
	}
}