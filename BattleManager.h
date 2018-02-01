#pragma once

#include "Game.h"
#include "Enemy.h"
#include "EnemyDef.h"
#include "FileLoader.h"
#include "UIManager.h"
#include "Entity.h"

#include <iostream>
#include <vector>
#include <random>

class BattleManager
{
public:
	std::random_device rdevice{};
	std::default_random_engine num{ rdevice() };

	BattleManager();

	double ReturnRandStat(int low, int high);
	int ReturnEnemyAmount();
	int ReturnEnemyID();
	int ReturnEasyEnemyID();

	void CreateEnemies();
	void CreateEnemy();
	void PrintEnemies();
	void Battle(Entity * player, int locationID);
	void EnemiesToAttack(Entity * player);
	bool EnemiesAttackPlayer(Entity * player);
	bool EnemiesAlive();
	void EnemiesFormatted();

	std::vector<Enemy> enemies;

private:
	bool battling;
};