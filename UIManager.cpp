#include "stdafx.h"
#include "UIManager.h"

#include <iomanip>

UIManager::UIManager() {}

void UIManager::Options()
{
	std::cout << std::setfill('=') << std::setw(30) << '=' << std::setfill(' ') << std::endl;
	std::cout << std::left << std::setw(15) << "> 1" << std::right << std::setw(15) << "Travel" << std::endl;
	std::cout << std::left << std::setw(15) << "> 2" << std::right << std::setw(15) << "Inventory" << std::endl;
	std::cout << std::left << std::setw(15) << "> 3" << std::right << std::setw(15) << "Check Stats" << std::endl;
	std::cout << std::left << std::setw(15) << "> 4" << std::right << std::setw(15) << "Save Game" << std::endl;
	std::cout << std::left << std::setw(15) << "> 5" << std::right << std::setw(15) << "Quit Game" << std::endl;
	std::cout << std::setfill('=') << std::setw(30) << '=' << std::setfill(' ') << std::endl;
}

void UIManager::Menu(int location, const std::string & l)
{
	std::cout << "Location // " << l << std::endl;
	std::cout << std::setfill('=') << std::setw(30) << '=' << std::setfill(' ') << std::endl;
	switch (location)
	{
	case Locations::Home:
		std::cout << std::left << std::setw(4) << "1 - " << std::setw(10) << std::right << "Travel " << std::setw(2) << "| " << std::setw(4) << std::left << "2 - " << std::setw(10) << std::right << "Inventory" << std::endl;
		std::cout << std::left << std::setw(4) << "3 - " << std::setw(10) << std::right << "Rest " << std::setw(2) << "| " << std::setw(4) << std::left << "4 - " << std::setw(10) << std::right << "Stats" << std::endl;
		break;
	default:
		std::cout << std::left << std::setw(4) << "1 - " << std::setw(10) << std::right << "Travel " << std::setw(2) << "| " << std::setw(4) << std::left << "2 - " << std::setw(10) << std::right << "Inventory" << std::endl;
		std::cout << std::left << std::setw(4) << "3 - " << std::setw(10) << std::right << "Escape " << std::setw(2) << "| " << std::setw(4) << std::left << "4 - " << std::setw(10) << std::right << "Stats" << std::endl;
		break;
	}
	std::cout << std::setfill('=') << std::setw(30) << '=' << std::setfill(' ') << std::endl;
}

void UIManager::BattleMenu()
{
	std::cout << std::setfill('*') << std::setw(25) << '*' << std::setfill(' ') << std::endl;
	std::cout << std::left << std::setw(2) << "1." << std::setw(8) << std::right << "Attack" << std::setw(4) << " | " << std::setw(2) << std::left << "2." << std::setw(8) << std::right << "Defend" << std::endl;
	std::cout << std::left << std::setw(2) << "3." << std::setw(8) << std::right << "Heal" << std::setw(4) << " | " << std::setw(2) << std::left << "4." << std::setw(8) << std::right << "Item" << std::endl;
	std::cout << std::setfill('*') << std::setw(25) << '*' << std::setfill(' ') << std::endl;
}

void UIManager::Clear()
{
	system("cls");
}

void UIManager::OutputText(const std::string & text)
{
	std::cout << text << std::endl;
}