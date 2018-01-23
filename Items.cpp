#include "stdafx.h"
#include "Items.h"

Item::Item(int id, std::string nam, std::string desc, double stat, int val)
	:ID(id)
	,name(nam)
	,description(desc)
	,stats(stat)
	,value(val)
{
	equippable = false;
	equipped = false;
}

int Item::ReturnID()
{
	return ID;
}

std::string Item::ReturnName()
{
	return name;
}

std::string Item::ReturnDesc()
{
	return description;
}

int Item::ReturnValue()
{
	return value;
}

std::string Item::IsEquippedAsString()
{
	if (equipped)
		return "Equipped";
	return "Not equipped";
}

bool Item::Equippable()
{
	if (equippable)
		return true;
	return false;
}

bool Item::Equipped()
{
	return equipped;
}

void Item::SetEquippedSlot(int i)
{
	equippedSlot = i;
}

void Item::SetEquipped(bool b)
{
	equipped = b;
}

int Item::ReturnEquippedSlot()
{
	return equippedSlot;
}

Weapon::Weapon(int id, std::string nam, std::string desc, double stat, int val) : Item(id, nam, desc, stat, val)
{
	ID = id;
	description = desc;
	stats = stat;
	attack = stats;
	value = val;
	item_type = "Weapon";
}

Armor::Armor(int id, std::string nam, std::string desc, double stat, int val) : Item(id, nam, desc, stat, val)
{
	ID = id;
	description = desc;
	stats = stat;
	defense = stats;
	value = val;
	item_type = "Armor";
}

Consumable::Consumable(int id, std::string nam, std::string desc, double stat, int val) : Item(id, nam, desc, stat, val)
{
	ID = id;
	description = desc;
	stats = stat;
	effect_amount = stats;
	value = val;
	item_type = "Consumable";
}

void Weapon::Equip()
{
	if (equippable && !equipped)
	{
		equipped = true;
		std::cout << "The " << name << " has been equipped!" << std::endl;
	}
	else
		std::cout << "Cannot equip that!" << std::endl;
}

void Armor::Equip()
{
	std::cout << "Equipped!" << std::endl;
}

void Consumable::Equip()
{
	std::cout << "Equipped!" << std::endl;
}

double Weapon::ReturnStat()
{
	return attack;
}

double Armor::ReturnStat()
{
	return defense;
}

double Consumable::ReturnStat()
{
	return effect_amount;
}