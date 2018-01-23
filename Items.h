#pragma once

#include <string>
#include <iostream>

class Item
{
public:
	Item(int id, std::string nam, std::string desc, double stat, int val);

	int ReturnID();
	std::string ReturnName();
	std::string ReturnDesc();
	int ReturnValue();
	std::string IsEquippedAsString();
	bool Equippable();
	bool Equipped();
	void SetEquippedSlot(int i);
	void SetEquipped(bool b);
	int ReturnEquippedSlot();
	virtual void Equip() = 0;
	virtual double ReturnStat() = 0;

	std::string item_type;

protected:
	std::string name, description;
	int ID, value, equippedSlot;
	double stats;
	bool equippable, equipped;
};

class Weapon : public Item
{
public:
	Weapon(int id, std::string nam, std::string desc, double stat, int val);
	virtual void Equip();
	virtual double ReturnStat();

protected:
	double attack;
};

class Armor : public Item
{
public:
	Armor(int id, std::string nam, std::string desc, double stat, int val);
	virtual void Equip();
	virtual double ReturnStat();


protected:
	double defense;
};

class Consumable : public Item
{
public:
	Consumable(int id, std::string nam, std::string desc, double stat, int val);
	virtual void Equip();
	virtual double ReturnStat();

protected:
	double effect_amount;
};