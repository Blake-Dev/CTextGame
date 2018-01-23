#pragma once

typedef int EnemyIndex;

struct EnemyKey
{
	enum EnemyType
	{
		Goblin,
		Skeleton,
		Undead,
		Dragon,
		GiantSpider,
		Bandit,
		Mage,

		Count
	};
};