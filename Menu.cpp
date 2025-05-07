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

	//��ʼ���˵�������
	menu_buffer = new char* [height + 2];
	for (int i = 0; i < height; i++)
	{
		menu_buffer[i] = new char[width + 2];
	}

	//���˵����������ݳ�ʼ��Ϊ��
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			menu_buffer[i][j] = ' ';
		}
	}

	//���ݲ�ͬ�˵����ͳ�ʼ��
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
	//���Ϸ���
	for (int i = 0; i < width; i++)
	{
		menu_buffer[0][i] = '@';
	}
	//д���м��������
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
	//�ױ�
	for (int i = 0; i < width; i++)
	{
		menu_buffer[j][i] = '@';
	}
}

void Menu::DesignMenuInitialize()
{
	//��ȡ��ͼ���ݣ��������ﵽ6������ʾ�����ȥ�棬�������
	//Ŀ����Ϊ�����Ƶ�ͼ��6������Ϊ��Ϸ�ؿ�ѡ���ϲ�����Ʒ�ҳ
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
		string haha = "ʵ�����Ҿ�����������ͼѡ��ҳ��ķ�ҳ���ܣ�hhh";
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

	//���Ϸ���
	for (int i = 0; i < width - 1; i++)
	{
		menu_buffer[0][i] = '@';
	}

	strcpy_s(menu_buffer[1], 100, "@   Please design your maze below :D                                                               ");  //��һ�б���
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
	menu_buffer[i][3] = '^';  //��ʾ��꣬��ʼλ��4��3
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

	//��ͼ�����ʾ
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
/// ���Թ��ļ��е����ִ���ת��Ϊ�˵�����ʾ���ַ���
/// </summary>
/// <param name="mazeNum">�Թ��ļ��е��������</param>
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
	fstream levelData("mazelevel.data", ios::in);  //��ȡ�Թ��ؿ��б���Ϣ
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

	//���Ϸ���
	for (int i = 0; i < width; i++)
	{
		menu_buffer[0][i] = '@';
	}
	//�Ա߱߿�
	for (int i = 1; i <= 18; i++)
	{
		menu_buffer[i][0] = '@';
		//menu_buffer[i][99] = '@';
	}
	//�ױ�
	for (int i = 0; i < width; i++)
	{
		menu_buffer[19][i] = '@';
	}

	if (mazeLevelNames.size() == 0)
	{
		//��ʾû���Թ��ؿ�
		strcpy_s(menu_buffer[10], 100, "               There are no levels yet, hurry up and design one :D                                 ");
		//strcpy_s(menu_buffer[12], 100, "                       Press 'm' to return to the start menu                                       ");
		return;
	}

	strcpy_s(menu_buffer[2], 100, "@           Please select a level :D                                                               ");  //��һ�б���
	strcpy_s(menu_buffer[4], 100, "@                                                                   Press 'w s' to move the cursor ");
	strcpy_s(menu_buffer[6], 100, "@                                                                   Press 'space' to confirm    :D ");
	strcpy_s(menu_buffer[8], 100, "@                                                                   Press 'd' to delete maze       ");
	strcpy_s(menu_buffer[10],100, "@                                                                   If you want to quit playing    ");
	strcpy_s(menu_buffer[11],100, "@                                                                   press 'b'                   :D ");
	string menuline;
	int i;
	for (i = 1; i <= mazeLevelNames.size(); i++)  //���ص�ͼ��Ϣ
	{
		//if (2 * i + 2 >= 18)  //�����ͼ̫�࣬һҳ��ʾ���꣬��Ҫ��ʾ����һҳ
		//{
		//	strcpy_s(menu_buffer[18], 18, "@       next page");
		//	for (int j = 6; j <= 99; j++)  //�����ַ�ת��Ϊ�ո�
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
		for (int j = 6; j <= 99; j++)  //�����ַ�ת��Ϊ�ո�
		{
			if (menu_buffer[2 * i + 2][j] == '\0')
			{
				menu_buffer[2 * i + 2][j] = ' ';
				break;
			}
		}
		//}
	}
	//���һ����ʾ�������˵�
	strcpy_s(menu_buffer[2 * i + 2], 13, "@       back");
	for (int j = 6; j <= 99; j++)  //�����ַ�ת��Ϊ�ո�
	{
		if (menu_buffer[2 * i + 2][j] == '\0')
		{
			menu_buffer[2 * i + 2][j] = ' ';
			break;
		}
	}
	
	menu_buffer[4][6] = '^';  //��꣬����ѡ��ؿ�

	//��ͼ�����߿�
	for (int i = 50; i <= 66; i++)  //���Ϸ���
	{
		menu_buffer[2][i] = '#';
	}
	for (int i = 3; i <= 17; i++)  //����߿�
	{
		menu_buffer[i][50] = '#';
		menu_buffer[i][66] = '#';
	}
	for (int i = 50; i <= 66; i++)
	{
		menu_buffer[18][i] = '#';
	}

	//���ص�һ�صĵ�ͼ����ͼ
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
/// ��ʾ������������
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
/// ���ݲ�ͬ�˵�ҳ������û�����
/// </summary>
PlayerAction Menu::ReceiveUserAction()
{
	PlayerAction action = none;
	switch (this->menutype)
	{
	case start_menu:  //�ڿ�ʼ�˵�ҳ�洦���û�����
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
					action = start_play;  //��������ΪΪplay
					break;
				case 'd':
					ShowAnimation(input);
					cout << "hit D, design" << endl;
					flag = false;
					action = start_design;  //��������ΪΪdesign
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

	case design_menu:  //��ͼ��Ʋ˵������û�����
#pragma region designMenuReceiveAction
	{
		//��ȡ��ͼ���ݣ��������ﵽ6������ʾ�����ȥ�棬�������
		//Ŀ����Ϊ�����Ƶ�ͼ��6������Ϊ��Ϸ�ؿ�ѡ���ϲ�����Ʒ�ҳ
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

		MazeDesign mazedesign(16, 15);//ʵ�����Թ���ƴ�СΪ15*15��Ϊ��ֹ���д��16
		int cursorPos[2] = { 4, 3 };  //���ĳ�ʼ����4��3, ��Ӧ�Թ������ʼλ��0��0
		//pos[0]�У�pos[1]��
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
				case 'p':  //��Ұ���p�Թ�������
				{
					if (has_entrance && has_exit)  //����Թ��Ѿ�������ںͳ�������Ա���
					{
						//��ʾ����Ƿ�ȷ��������ƺõ��Թ�
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

									//��ȡ��ͼ���ݣ��жϵ�ͼ���Ƿ��ظ�  mazelevel.data ����������е�ͼ��������
									fstream mazeLevelsFile("mazelevel.data", ios::in);
									if (mazeLevelsFile.fail())
									{
										cout << "can not find mazelevel.data" << endl;
										exit(0);
									}
									vector<string> mazeLevelNames;
									string name;
									while (!mazeLevelsFile.eof())   //�����е�ͼ�������ݴ�����mazeLevelNames��
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
									bool has_duplicate = true;  //��Ĭ�ϴ����ظ��ĵ�ͼ
									while (has_duplicate)
									{
										cin >> mazeName;  //�����ͼ����
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
										if (i == mazeLevelNames.size())  //���ɹ��������򲻴����ظ���ͼ
										{
											has_duplicate = false;
										}
									}

									if (mazedesign.Save(mazeName))  //�ɹ�����󽫵�ͼ���ּ�¼��mazelevelsfile��mazelevel.data����
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
									strcpy_s(menu_buffer[1], 100, "@   Please design your maze below :D                                                               ");  //��һ�б���
									fputs("\033[0;0H", stdout);
									display();
									break;
								}
							}
						}
					}
					else if (!has_entrance && !has_exit)  //��ʾ�����ڳ��ڶ���û����
					{
						strcpy_s(menu_buffer[1], 79, "@   !!!!!!!BOTH the ENTRANCE and EXIT have not been set up yet!!!!!!!         ");
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (!has_entrance)  //��ʾ��һ�û�������
					{
						strcpy_s(menu_buffer[1], 71, "@   !!!!!!!The ENTRANCE have not been set up yet!!!!!!!               ");
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (!has_exit)  //��ʾ��һ�û���ó���
					{
						strcpy_s(menu_buffer[1], 71, "@   !!!!!!!The EXIT have not been set up yet!!!!!!!                   ");
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'w':  //�������
				{
					if (cursorPos[0] > 4)  //�������������
					{
						//��ȡԭ�ȵ�����
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //���ʾ��
							currentContentChar = ' ';
							break;
						case 1:  //һ��ʾש��
							currentContentChar = '1';
							break;
						case 2:  //����ʾ���
							currentContentChar = 's';
							break;
						case 3:  //����ʾ����
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //��ǰλ����Ϊԭ������
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = '^';  //����ƶ�����һ��λ��
						cursorPos[0]--;

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'd':  //�������
				{
					if (cursorPos[1] < 17) //�������������
					{
						//��ȡԭ�ȵ�����
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //���ʾ��
							currentContentChar = ' ';
							break;
						case 1:  //һ��ʾש��
							currentContentChar = '1';
							break;
						case 2:  //����ʾ���
							currentContentChar = 's';
							break;
						case 3:  //����ʾ����
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //��ǰλ����Ϊԭ������
						menu_buffer[cursorPos[0]][cursorPos[1] + 1] = '^';
						cursorPos[1]++;
						//�������ƶ����ĸ������ϵ�����, ��ֹ����ƶ���ԭ�����ݱ�����

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 's':  //�������
				{
					if (cursorPos[0] < 18)  //�������������
					{
						//��ȡԭ�ȵ�����
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //���ʾ��
							currentContentChar = ' ';
							break;
						case 1:  //һ��ʾש��
							currentContentChar = '1';
							break;
						case 2:  //����ʾ���
							currentContentChar = 's';
							break;
						case 3:  //����ʾ����
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //��ǰλ����Ϊԭ������
						menu_buffer[cursorPos[0] + 1][cursorPos[1]] = '^';
						cursorPos[0]++;

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'a':  //�������
				{
					if (cursorPos[1] > 3)  //�������������
					{
						//��ȡԭ�ȵ�����
						int currentContent = mazedesign.GetBuffer(cursorPos[0] - 3, cursorPos[1] - 3);
						char currentContentChar = ' ';
						switch (currentContent)
						{
						case 0:  //���ʾ��
							currentContentChar = ' ';
							break;
						case 1:  //һ��ʾש��
							currentContentChar = '1';
							break;
						case 2:  //����ʾ���
							currentContentChar = 's';
							break;
						case 3:  //����ʾ����
							currentContentChar = 'e';
							break;
						}

						menu_buffer[cursorPos[0]][cursorPos[1]] = currentContentChar;  //��ǰλ����Ϊԭ������
						menu_buffer[cursorPos[0]][cursorPos[1] - 1] = '^';
						cursorPos[1]--;

						//...
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case ' ':  //���¿ո����ש��
				{
					//���ָ����ָ��ǰλ��û��ש������Է�
					if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == ' ')
					{
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = '1';
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 1);  //�Թ������Ӧ�ط���Ϊ1
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'b':  //ɾ�������ָ���ש��
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
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 0);  //ɾ���Թ������Ӧ�ط�
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'i':  //�����Թ����
				{
					if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == ' ' && !has_entrance)
					{
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = 's';
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 2);
						has_entrance = true;
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (has_entrance)  //��ֹ����ظ��������
					{
						strcpy_s(menu_buffer[1], 69, "@   !!!!!!!You have already designed the ENTRANCE to the maze!!!!!!!");
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'o':  //�����Թ�����
				{
					if (menu_buffer[cursorPos[0] - 1][cursorPos[1]] == ' ' && !has_exit)
					{
						menu_buffer[cursorPos[0] - 1][cursorPos[1]] = 'e';
						mazedesign.SetBuffer(cursorPos[0] - 4, cursorPos[1] - 3, 3);
						has_exit = true;
						fputs("\033[0;0H", stdout);
						display();
					}
					else if (has_exit)  //��ֹ����ظ����ó���
					{
						strcpy_s(menu_buffer[1], 65, "@   !!!!!!!You have already designed the EXIT to the maze!!!!!!!");
						fputs("\033[0;0H", stdout);
						display();
					}
				}
				break;

				case 'm':  //ֹͣ��Ʒ���������
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

	case play_menu:  //��ͼѡ��˵������û�����
#pragma region playMenuReceiveAction
	{
		fstream levelData("mazelevel.data", ios::in);  //��ȡ��ͼ��Ϣ�ļ�
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

		//��û�е�ͼ�����򷵻����˵�
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

		int cursorPos[2] = { 4, 6 };  //����ʼλ��
		string currentLevel = mazeLevelNames[0];  //��굱ǰָ��ĵ�ͼ

		bool end_select = false;
		while (!end_select)
		{
			if (_kbhit())
			{
				char input = _getch();
				switch (input)
				{
				case 'w':  //�������
				{
					if (cursorPos[0] > 4)  //���������������ʱ��
					{
						menu_buffer[cursorPos[0]][cursorPos[1]] = ' ';
						menu_buffer[cursorPos[0] - 2][cursorPos[1]] = '^';
						cursorPos[0] -= 2;
						//���µ�ǰ���ָ��Ĺؿ���Ϣ
						currentLevel = mazeLevelNames[((int)(cursorPos[0] - 4) / 2)];

						//���ص�ǰ�ؿ��ĵ�ͼ����ͼ
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

				case 's':  //�������
				{
					if (cursorPos[0] < 2 * mazeLevelNames.size() + 2)  //���������������ʱ��
					{
						menu_buffer[cursorPos[0]][cursorPos[1]] = ' ';
						menu_buffer[cursorPos[0] + 2][cursorPos[1]] = '^';
						cursorPos[0] += 2;
						//���µ�ǰ���ָ��Ĺؿ���Ϣ
						currentLevel = mazeLevelNames[((int)(cursorPos[0] - 4) / 2)];

						//���ص�ǰ�ؿ��ĵ�ͼ����ͼ
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
					else if (cursorPos[0] == 2 * mazeLevelNames.size() + 2)  //���һ�з������˵�
					{
						menu_buffer[cursorPos[0]][cursorPos[1]] = ' ';
						menu_buffer[cursorPos[0] + 2][cursorPos[1]] = '^';
						cursorPos[0] += 2;
						currentLevel = "back";

						//��յ�ͼ����ͼ
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

				case ' ':  //ȷ��
				{
					if (currentLevel == "back")  //�������˵�
					{
						action = back_to_start_menu;
						end_select = true;
					}
					//...
					else  //ѡ�����ؿ�
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

				case 'd':  //ɾ����ͼ
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
							//��ʾû���Թ��ؿ�
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

						//���Ϸ���
						for (int i = 0; i < width; i++)
						{
							menu_buffer[0][i] = '@';
						}
						//�Ա߱߿�
						for (int i = 1; i <= 18; i++)
						{
							menu_buffer[i][0] = '@';
							//menu_buffer[i][99] = '@';
						}
						//�ױ�
						for (int i = 0; i < width; i++)
						{
							menu_buffer[19][i] = '@';
						}

						strcpy_s(menu_buffer[2], 100, "@           Please select a level :D                                                               ");  //��һ�б���
						strcpy_s(menu_buffer[4], 100, "@                                                                   Press 'w s' to move the cursor ");
						strcpy_s(menu_buffer[6], 100, "@                                                                   Press 'space' to confirm    :D ");
						strcpy_s(menu_buffer[8], 100, "@                                                                   Press 'd' to delete maze       ");
						strcpy_s(menu_buffer[10], 100, "@                                                                   If you want to quit playing    ");
						strcpy_s(menu_buffer[11], 100, "@                                                                   press 'b'                   :D ");
						
						string menuline;
						int i;
						for (i = 1; i <= mazeLevelNames.size(); i++)  //���ص�ͼ��Ϣ
						{
							menuline = "@       " + mazeLevelNames[i - 1];
							strcpy_s(menu_buffer[2 * i + 2], 9 + mazeLevelNames[i - 1].length(), menuline.c_str());
							for (int j = 6; j <= 99; j++)  //�����ַ�ת��Ϊ�ո�
							{
								if (menu_buffer[2 * i + 2][j] == '\0')
								{
									menu_buffer[2 * i + 2][j] = ' ';
									break;
								}
							}
							//}
						}
						//���һ����ʾ�������˵�
						strcpy_s(menu_buffer[2 * i + 2], 13, "@       back");
						for (int j = 6; j <= 99; j++)  //�����ַ�ת��Ϊ�ո�
						{
							if (menu_buffer[2 * i + 2][j] == '\0')
							{
								menu_buffer[2 * i + 2][j] = ' ';
								break;
							}
						}

						menu_buffer[4][6] = '^';  //��꣬����ѡ��ؿ�
						cursorPos[0] = 4;
						currentLevel = mazeLevelNames[0];

						//��ͼ�����߿�
						for (int i = 50; i <= 66; i++)  //���Ϸ���
						{
							menu_buffer[2][i] = '#';
						}
						for (int i = 3; i <= 17; i++)  //����߿�
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
/// ģ�ⰴ��f11������ȫ��
/// </summary>
void Menu::FullScreen()
{
	keybd_event(VK_F11, 0, 0, 0);
	keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
	return;
}

/// <summary>
/// ���Ʋ˵�����
/// </summary>
/// <param name="input">�������İ���</param>
void Menu::ShowAnimation(char input)
{
	switch (input)
	{
	case 'a':
		//����a�Ķ��� a��һ�й���
		StartPlayAnimation();
		break;
	case 'd':
		//d��һ�й���
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
	//���Ϸ���
	for (int i = 0; i < width; i++)
	{
		menu_buffer[0][i] = '@';
	}
	//д���м��������
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
	//�ױ�
	for (int i = 0; i < width; i++)
	{
		menu_buffer[j][i] = '@';
	}
}