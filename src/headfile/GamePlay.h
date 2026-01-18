#pragma once
#include <vector>
#include <string>
#include "vec2.h"
enum PlayerMoveState
{
	noMove = 0,
	up = 1,
	down = 2
};
using namespace std;
class GamePlay
{
private:
	int** map;  //迷宫地图信息
	int start[2] = {0, 0};  //地图起点
	int end[2] = {0, 0};  //地图终点


	//vec2* pos;  //玩家位置
	//vec2* dir;  //玩家指向方向
	//vec2* plane;  //相机平面向量
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed = 0.1;  //玩家移动速度
	double rotSpeed = 0.1; //玩家转向速度
	PlayerMoveState moveState = noMove;  //玩家当前运动状态，用于穿墙后复位

	vector<vec2> wall;  //储存墙面信息

	char* canvas;  //幕布
	int screenWidth = 200;  //屏幕显示宽度
	int screenHeight = 50;
	//char colorChr = '@';  //画线字符
	//double posX; //玩家位置x坐标
	//double posY; //玩家位置y坐标
	//double dirX = -1;  //玩家指向方向x坐标
	//double dirY = 0;  //玩家指向方向y坐标
public:
	static string currentLevel;  //迷宫关卡地图信息
	GamePlay();
	bool Update();  //每帧执行检测游戏是否结束
};


