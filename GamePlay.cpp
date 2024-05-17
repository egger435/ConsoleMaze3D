#include <fstream>
#include <stdlib.h>
#include "GamePlay.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
//#include <synchapi.h>
using namespace std;

char MazeNumToChar_(char mazeNum)
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
GamePlay::GamePlay()
{
	map = new int* [17];
	for (int i = 0; i < 17; i++)
	{
		map[i] = new int[17];
	}

	if (currentLevel == "none")
	{
		return;
	}

	//周围围一圈墙，防止后面光线投射报错
	for (int i = 0; i < 17; i++)
	{
		map[0][i] = 1;
	}
	for (int i = 1; i <= 15; i++)
	{
		map[i][0] = 1;
		map[i][16] = 1;
	}
	for (int i = 0; i < 17; i++)
	{
		map[16][i] = 1;
	}

	//打开文件载入地图
	fstream levelData(currentLevel + ".maze", ios::in);
	if (levelData.fail())
	{
		exit(0);
	}
	for (int i = 1; i <= 15; i++)
	{
		string mazeline;
		levelData >> mazeline;
		for (int j = 1; j <= 15; j++)
		{
			map[i][j] = mazeline[j - 1] - 48;
		}
	}

	//确定起点终点位置, 顺便储存墙面信息
	bool findStart = false;
	bool findEnd = false;
	for (int i = 0; i <= 16; i++)
	{
		for (int j = 0; j <= 16; j++)
		{
			if (map[i][j] == 2)
			{
				start[0] = i;
				start[1] = j;
				findStart = true;
			}
			if (map[i][j] == 3)
			{
				end[0] = i;
				end[1] = j;
				findEnd = true;
			}
			if (map[i][j] == 1)
			{
				vec2 wallPos(i, j);
				wall.push_back(wallPos);
			}
		}
	}
	/*pos = new vec2(start[0], start[1]);
	dir = new vec2(-1, 0);
	plane = new vec2(0, 0.66);*/

	posX = start[0] + 0.5;
	posY = start[1] + 0.5;
	dirX = -1;
	dirY = 0;
	planeX = 0;
	planeY = 0.66;

	canvas = new char[screenHeight * screenWidth];  //初始化幕布

	//根据控制台大小调整屏幕显示大小
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	screenWidth = consoleWidth - 10;
	screenHeight = consoleHeight - 11;
}

