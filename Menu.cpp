#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
#include "Menu.h"
#include "MazeDesign.h"
#include "GamePlay.h"
string GamePlay::currentLevel = "none";
Menu::Menu(MenuType menutype)
{
	this->height = 20;
	this->width = 100;
	this->menutype = menutype;

	//初始化菜单缓冲区
	menu_buffer = new char* [height + 2];
	for (int i = 0; i < height; i++)
	{
		menu_buffer[i] = new char[width + 2];
	}

	//将菜单缓冲区内容初始化为空
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			menu_buffer[i][j] = ' ';
		}
	}

	//根据不同菜单类型初始化
	switch (menutype)
	{
	case start_menu:
		StartMenuInitialize();
		break;
	case design_menu:
		DesignMenuInitialize();
		break;
	case play_menu:
		PlayMenuInitialize();
		break;
	}
}

void Menu::StartMenuInitialize()
{
	//最上方边
	for (int i = 0; i < width; i++)
	{
		menu_buffer[0][i] = '@';
	}
	//写入中间标语内容
	int j;
	for (j = 1; j < (height - 5) / 2; j++)
	{
		menu_buffer[j][0] = '@';
		int i;
		for (i = 1; i < width - 1; i++)
		{
			menu_buffer[j][i] = ' ';
		}
		menu_buffer[j][i] = '@';
	}
	/*menu_buffer[7]  = (char*)"   #     #     #     #####   #####  |   &&&&    &&&        1.Press A to play                       ";
	menu_buffer[8]  = (char*)"   ##   ##    # #       #    #      |       &   &  &                                               ";
	menu_buffer[9]  = (char*)"   # # # #   #   #     #     #####  |   &&&&&   &   &      2.Press D to design maze                ";
	menu_buffer[10] = (char*)"   #  #  #   #####    #      #      |       &   &  &                                               ";
	menu_buffer[11] = (char*)"   #  #  #   #   #   #####   #####  |   &&&&    &&&        3.Press E to exit                       ";*/

	/*strcpy(menu_buffer[7],  "   #     #     #     #####   #####  |   &&&&    &&&        1.Press A to play                       ");
	strcpy(menu_buffer[8],  "   ##   ##    # #       #    #      |       &   &  &                                               ");
	strcpy(menu_buffer[9],  "   # # # #   #   #     #     #####  |   &&&&&   &   &      2.Press D to design maze                ");
	strcpy(menu_buffer[10], "   #  #  #   #####    #      #      |       &   &  &                                               ");
	strcpy(menu_buffer[11], "   #  #  #   #   #   #####   #####  |   &&&&    &&&        3.Press E to exit                       ");*/

	strcpy_s(menu_buffer[7], 100,  "   #     #     #     #####   #####  |   &&&&    &&&        1.Press A to play                       ");
	strcpy_s(menu_buffer[8], 100,  "   ##   ##    # #       #    #      |       &   &  &                                               ");
	strcpy_s(menu_buffer[9], 100,  "   # # # #   #   #     #     #####  |   &&&&&   &   &      2.Press D to design maze                ");
	strcpy_s(menu_buffer[10], 100, "   #  #  #   #####    #      #      |       &   &  &                                               ");
	strcpy_s(menu_buffer[11], 100, "   #  #  #   #   #   #####   #####  |   &&&&    &&&        3.Press E to exit                       ");

	j = j + 5;
	for (; j < height - 1; j++)
	{
		menu_buffer[j][0] = '@';
		int i;
		for (i = 1; i < width - 1; i++)
		{
			menu_buffer[j][i] = ' ';
		}
		menu_buffer[j][i] = '@';
	}
	//底边
	for (int i = 0; i < width; i++)
	{
		menu_buffer[j][i] = '@';
	}
}

