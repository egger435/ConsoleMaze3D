#include <iostream>
#include <stdlib.h>
using namespace std;
#include "Menu.h"
#include "GamePlay.h"
int main()
{
    bool gotoStartMenu = true;
    Menu startMenu(start_menu);
    startMenu.FullScreen();
    while (gotoStartMenu)
    {
        system("cls");
        startMenu.ResetStartMenu();
        startMenu.display();
        PlayerAction action = startMenu.ReceiveUserAction();  //接收用户操作

        system("cls");
        switch (action)
        {
		case start_play:
		{
			Menu playMenu(play_menu);
			playMenu.display();
			action = playMenu.ReceiveUserAction();  //接收用户选择关卡操作
			if (action == back_to_start_menu)
			{
				gotoStartMenu = true;
			}
			else if (action == play_game)
			{
				system("cls");
				GamePlay gamePlay;
				bool game_over = false;
				while (!game_over)
				{
					game_over = gamePlay.Update();
				}
			}
		}
		break;
		case start_design:
		{
			Menu designMenu(design_menu);
			designMenu.display();
			action = designMenu.ReceiveUserAction();  //接受用户设计地图操作
			if (action == back_to_start_menu)
			{
				gotoStartMenu = true;
			}
		}
		break;
		}
	}

    system("pause");
    return 0;
}

