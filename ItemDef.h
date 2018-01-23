#pragma once

typedef int ItemID;

struct ItemDefs
{
	enum Item
	{
		WoodenSword = 100,
		IronSword,
		SteelDagger,
		DualWieldDagger,
		SteelTipSpear,
		BowAndArrow,

		TornClothes = 200,
		LeatherHelm,
		LeatherArms,
		LeatherCuirass,
		LeatherLegs,
		SteelHelm,
		SteelArms,
		SteelBreastPlate,
		SteelLegs,
		WoodenShield,
		SteelKiteShield,

		HealthPotion = 300,
		ManaPotion,

		Count
	};
};