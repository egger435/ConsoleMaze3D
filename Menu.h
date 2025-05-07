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
	int height;          //�˵��߶�
	int width;           //�˵����
	MenuType menutype;   //�˵�����
	char** menu_buffer;  //�˵�����������
	void StartMenuInitialize();  //��ʼ����˵���ʼ��
	void DesignMenuInitialize(); //��ͼ��Ʋ˵�ҳ���ʼ��
	void PlayMenuInitialize();   //��ʼ��Ϸ�˵�ҳ���ʼ��
	void ShowAnimation(char input);//�˵��ַ������� 
	void StartPlayAnimation();
	void StartDesignAnimation();
public:
	Menu(MenuType menutype);
	void display();
	PlayerAction ReceiveUserAction();
	void FullScreen();
	void ResetStartMenu();  //���ÿ�ʼ�˵�
};

