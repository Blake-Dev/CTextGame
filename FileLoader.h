#pragma once

#include "Entity.h"
#include "Items.h"
#include "HeroDef.h"
#include "EnemyDef.h"
#include "Enemy.h"
#include "ItemDef.h"
#include "Locations.h"

#include <vector>
#include <fstream>
#include <string>

class FileLoader
{
public:
	FileLoader();

	std::vector<Item*> LoadPlayerItems();
	Entity* LoadSave();
	Entity* CreateSave();
	Item* CreateObject(int id);
	Location LoadLocation(int id);
	Enemy CreateEnemy(int id);
	//std::vector<Entity*> ReturnEnt();

	std::vector<Item*> m_items;
	std::vector<Entity*> m_ent;
};