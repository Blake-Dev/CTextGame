#pragma once

typedef int HeroIndex;

struct HeroKey
{
	enum HeroType
	{
		Warrior = 1,
		Rogue,
		Wizard,

		Count
	};
};