void Menu::DesignMenuInitialize()
{
	//读取地图数据，若数量达到6个，提示玩家先去玩，不让设计
	//目的是为了限制地图在6个，因为游戏关卡选择上不想设计翻页
	fstream mazelevelData("mazelevel.data", ios::in);
	vector<string> mazelevelNames;
	string name;
	while (!mazelevelData.eof())
	{
		mazelevelData >> name;
		if (mazelevelData.fail())
		{
			break;
		}
		mazelevelNames.push_back(name);
	}
	mazelevelData.close();
	if (mazelevelNames.size() == 6)
	{
		for (int i = 0; i < 4; i++)
		{
			cout << endl;
		}
		string to_much_maze = "There are too many maze maps, let's play a few more and come back :D";
		string haha = "实际上我就是懒得做地图选择页面的翻页功能，hhh";
		for (int i = 0; i < to_much_maze.length(); i++)
		{
			cout << to_much_maze[i];
			Sleep(50);
		}
		cout << endl;
		for (int i = 0; i < haha.length(); i++)
		{
			cout << haha[i];
			Sleep(50);
		}
		return;
	}

	//最上方边
	for (int i = 0; i < width - 1; i++)
	{
		menu_buffer[0][i] = '@';
	}

	strcpy_s(menu_buffer[1], 100, "@   Please design your maze below :D                                                               ");  //第一行标语
	menu_buffer[1][99] = '@';
	int i = 2;
	menu_buffer[i][0] = '@';
	menu_buffer[i][1] = ' ';
	for (int j = 2; j <= 18; j++)
	{
		menu_buffer[i][j] = '#';
	}
	menu_buffer[i][98] = '@';

	i++;  //i = 3
	menu_buffer[i][0] = '@';
	menu_buffer[i][1] = ' ';
	menu_buffer[i][2] = '#';
	menu_buffer[i][18] = '#';
	menu_buffer[i][98] = '@';

	i++;  //i = 4
	menu_buffer[i][0] = '@';
	menu_buffer[i][1] = ' ';
	menu_buffer[i][2] = '#';
	menu_buffer[i][3] = '^';  //表示光标，初始位置4，3
	menu_buffer[i][18] = '#';
	menu_buffer[i][98] = '@';

	for (i = 5; i <= 18; i++)
	{
		menu_buffer[i][0] = '@';
		menu_buffer[i][1] = ' ';
		menu_buffer[i][2] = '#';
		menu_buffer[i][18] = '#';
		menu_buffer[i][98] = '@';
	}  //i = 18

	//地图设计提示
	strcpy_s(menu_buffer[6], 100,  "@ #               #     tips: Use 'w a s d' to move the cursor.                                   #");
	strcpy_s(menu_buffer[8], 100,  "@ #               #           Press 'space' to place bricks.                                      #");
	strcpy_s(menu_buffer[10], 100, "@ #               #           Press 'b' to delate bricks.                                         #");
	strcpy_s(menu_buffer[12], 100, "@ #               #           Press 'i' to set the entrance.                                      #");
	strcpy_s(menu_buffer[14], 100, "@ #               #           Press 'o' to set the exit.                                          #");
	strcpy_s(menu_buffer[16], 100, "@ #               #           Press 'm' to return to the main menu.                               #");
	strcpy_s(menu_buffer[18], 100, "@ #               #           If the maze has already been designed, press 'p'.                   #");

	menu_buffer[i][0] = '@';
	menu_buffer[i][1] = ' ';
	for (int j = 2; j <= 18; j++)
	{
		menu_buffer[i][j] = '#';
	}
	menu_buffer[i][98] = '@';

}

/// <summary>
/// 将迷宫文件中的数字代码转换为菜单中显示的字符串
/// </summary>
/// <param name="mazeNum">迷宫文件中的数组代码</param>
/// <returns></returns>
char MazeNumToChar(int mazeNum)
{
	char c = ' ';
	switch (mazeNum)
	{
	case 0:
		c = ' ';
		break;
	case 1:
		c = '1';
		break;
	case 2:
		c = 's';
		break;
	case 3:
		c = 'e';
		break;
	}
	return c;
}

char MazeNumToChar(char mazeNum)
{
	char c = ' ';
	switch (mazeNum)
	{
	case '0':
		c = ' ';
		break;
	case '1':
		c = '1';
		break;
	case '2':
		c = 's';
		break;
	case '3':
		c = 'e';
		break;
	}
	return c;
}

