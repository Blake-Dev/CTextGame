#pragma once

#include <string>
#include <iostream>

typedef int LocationID;

struct Locations
{
	enum Location
	{
		Home,
		SmallDungeon,
		LargeDungeon,
		Abyss,

		Count
	};
};

struct Location
{
	int ID;
	std::string name;
	std::string description;
};