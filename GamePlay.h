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
	int** map;  //�Թ���ͼ��Ϣ
	int start[2] = {0, 0};  //��ͼ���
	int end[2] = {0, 0};  //��ͼ�յ�


	//vec2* pos;  //���λ��
	//vec2* dir;  //���ָ����
	//vec2* plane;  //���ƽ������
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed = 0.1;  //����ƶ��ٶ�
	double rotSpeed = 0.1; //���ת���ٶ�
	PlayerMoveState moveState = noMove;  //��ҵ�ǰ�˶�״̬�����ڴ�ǽ��λ

	vector<vec2> wall;  //����ǽ����Ϣ

	char* canvas;  //Ļ��
	int screenWidth = 200;  //��Ļ��ʾ���
	int screenHeight = 50;
	//char colorChr = '@';  //�����ַ�
	//double posX; //���λ��x����
	//double posY; //���λ��y����
	//double dirX = -1;  //���ָ����x����
	//double dirY = 0;  //���ָ����y����
public:
	static string currentLevel;  //�Թ��ؿ���ͼ��Ϣ
	GamePlay();
	bool Update();  //ÿִ֡�м����Ϸ�Ƿ����
};