void Menu::PlayMenuInitialize()
{
	fstream levelData("mazelevel.data", ios::in);  //获取迷宫关卡列表信息
	vector<string> mazeLevelNames;
	string name;
	while (!levelData.eof())
	{
		levelData >> name;
		if (levelData.fail())
		{
			break;
		}
		mazeLevelNames.push_back(name);
	}
	levelData.close();

	//最上方边
	for (int i = 0; i < width; i++)
	{
		menu_buffer[0][i] = '@';
	}
	//旁边边框
	for (int i = 1; i <= 18; i++)
	{
		menu_buffer[i][0] = '@';
		//menu_buffer[i][99] = '@';
	}
	//底边
	for (int i = 0; i < width; i++)
	{
		menu_buffer[19][i] = '@';
	}

	if (mazeLevelNames.size() == 0)
	{
		//提示没有迷宫关卡
		strcpy_s(menu_buffer[10], 100, "               There are no levels yet, hurry up and design one :D                                 ");
		//strcpy_s(menu_buffer[12], 100, "                       Press 'm' to return to the start menu                                       ");
		return;
	}

	strcpy_s(menu_buffer[2], 100, "@           Please select a level :D                                                               ");  //第一行标语
	strcpy_s(menu_buffer[4], 100, "@                                                                   Press 'w s' to move the cursor ");
	strcpy_s(menu_buffer[6], 100, "@                                                                   Press 'space' to confirm    :D ");
	strcpy_s(menu_buffer[8], 100, "@                                                                   Press 'd' to delete maze       ");
	strcpy_s(menu_buffer[10],100, "@                                                                   If you want to quit playing    ");
	strcpy_s(menu_buffer[11],100, "@                                                                   press 'b'                   :D ");
	string menuline;
	int i;
	for (i = 1; i <= mazeLevelNames.size(); i++)  //加载地图信息
	{
		//if (2 * i + 2 >= 18)  //如果地图太多，一页显示不完，则要显示到下一页
		//{
		//	strcpy_s(menu_buffer[18], 18, "@       next page");
		//	for (int j = 6; j <= 99; j++)  //将空字符转化为空格
		//	{
		//		if (menu_buffer[2 * i + 2][j] == '\0')
		//		{
		//			menu_buffer[2 * i + 2][j] = ' ';
		//			break;
		//		}
		//	}
		//	break;
		//}
		//else
		//{
		menuline = "@       " + mazeLevelNames[i - 1];
		strcpy_s(menu_buffer[2 * i + 2], 9 + mazeLevelNames[i - 1].length(), menuline.c_str());
		for (int j = 6; j <= 99; j++)  //将空字符转化为空格
		{
			if (menu_buffer[2 * i + 2][j] == '\0')
			{
				menu_buffer[2 * i + 2][j] = ' ';
				break;
			}
		}
		//}
	}
	//最后一行显示返回主菜单
	strcpy_s(menu_buffer[2 * i + 2], 13, "@       back");
	for (int j = 6; j <= 99; j++)  //将空字符转化为空格
	{
		if (menu_buffer[2 * i + 2][j] == '\0')
		{
			menu_buffer[2 * i + 2][j] = ' ';
			break;
		}
	}
	
	menu_buffer[4][6] = '^';  //光标，用于选择关卡

	//地图概览边框
	for (int i = 50; i <= 66; i++)  //最上方边
	{
		menu_buffer[2][i] = '#';
	}
	for (int i = 3; i <= 17; i++)  //两侧边框
	{
		menu_buffer[i][50] = '#';
		menu_buffer[i][66] = '#';
	}
	for (int i = 50; i <= 66; i++)
	{
		menu_buffer[18][i] = '#';
	}

	//加载第一关的地图俯视图
	fstream level1(mazeLevelNames[0] + ".maze", ios::in);
	if (level1.fail())
	{
		exit(0);
	}
	for (int i = 3; i <= 17; i++)
	{
		string mazeline;
		level1 >> mazeline;
		for (int j = 51; j <= 65; j++)
		{
			menu_buffer[i][j] = MazeNumToChar(mazeline[j - 51]);
		}
	}
	level1.close();
}