bool GamePlay::Update()
{
	bool game_over = false;
	/*double oldDirX;
	double oldPlaneX;*/
	/*double newdirX, newdirY;
	double newplaneX, newplaneY;*/
	double oldDirX;
	double oldPlaneX;
	
	
	//raycasting
	for (int c = 0; c < screenWidth; c++)
	{
		// calculate ray position and direction
		double cameraX = 2 * c / (double)(screenWidth - 1) - 1; ////x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		// which box of the map we are in
		int mapX = int(posX);
		int mapY = int(posY);

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);

		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?
		// calculate step and initial sideDist

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (mapX < 0 || mapX > 14 || mapY < 0 || mapY > 14)
			{
				hit = 1;
				break;
			}
			if (map[mapX][mapY] == 1 || map[mapX][mapY] == 3)
				hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		if (abs(perpWallDist) < 1e-5)
		{
			perpWallDist = 1e-5;
		}
		// calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);
		// draw the screen to the screen buffer matrix
		int drawStart = (screenHeight - lineHeight) / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = (screenHeight + lineHeight) / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		// choose different color charactor
		char colorChr;
		colorChr = '@';
		
		// give x and y sides different brightness
		if (side == 1)
		{
			colorChr = '+';
		}

		if (mapX < 0) mapX = 0;
		if (mapX > 14) mapX = 14;
		if (mapY < 0) mapY = 0;
		if (mapY > 14) mapY = 14;
		//提示终点位置
		if (map[mapX][mapY] == 3)
		{
			colorChr = '!';
		}

		// draw line
		for (int r = 0; r < drawStart; r++)
		{
			canvas[r * screenWidth + c] = ' ';
		}
		for (int r = drawStart; r < drawEnd; r++)
		{
			canvas[r * screenWidth + c] = colorChr;
		}
		for (int r = drawEnd; r < screenHeight; r++)
		{
			canvas[r * screenWidth + c] = '.';
		}
	}
	//绘制一帧输出
	char* frame = new char[screenHeight * screenWidth];
	for (int r = 0; r < screenHeight - 1; r++)
	{
		frame[screenWidth * r + screenWidth - 1] = '\n';
	}
	frame[screenWidth * screenHeight - 1] = '\0';
	for (int r = 0; r < screenHeight; r++)
	{
		for (int c = 0; c < screenWidth - 1; c++)
		{
			frame[r * screenWidth + c] = canvas[r * screenWidth + c];
		}
	}
	fputs(frame, stdout);
	delete[] frame;
	//清屏
	for (int r = 0; r < screenHeight; r++)
	{
		for (int c = 0; c < screenWidth; c++)
		{
			canvas[r * screenWidth + c] = ' ';
		}
	}
	fputs("\033[0;0H", stdout);

	//判断玩家位置，检测是否到达终点
	if ((end[0] < posX && posX < end[0] + 1) && (end[1] < posY && posY < end[1] + 1))
	{
		game_over = true;
	}

	//判断玩家是否在墙内(飞舞式碰撞检测)
	for (int i = 0; i < wall.size(); i++)
	{
		if ((wall[i].GetX() < posX && posX < wall[i].GetX() + 1) &&
			(wall[i].GetY() < posY && posY < wall[i].GetY() + 1))  //在墙内求玩家不要穿墙/(ㄒoㄒ)/~~
		{
			system("cls");
			string qiu_ni_la = "真不会写碰撞检测/(ㄒoㄒ)/~~，求求你不要穿墙辣。。。";
			for (int i = 0; i < 5; i++)
			{
				cout << endl;
			}
			cout << "                   ";
			for (int i = 0; i < qiu_ni_la.length(); i++)
			{
				cout << qiu_ni_la[i];
				Sleep(50);
			}
			Sleep(500);
			string bao_cuo_la = "再穿墙就要报错辣/(ㄒoㄒ)/~~";
			cout << endl;
			cout << "                   ";
			for (int i = 0; i < bao_cuo_la.length(); i++)
			{
				cout << bao_cuo_la[i];
				Sleep(50);
			}
			cout << endl;
			system("pause");
			//根据移动状态复位
			if (moveState == up)
			{
				posX = posX - dirX * moveSpeed;
				posY = posY - dirY * moveSpeed;
			}
			else if (moveState == down)
			{
				posX = posX + dirX * moveSpeed;
				posY = posY + dirY * moveSpeed;
			}
		}
	}

	if (_kbhit())
	{
		int input = _getch();
		switch (input)
		{
		case 'w':
			posX += dirX * moveSpeed;
			posY += dirY * moveSpeed;
			moveState = up;
			break;
		case 's':
			posX -= dirX * moveSpeed;
			posY -= dirY * moveSpeed;
			moveState = down;
			break;
		case 'd':
			oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
			break;
		case 'a':
			oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
			break;
		case 'b':
			game_over = true;
			return game_over;
		}
	}

	if (game_over)
	{
		system("cls");
		string congratulation1 = "Coooooooooooooooooongratulations!!!";
		string congratulation2 = "You successfully find the exit!!!!";
		for (int i = 0; i < 5; i++)
		{
			cout << endl;
		}
		cout << "                   ";
		for (int i = 0; i < congratulation1.length(); i++)
		{
			cout << congratulation1[i];
			Sleep(50);
		}
		Sleep(500);
		for (int i = 0; i < congratulation2.length(); i++)
		{
			cout << congratulation2[i];
			Sleep(50);
		}
		cout << endl;
		string back = "About to return to Start Menu...";
		cout << "                   ";
		for (int i = 0; i < back.length(); i++)
		{
			cout << back[i];
			Sleep(50);
		}
		system("pause");
	}
	return game_over;
}
