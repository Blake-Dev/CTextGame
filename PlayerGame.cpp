// PlayerGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "Entity.h"
#include "Items.h"
#include "PlayerStates.h"
#include "FileLoader.h"
#include "UIManager.h"
#include "BattleManager.h"

#include <iostream>
#include <conio.h>

int main()
{
	Game game;
	UIManager UI;
	
	int choice;

	UI.OutputText("Throughout this game, you will be shown a screen with a '> ' followed by a blinking cursor.\nThis means press any key to continue.\nGood luck!\n");
	_getch();

	while (game.Playing())
	{
		UI.Clear();
		//Process Inputs
		switch (game.CheckPlayerState())
		{
		case States::Idle:
			UI.Menu(game.currentLocation.ID, game.currentLocation.name);
			std::cout << "> ";
			std::cin >> choice;
			UI.Clear();
			game.ProcessInput(States::Idle, choice);

			break;
		case States::Battle:
		{
			BattleManager bm;
			bm.Battle(game.m_ent[0], game.currentLocation.ID);
		}
			break;
		default:
			break;
		}
		//Update Game World
		game.SetLocation();
		//Generate Outputs

		//Pause for user input
		std::cout << "> ";
		_getch();
	}

    return 0;
}

