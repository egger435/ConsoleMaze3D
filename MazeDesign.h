#pragma once
class MazeDesign
{
private:
	int** maze_buffer;  //�Թ����黺����
	int height;
	int width;
public:
	MazeDesign(int height, int width);
	void SetBuffer(int i, int j, int block);
	int GetBuffer(int i, int j);
	bool Save(string mazeName);  //�����Թ�����
};

