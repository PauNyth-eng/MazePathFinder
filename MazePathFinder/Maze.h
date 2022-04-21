#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <ctype.h>
using namespace std;

class Maze
{
private:
	vector<vector<int>> maze;
	int startX, startY, sizeX, sizeY;
	vector<int> helper;
	char value;
	vector<tuple<int, int>> path;
	bool internalFindPath(int x, int  y, tuple<int, int> dir);
	bool is_empty(ifstream& pFile);



public:
	Maze();
	bool ReadFile(string filename);
	void PrintMaze();
	bool FindPath();
	void WritePath();
	bool WriteFile(string filename);
};
