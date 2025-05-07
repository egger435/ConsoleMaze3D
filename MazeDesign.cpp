#include <fstream>
#include <string.h>
using namespace std;
#include "MazeDesign.h"
MazeDesign::MazeDesign(int height, int width)
{
	this->height = height;
	this->width = width;
	//�Թ����ݻ�����ȫ����ʼ��Ϊ0
	maze_buffer = new int* [height + 2];
	for (int i = 0; i < height; i++)
	{
		maze_buffer[i] = new int[width + 2];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			maze_buffer[i][j] = 0;
		}
	}
}

/// <summary>
/// �޸��Թ����黺�����е�����
/// </summary>
/// <param name="i">�Թ�����������</param>
/// <param name="j">�Թ�����������</param>
/// <param name="block">Ҫ���ĵ�����</param>
void MazeDesign::SetBuffer(int i, int j, int block)
{
	maze_buffer[i][j] = block;
}

int MazeDesign::GetBuffer(int i, int j)
{
	return maze_buffer[i][j];
}

bool MazeDesign::Save(string mazeName)
{
	bool res = false;
	mazeName += ".maze";  //��Ӻ�׺
	fstream mazefile(mazeName, ios::out);
	for (int i = 0; i < height - 1; i++)
	{
		for (int j = 0; j < width; j++)
		{
			mazefile << maze_buffer[i][j];
		}
		mazefile << endl;
	}
	res = true;
	mazefile.close();
	return res;
}
