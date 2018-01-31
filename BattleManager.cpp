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
			std::cout << enemies[i].name << " // ATK " << enemies[i].attack << "   HP " << enemies[i].health << std::endl;
			/*std::cout << "Magic: " << enemies[i].magic << std::endl;
			std::cout << "Mana: " << enemies[i].mana << std::endl << std::endl;*/
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
		if (enemies.size() == 1)
		{
			ui.OutputText("As you push through the clearing into the next room\nyou see a lone enemy unaware of your presence.\n");
			PrintEnemies();
		}
		else
		{
			ui.OutputText("Multiple enemies stand between you and the exit...\n\n");
			PrintEnemies();
		}
		_getch();
		system("cls");
		int choice;

		battling = true;
		while (battling)
		{
			std::cout << player->ReturnName() << " // " << "ATK " << player->ReturnAttack() << "   HP " << player->ReturnHealth() << std::endl;
			ui.BattleMenu();
			std::cout << "\n -------\n<ENEMIES>\n -------\n" << std::endl;
			PrintEnemies();
			
			std::cout << "\n" << "> ";
			std::cin >> choice;
			ui.Clear();

			if ((!EnemiesAlive()) || (player->ReturnHealth() <= 0))
			{
				battling = false;
				player->SetState(States::Idle);
			}
			else
			{
				switch (choice)
				{
				case 1:
					//Attack
					int attackChoice;
					EnemiesToAttack(player);
					std::cout << "\n" << "> ";
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
				ui.OutputText("\n");
				player->RechargeMana();
			}
		}
	}

}

void BattleManager::EnemiesToAttack(Entity * player)
{
	std::cout << player->ReturnName() << " // " << "ATK " << player->ReturnAttack() << "   HP " << player->ReturnHealth() << std::endl << std::endl;
	std::cout << "---------------------------\nSelect an enemy to attack:\n---------------------------" << std::endl << std::endl;

	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].health > 0.0)
			{
				std::cout << i << ". " << enemies[i].name << " // " << "HP " << enemies[i].health << std::endl;
			}
			else
			{
				std::cout << i << ". " << enemies[i].name << " // " << "HP 0" << std::endl;
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
					std::cout << "You retreat back to the safety of your home..." << std::endl;
					player->SetState(States::Idle);
					player->SetLocation(Locations::Home);
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