#pragma once

#include <string>
#include <iostream>
#include "Locations.h"

class UIManager
{
public:

	UIManager();

	void Options();
	void Clear();
	void Menu(int location, const std::string & l);
	void BattleMenu();
	void OutputText(const std::string & text);
	//int GetInput(char input);
};