#include "stdafx.h"
#include "BattleManager.h"

BattleManager::BattleManager() {}

double BattleManager::ReturnRandStat(int low, int high)
{
	std::uniform_int_distribution<int> randomNum{ low, high };
	return static_cast<double>(randomNum(num));
}


int BattleManager::ReturnEnemyAmount()
{
	std::uniform_int_distribution<unsigned int> randomNum{ 0, 3 };
	return randomNum(num);
}

int BattleManager::ReturnEnemyID()
{
	std::uniform_int_distribution<unsigned int> randomNum{ 0, 6 };
	return randomNum(num);
}

int BattleManager::ReturnEasyEnemyID()
{
	std::uniform_int_distribution<unsigned int> randomNum{ 0, 3 };
	return randomNum(num);
}

void BattleManager::CreateEnemies()
{
	FileLoader file;

	//Create baddies
	if (ReturnEnemyAmount() > 0)
	{
		for (int i = 0; i < ReturnEnemyAmount(); i++)
		{
			Enemy e;
			e = file.CreateEnemy(ReturnEnemyID());
			e.magic = ReturnRandStat(e.attack, e.attack + 5);
			e.mana = ReturnRandStat(e.health, e.health + 5);
			e.attack = ReturnRandStat(e.attack, e.attack + 5);
			e.health = ReturnRandStat(e.health, e.health + 5);

			enemies.push_back(e);
		}
	}
}

void BattleManager::CreateEnemy()
{
	FileLoader file;

	//Create baddies
	
	Enemy e;
	e = file.CreateEnemy(ReturnEasyEnemyID());
	e.magic = ReturnRandStat(e.attack, e.attack + 5);
	e.mana = ReturnRandStat(e.health, e.health + 5);
	e.attack = ReturnRandStat(e.attack, e.attack + 5);
	e.health = ReturnRandStat(e.health, e.health + 5);

	enemies.push_back(e);
	
}

void BattleManager::PrintEnemies()
{
	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			std::cout << "Name: " << enemies[i].name << std::endl;
			std::cout << "Attack: " << enemies[i].attack << std::endl;
			std::cout << "Health: " << enemies[i].health << std::endl;
			std::cout << "Magic: " << enemies[i].magic << std::endl;
			std::cout << "Mana: " << enemies[i].mana << std::endl << std::endl;
		}
	}
	else
		std::cout << "Potato\n";
}

void BattleManager::Battle(Entity * player, int locationID)
{
	UIManager ui;

	if (locationID == Locations::SmallDungeon)
		CreateEnemy();
	else
		CreateEnemies();

	if (enemies.size() > 0)
	{
		int choice;
		ui.OutputText("Prepare for battle!\n");
		PrintEnemies();

		battling = true;
		while (battling)
		{
			EnemiesFormatted();
			ui.OutputText("\n");
			std::cout << "Player - Health | " << player->ReturnHealth() << " - Attack | " << player->ReturnAttack() << std::endl;
			ui.BattleMenu();
			std::cout << "> ";
			std::cin >> choice;

			switch (choice)
			{
			case 1:
				//Attack
				int attackChoice;
				EnemiesToAttack();
				std::cout << "> ";
				std::cin >> attackChoice;

				if (enemies[attackChoice].health > 0.0)
				{
					std::cout << "You attack the " << enemies[attackChoice].name << " for " << player->ReturnAttack() << " damage!" << std::endl;
					enemies[attackChoice].health -= player->ReturnAttack();
					if (enemies[attackChoice].health <= 0.0)
						ui.OutputText("You have slain the enemy!");
				}
				else
					ui.OutputText("You can't attack something that's dead!");
	
				break;
			case 2:
				//Defend
				ui.OutputText("You defend and stuff and things!");
				break;
			case 3:
				//Heal
				player->Heal();
				break;
			case 4:
				//Use Item
				ui.OutputText("Coming Soon");
				break;
			default:
				std::cout << "Choice out of range!" << std::endl;
				break;
			}
			EnemiesAttackPlayer(player);
			player->RechargeMana();

			if ((!EnemiesAlive()) || (player->ReturnHealth() <= 0))
			{
				battling = false;
				player->SetState(States::Idle);
			}
		}
	}

}

void BattleManager::EnemiesToAttack()
{
	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].health > 0.0)
			{
				std::cout << i << " - " << enemies[i].name << " | " << "Health - " << enemies[i].health << std::endl;
			}
			else
			{
				std::cout << i << " - " << enemies[i].name << " | " << "Health - X" << std::endl;
			}
		}
	}
}

void BattleManager::EnemiesAttackPlayer(Entity * player)
{
	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if ((player->ReturnHealth() > 0.0) && (enemies[i].health > 0.0))
			{
				player->TakeDamage(enemies[i].attack);
				std::cout << "The " << enemies[i].name << " attacks you for " << enemies[i].attack << " damage!" << std::endl;

				if (player->ReturnHealth() <= 0.0)
				{
					std::cout << "You have been slain!" << std::endl;
					return;
				}
			}
		}
	}
}

bool BattleManager::EnemiesAlive()
{
	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].health > 0.0)
			{
				return true;
			}
		}
	}
	return false;
}

void BattleManager::EnemiesFormatted()
{
	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].health > 0.0)
			{
				std::cout << enemies[i].name << " - " << "Health | " << enemies[i].health << " - " << "Attack | " << enemies[i].attack << std::endl;
			}
			else
			{
				std::cout << enemies[i].name << " - " << "Health | X" << " - " << "Attack | " << enemies[i].attack << std::endl;
			}
		}
	}
}