/// <summary>
/// 显示缓冲区的内容
/// </summary>
void Menu::display()
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			cout << menu_buffer[j][i];
		}
		cout << endl;
	}
	return;
}

/// <summary>
/// 根据不同菜单页面接收用户输入
/// </summary>
PlayerAction Menu::ReceiveUserAction()
{
	PlayerAction action = none;
	switch (this->menutype)
	{
	case start_menu:  //在开始菜单页面处理用户输入
#pragma region startMenuReceiveAction
	{
		bool flag = true;
		while (flag)
		{
			if (_kbhit())
			{
				char input = _getch();
				switch (input)
				{
				case 'a':
					ShowAnimation(input);
					cout << "hit A, play" << endl;
					flag = false;
					action = start_play;  //标记玩家行为为play
					break;
				case 'd':
					ShowAnimation(input);
					cout << "hit D, design" << endl;
					flag = false;
					action = start_design;  //标记玩家行为为design
					break;
				case 'e':
					exit(0);
					flag = false;
					break;
				default:
					cout << "wrong input" << endl;
					flag = true;
					break;
				}
			}
		}
	}
#pragma endregion
	break;

	case design_menu:  //地图设计菜单处理用户输入
#pragma region designMenuReceiveAction
	{
		//读取地图数据，若数量达到6个，提示玩家先去玩，不让设计
		//目的是为了限制地图在6个，因为游戏关卡选择上不想设计翻页
		fstream mazelevelData("mazelevel.data", ios::in);
		vector<string> mazelevelNames;
		string name;
		while (!mazelevelData.eof())
		{
			mazelevelData >> name;
			if (mazelevelData.fail())
			{
				break;
			}
			mazelevelNames.push_back(name);
		}
		mazelevelData.close();
		if (mazelevelNames.size() == 6)
		{
			string back_to_start = "about to return to start menu";
			for (int i = 0; i < back_to_start.length(); i++)
			{
				cout << back_to_start[i];
				Sleep(50);
			}
			system("pause");
			return back_to_start_menu;
		}

		MazeDesign mazedesign(16, 15);//实际上迷宫设计大小为15*15，为防止溢出写作16
		int cursorPos[2] = { 4, 3 };  //光标的初始坐标4，3, 对应迷宫数组初始位置0，0
		//pos[0]行，pos[1]列
		mazedesign.GetBuffer(15, 1);
		bool has_entrance = false;
		bool has_exit = false;
		bool end_design = false;
		while (!end_design)
		{
			if (_kbhit())
			{
				char input = _getch();
				switch (input)
				{
				case 'p':  //玩家按下p迷宫设计完成
				{
					if (has_entrance && has_exit)  //如果迷宫已经有了入口和出口则可以保存
					{
						//提示玩家是否确定保存设计好的迷宫
						strcpy_s(menu_buffer[1], 82, "@   !!!!!!!Are you sure the maze has been designed and ready to be saved?  y or n");
						fputs("\033[0;0H", stdout);
						display();
						while (true)
						{
							if (_kbhit())
							{
								char input = _getch();
								if (input == 'y')
								{
									strcpy_s(menu_buffer[1], 84, "@   !!!!!!!Give your maze a beautiful name :D                                      ");
									fputs("\033[0;0H", stdout);
									display();

									//读取地图数据，判断地图名是否重复  mazelevel.data 里面包含所有地图名称数据
									fstream mazeLevelsFile("mazelevel.data", ios::in);
									if (mazeLevelsFile.fail())
									{
										cout << "can not find mazelevel.data" << endl;
										exit(0);
									}
									vector<string> mazeLevelNames;
									string name;
									while (!mazeLevelsFile.eof())   //将所有地图名称数据储存在mazeLevelNames中
									{
										mazeLevelsFile >> name;
										if (mazeLevelsFile.fail())
										{
											break;
										}
										mazeLevelNames.push_back(name);
									}
									mazeLevelsFile.close();
									string mazeName;
									bool has_duplicate = true;  //先默认存在重复的地图
									while (has_duplicate)
									{
										cin >> mazeName;  //输入地图名称
										int i;
										for (i = 0; i < mazeLevelNames.size(); i++)
										{
											if (mazeName == mazeLevelNames[i])
											{
												cout << "Oops, the maze name is duplicated. Please change another name." << endl;
												has_duplicate = true;
												break;
											}
										}
										if (i == mazeLevelNames.size())  //若成功遍历完则不存在重复地图
										{
											has_duplicate = false;
										}
									}

									if (mazedesign.Save(mazeName))  //成功保存后将地图名字记录在mazelevelsfile（mazelevel.data）中
									{
										mazeLevelsFile.open("mazelevel.data", ios::app);
										mazeLevelsFile << mazeName << endl;
										mazeLevelsFile.close();
										cout << "The maze has been successfully saved :D" << endl;
									}
									cout << "About to return to the start menu!!!..." << endl;
									for (int i = 0; i < 15; i++)
									{
										Sleep(200);
										cout << '.';
									}
									action = back_to_start_menu;
									end_design = true;
									break;
								}
								else if (input == 'n')
								{
									strcpy_s(menu_buffer[1], 100, "@   Please design your maze below :D                                                               ");  //第一行标语
									fputs("\033[0;0H", stdout);
									display();
									break;
								}
							}
						}
					}
					else if (!has_entrance && !has_exit)  //提示玩家入口出口都还没放置
					{
						strcpy_s(menu_buffer[1], 79, "@   !!!!!!!BOTH the ENTRANCE and EXIT have not been set up yet!!!!!!!         ");
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (!has_entrance)  //提示玩家还没放置入口
					{
						strcpy_s(menu_buffer[1], 71, "@   !!!!!!!The ENTRANCE have not been set up yet!!!!!!!               ");
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (!has_exit)  //提示玩家还没放置出口
					{
						strcpy_s(menu_buffer[1], 71, "@   !!!!!!!The EXIT have not been set up yet!!!!!!!                   ");
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'w':  //光标上移
				{
					if (cursorPos[0] > 4)  //光标有上移余量
					{
						//读取原先的内容
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //零表示空
							currentContentChar = ' ';
							break;
						case 1:  //一表示砖块
							currentContentChar = '1';
							break;
						case 2:  //二表示入口
							currentContentChar = 's';
							break;
						case 3:  //三表示出口
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //当前位置设为原先内容
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = '^';  //光标移动至上一个位置
						cursorPos[0]--;

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'd':  //光标右移
				{
					if (cursorPos[1] < 17) //光标有右移余量
					{
						//读取原先的内容
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //零表示空
							currentContentChar = ' ';
							break;
						case 1:  //一表示砖块
							currentContentChar = '1';
							break;
						case 2:  //二表示入口
							currentContentChar = 's';
							break;
						case 3:  //三表示出口
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //当前位置设为原先内容
						menu_buffer[cursorPos[0]][cursorPos[1] + 1] = '^';
						cursorPos[1]++;
						//保存光标移动后四个方向上的内容, 防止光标移动后原先内容被覆盖

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 's':  //光标下移
				{
					if (cursorPos[0] < 18)  //光标有下移余量
					{
						//读取原先的内容
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //零表示空
							currentContentChar = ' ';
							break;
						case 1:  //一表示砖块
							currentContentChar = '1';
							break;
						case 2:  //二表示入口
							currentContentChar = 's';
							break;
						case 3:  //三表示出口
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //当前位置设为原先内容
						menu_buffer[cursorPos[0] + 1][cursorPos[1]] = '^';
						cursorPos[0]++;

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'a':  //光标左移
				{
					if (cursorPos[1] > 3)  //光标有左移余量
					{
						//读取原先的内容
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //零表示空
							currentContentChar = ' ';
							break;
						case 1:  //一表示砖块
							currentContentChar = '1';
							break;
						case 2:  //二表示入口
							currentContentChar = 's';
							break;
						case 3:  //三表示出口
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //当前位置设为原先内容
						menu_buffer[cursorPos[0]][cursorPos[1] - 1] = '^';
						cursorPos[1]--;

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case ' ':  //按下空格放置砖块
				{
					//如果指针所指当前位置没有砖块则可以放
					if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == ' ')
					{
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = '1';
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 1);  //迷宫数组对应地方设为1
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'b':  //删除光标所指向的砖块
				{
					if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] != ' ')
					{
						if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == 's')
						{
							has_entrance = false;
						}
						if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == 'e')
						{
							has_exit = false;
						}
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = ' ';
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 0);  //删除迷宫数组对应地方
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'i':  //设置迷宫入口
				{
					if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == ' ' && !has_entrance)
					{
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = 's';
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 2);
						has_entrance = true;
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (has_entrance)  //防止玩家重复设置入口
					{
						strcpy_s(menu_buffer[1], 69, "@   !!!!!!!You have already designed the ENTRANCE to the maze!!!!!!!");
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'o':  //设置迷宫出口
				{
					if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == ' ' && !has_exit)
					{
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = 'e';
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 3);
						has_exit = true;
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (has_exit)  //防止玩家重复设置出口
					{
						strcpy_s(menu_buffer[1], 65, "@   !!!!!!!You have already designed the EXIT to the maze!!!!!!!");
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'm':  //停止设计返回主界面
				{
					end_design = true;
					action = back_to_start_menu;
				}
				break;
				}
			}
		}
	}
#pragma endregion
	break;

	case play_menu:  //地图选择菜单处理用户输入
#pragma region playMenuReceiveAction
	{
		fstream levelData("mazelevel.data", ios::in);  //读取地图信息文件
		vector<string> mazeLevelNames;
		string name;
		while (!levelData.eof())
		{
			levelData >> name;
			if (levelData.fail())
			{
				break;
			}
			mazeLevelNames.push_back(name);
		}
		levelData.close();

		//若没有地图数据则返回主菜单
		if (mazeLevelNames.size() == 0)
		{
			cout << "About to return to the start menu..." << endl;
			for (int i = 0; i < 35; i++)
			{
				Sleep(200);
				cout << '.';
			}
			return back_to_start_menu;
		}

		int cursorPos[2] = { 4, 6 };  //光标初始位置
		string currentLevel = mazeLevelNames[0];  //光标当前指向的地图

		bool end_select = false;
		while (!end_select)
		{
			if (_kbhit())
			{
				char input = _getch();
				switch (input)
				{
				case 'w':  //光标上移
				{
					if (cursorPos[0] > 4)  //光标有上移余量的时候
					{
						menu_buffer[cursorPos[0]][cursorPos[1]] = ' ';
						menu_buffer[cursorPos[0] - 2][cursorPos[1]] = '^';
						cursorPos[0] -= 2;
						//更新当前光标指向的关卡信息
						currentLevel = mazeLevelNames[((int)(cursorPos[0] - 4) / 2)];

						//加载当前关卡的地图俯视图
						fstream currentlevelData(currentLevel + ".maze", ios::in);
						if (currentlevelData.fail())
						{
							exit(0);
						}
						for (int i = 3; i <= 17; i++)
						{
							string mazeline;
							currentlevelData >> mazeline;
							for (int j = 51; j <= 65; j++)
							{
								menu_buffer[i][j] = MazeNumToChar(mazeline[j - 51]);
							}
						}
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 's':  //光标下移
				{
					if (cursorPos[0] < 2 * mazeLevelNames.size() + 2)  //光标有下移余量的时候
					{
						menu_buffer[cursorPos[0]][cursorPos[1]] = ' ';
						menu_buffer[cursorPos[0] + 2][cursorPos[1]] = '^';
						cursorPos[0] += 2;
						//更新当前光标指向的关卡信息
						currentLevel = mazeLevelNames[((int)(cursorPos[0] - 4) / 2)];

						//加载当前关卡的地图俯视图
						fstream currentlevelData(currentLevel + ".maze", ios::in);
						if (currentlevelData.fail())
						{
							exit(0);
						}
						for (int i = 3; i <= 17; i++)
						{
							string mazeline;
							currentlevelData >> mazeline;
							for (int j = 51; j <= 65; j++)
							{
								menu_buffer[i][j] = MazeNumToChar(mazeline[j - 51]);
							}
						}
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (cursorPos[0] == 2 * mazeLevelNames.size() + 2)  //最后一行返回主菜单
					{
						menu_buffer[cursorPos[0]][cursorPos[1]] = ' ';
						menu_buffer[cursorPos[0] + 2][cursorPos[1]] = '^';
						cursorPos[0] += 2;
						currentLevel = "back";

						//清空地图俯视图
						for (int i = 3; i <= 17; i++)
						{
							for (int j = 51; j <= 65; j++)
							{
								menu_buffer[i][j] = ' ';
							}
						}
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case ' ':  //确认
				{
					if (currentLevel == "back")  //返回主菜单
					{
						action = back_to_start_menu;
						end_select = true;
					}
					//...
					else  //选择进入关卡
					{
						GamePlay::currentLevel = currentLevel;
						action = play_game;
						end_select = true;
						system("cls");
						string loading = "Maze is loading....................";
						for (int i = 0; i < 5; i++)
						{
							cout << endl;
						}
						cout << "                    ";
						for (int i = 0; i < loading.length(); i++)
						{
							cout << loading[i];
							Sleep(50);
						}
					}
				}
				break;

				case 'd':  //删除地图
				{
					if (currentLevel != "back")
					{
						for (int i = 0; i < mazeLevelNames.size(); i++)
						{
							if (mazeLevelNames[i] == currentLevel)
							{
								mazeLevelNames.erase(mazeLevelNames.begin() + i);
								break;
							}
						}
						levelData.open("mazelevel.data", ios::out);
						for (int i = 0; i < mazeLevelNames.size(); i++)
						{
							levelData << mazeLevelNames[i] << endl;
						}
						levelData.close();

						if (mazeLevelNames.size() == 0)
						{
							system("cls");
							for (int i = 0; i < 5; i++)
							{
								cout << endl;
							}
							//提示没有迷宫关卡
							cout << "               There are no levels yet, hurry up and design one :D                                 " << endl;;
							system("pause");
							action = back_to_start_menu;
							end_select = true;
							//strcpy_s(menu_buffer[12], 100, "                       Press 'm' to return to the start menu                                       ");
							return action;
						}

						for (int i = 0; i < height; i++)
						{
							for (int j = 0; j < width; j++)
							{
								menu_buffer[i][j] = ' ';
							}
						}

						//最上方边
						for (int i = 0; i < width; i++)
						{
							menu_buffer[0][i] = '@';
						}
						//旁边边框
						for (int i = 1; i <= 18; i++)
						{
							menu_buffer[i][0] = '@';
							//menu_buffer[i][99] = '@';
						}
						//底边
						for (int i = 0; i < width; i++)
						{
							menu_buffer[19][i] = '@';
						}

						strcpy_s(menu_buffer[2], 100, "@           Please select a level :D                                                               ");  //第一行标语
						strcpy_s(menu_buffer[4], 100, "@                                                                   Press 'w s' to move the cursor ");
						strcpy_s(menu_buffer[6], 100, "@                                                                   Press 'space' to confirm    :D ");
						strcpy_s(menu_buffer[8], 100, "@                                                                   Press 'd' to delete maze       ");
						strcpy_s(menu_buffer[10], 100, "@                                                                   If you want to quit playing    ");
						strcpy_s(menu_buffer[11], 100, "@                                                                   press 'b'                   :D ");
						
						string menuline;
						int i;
						for (i = 1; i <= mazeLevelNames.size(); i++)  //加载地图信息
						{
							menuline = "@       " + mazeLevelNames[i - 1];
							strcpy_s(menu_buffer[2 * i + 2], 9 + mazeLevelNames[i - 1].length(), menuline.c_str());
							for (int j = 6; j <= 99; j++)  //将空字符转化为空格
							{
								if (menu_buffer[2 * i + 2][j] == '\0')
								{
									menu_buffer[2 * i + 2][j] = ' ';
									break;
								}
							}
							//}
						}
						//最后一行显示返回主菜单
						strcpy_s(menu_buffer[2 * i + 2], 13, "@       back");
						for (int j = 6; j <= 99; j++)  //将空字符转化为空格
						{
							if (menu_buffer[2 * i + 2][j] == '\0')
							{
								menu_buffer[2 * i + 2][j] = ' ';
								break;
							}
						}

						menu_buffer[4][6] = '^';  //光标，用于选择关卡
						cursorPos[0] = 4;
						currentLevel = mazeLevelNames[0];

						//地图概览边框
						for (int i = 50; i <= 66; i++)  //最上方边
						{
							menu_buffer[2][i] = '#';
						}
						for (int i = 3; i <= 17; i++)  //两侧边框
						{
							menu_buffer[i][50] = '#';
							menu_buffer[i][66] = '#';
						}
						for (int i = 50; i <= 66; i++)
						{
							menu_buffer[18][i] = '#';
						}

						fstream level1(mazeLevelNames[0] + ".maze", ios::in);
						if (level1.fail())
						{
							exit(0);
						}
						for (int i = 3; i <= 17; i++)
						{
							string mazeline;
							level1 >> mazeline;
							for (int j = 51; j <= 65; j++)
							{
								menu_buffer[i][j] = MazeNumToChar(mazeline[j - 51]);
							}
						}
						level1.close();
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;
				}
			}
		}
	}
#pragma endregion
	break;
	}

	return action;
}

/// <summary>
/// 模拟按下f11，界面全屏
/// </summary>
void Menu::FullScreen()
{
	keybd_event(VK_F11, 0, 0, 0);
	keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
	return;
}

/// <summary>
/// 控制菜单动画
/// </summary>
/// <param name="input">玩家输入的按键</param>
void Menu::ShowAnimation(char input)
{
	switch (input)
	{
	case 'a':
		//按下a的动画 a那一行滚动
		StartPlayAnimation();
		break;
	case 'd':
		//d那一行滚动
		StartDesignAnimation();
		break;
	}
	return;
}

void Menu::StartPlayAnimation()
{
	for (int k = 0; k < width - 65; k++)
	{
		fputs("\033[0;0H", stdout);
		for (int i = width; i >= 3; i--)
		{
			menu_buffer[7][i] = menu_buffer[7][i - 3];
		}
		display();
	}
}

void Menu::StartDesignAnimation()
{
	for (int k = 0; k < width - 65; k++)
	{
		fputs("\033[0;0H", stdout);
		for (int i = width; i >= 3; i--)
		{
			menu_buffer[9][i] = menu_buffer[9][i - 3];
		}
		display();
	}
}

void Menu::ResetStartMenu()
{
	//最上方边
	for (int i = 0; i < width; i++)
	{
		menu_buffer[0][i] = '@';
	}
	//写入中间标语内容
	int j;
	for (j = 1; j < (height - 5) / 2; j++)
	{
		menu_buffer[j][0] = '@';
		int i;
		for (i = 1; i < width - 1; i++)
		{
			menu_buffer[j][i] = ' ';
		}
		menu_buffer[j][i] = '@';
	}
	
	strcpy_s(menu_buffer[7], 100,  "   #     #     #     #####   #####  |   &&&&    &&&        1.Press A to play                       ");
	strcpy_s(menu_buffer[8], 100,  "   ##   ##    # #       #    #      |       &   &  &                                               ");
	strcpy_s(menu_buffer[9], 100,  "   # # # #   #   #     #     #####  |   &&&&&   &   &      2.Press D to design maze                ");
	strcpy_s(menu_buffer[10], 100, "   #  #  #   #####    #      #      |       &   &  &                                               ");
	strcpy_s(menu_buffer[11], 100, "   #  #  #   #   #   #####   #####  |   &&&&    &&&        3.Press E to exit                       ");

	j = j + 5;
	for (; j < height - 1; j++)
	{
		menu_buffer[j][0] = '@';
		int i;
		for (i = 1; i < width - 1; i++)
		{
			menu_buffer[j][i] = ' ';
		}
		menu_buffer[j][i] = '@';
	}
	//底边
	for (int i = 0; i < width; i++)
	{
		menu_buffer[j][i] = '@';
	}
}