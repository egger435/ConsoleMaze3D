#pragma once
class MazeDesign
{
private:
	int** maze_buffer;  //迷宫数组缓冲区
	int height;
	int width;
public:
	MazeDesign(int height, int width);
	void SetBuffer(int i, int j, int block);
	int GetBuffer(int i, int j);
	bool Save(string mazeName);  //保存迷宫数据
};

