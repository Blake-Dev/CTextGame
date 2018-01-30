#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>
#include "Entity.h"
#include "HeroDef.h"
#include "FileLoader.h"
#include "Locations.h"

class Game
{
public:
	Game();

	void LoadSave();
	void Save();
	bool Playing();
	int CheckPlayerState();
	void ProcessInput(int state, int choice);
	void SetLocation();
	void MainMenu();

	std::vector<Entity*> m_ent;
	Location currentLocation;
private:
	bool playing;
};