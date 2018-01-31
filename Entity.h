#pragma once
#include <string>
#include <iomanip>
#include "Inventory.h"
#include "PlayerStates.h"
#include "Locations.h"
#include "UIManager.h"
#include "ArmorSlots.h"

const int EQUIPPED_INV_SIZE = 6;

class Entity
{
public:
	Entity(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman);

	void SetID(int i);
	std::string ReturnName();
	std::string ReturnClass();
	int ReturnState();
	int ReturnLocation();
	double ReturnHealth();
	double ReturnMaxHealth();
	double ReturnAttack();
	double ReturnMaxAttack();
	double ReturnMagic();
	double ReturnMaxMagic();
	double ReturnMana();
	double ReturnMaxMana();
	void RechargeMana();
	void Heal();
	void TakeDamage(double d);
	void SetDefense(double d);
	double ReturnDefense();

	void SetState(int p_state);
	void SetLocation(int p_location);
	void Travel();
	void ResetStats();
	void ReturnHome();
	void IncrementDungeonLevel();
	void SetDungeonLevel(int lvl);
	int ReturnDungeonLevel();

	void AddGold(int g);
	void RemoveGold(int g);
	int ReturnGold();

	void PrintStats();
	void PrintEquipped();
	void EquippedItemInfo(int id);
	void Equip();

	Inventory inventory;
	Item * currentlyEquipped[EQUIPPED_INV_SIZE] = { NULL, NULL, NULL, NULL, NULL, NULL };

protected:
	std::string name, classType;
	double health, max_health, attack, max_attack, magic, max_magic, mana, max_mana;
	double defense = 0;
	int ID, currentDungeonLevel;
	int gold = 0;
	int state = States::Idle;
	int location = Locations::Home;
};

class Warrior : public Entity
{
public:
	Warrior(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman);

private:
	std::string special_text = "You focus your carniverous rage!";

	double special_damage = max_attack * 3.0;
};

class Rogue : public Entity
{
public:
	Rogue(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman);

private:
	std::string special_text = "You're enemies appear to be unmoving. You move with the shadows.";

	double special_damage = max_attack * 3.0;
};

class Wizard : public Entity
{
public:
	Wizard(std::string n, double h, double mh, double a, double ma, double m, double mm, double man, double maxman);

private:
	std::string special_text = "You breathe away the worries of battle as you focus on inner peace.";

	double special_damage = max_attack * 3.0;
};