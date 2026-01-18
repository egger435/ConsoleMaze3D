#pragma once
#include <iostream>
using namespace std;
enum PlayerAction
{
	none = 0,
	start_play = 1,
	start_design = 2,
	finish_design = 3,
	back_to_start_menu = 4,
	play_game = 5
};
enum MenuType
{
	start_menu = 0,
	design_menu = 1,
	play_menu = 2
};
class Menu
{
private:
	int height;          //菜单高度
	int width;           //菜单宽度
	MenuType menutype;   //菜单类型
	char** menu_buffer;  //菜单缓冲区数组
	void StartMenuInitialize();  //初始界面菜单初始化
	void DesignMenuInitialize(); //地图设计菜单页面初始化
	void PlayMenuInitialize();   //开始游戏菜单页面初始化
	void ShowAnimation(char input);//菜单字符串动画 
	void StartPlayAnimation();
	void StartDesignAnimation();
public:
	Menu(MenuType menutype);
	void display();
	PlayerAction ReceiveUserAction();
	void FullScreen();
	void ResetStartMenu();  //重置开始菜单
};

