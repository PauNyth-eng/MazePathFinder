#include "Maze.h"


Maze::Maze()
{

}
/// <summary>
/// Recursive function internalFindPath, Algorithm used for this problem was A* -> Moving to every possible directions (Up, Down, Right, Left)
/// </summary>
/// <param name="x">Position x</param>
/// <param name="y">Position y</param>
/// <param name="dir">Direction</param>
/// <returns></returns>
bool Maze::internalFindPath(int x, int  y, tuple<int, int> dir)
{
	if (x < 0 || y < 0 || x > sizeX || y > sizeY || maze[x][y] == 1) return false; // Checking border of maze and at the same time checking if path is directed to the wall, if yes return false
	if (maze[x][y] == 3) return true; // Checking exit of the maze

	bool result = false; // Creating boolean valiable to save result of recursive

	// Conditions for next recursives
	if (get<0>(dir) != -1) result |= internalFindPath(x + 1, y, make_tuple(1, 0)); // Moving Up
	if (get<0>(dir) != 1) result |= internalFindPath(x - 1, y, make_tuple(-1, 0)); // Moving Down
	if (get<1>(dir) != -1) result |= internalFindPath(x, y + 1, make_tuple(0, 1)); // Moving Right
	if (get<1>(dir) != 1) result |= internalFindPath(x, y - 1, make_tuple(0, -1)); // Moving Left

	if (result) path.push_back(make_tuple(x, y)); 

	return result;
}
/// <summary>
/// Public function FindPath
/// </summary>
/// <returns>Return if maze has path, calling internalFindPath</returns>
bool Maze::FindPath()
{
	return internalFindPath(this->startX, this->startY, make_tuple(0, 0));
}
/// <summary>
/// Fuction for reading file with data and saving important data to atributes of class
/// </summary>
/// <param name="filename">Name of uploaded file</param>
/// <returns>Return TRUE if file is written correctly otherwise FALSE if one of conditions are met</returns>
bool Maze::ReadFile(string filename)
{
	ifstream mazeFile(filename);
	if (mazeFile.is_open())
	{
		mazeFile >> sizeX; // Reading number from file
		mazeFile >> sizeY; // Reading number from file
		if (sizeX == 0 || sizeY == 0) // Checking if sizeX or sizeY is number
		{
			cout << "Correct your number of rows or column" << endl;
			mazeFile.close();
			return false;
		}
		for (int i = 0; i < sizeX; i++)
		{
			mazeFile.get(value);
			vector<int> helper;
			for (int j = 0; j < sizeY; j++)
			{
				mazeFile.get(value);
				if (value - '0' < 0 || value - '0' > 3) //Checking if value is correctly written in file, bcs We are using just interval <0; 3>
				{
					cout << "Correct your values at maze" << endl;
					return false;
				}
				if (value == '2') // assigning an entrance to the maze
				{ 
					this->startX = i;
					this->startY = j;
				}
				helper.push_back(value - '0');
			}
			maze.push_back(helper);
		}
		if (!is_empty(mazeFile)) // Checking if file is empty, after getting all date byt given rows and columns
		{
			cout << "Your maze isn't valid" << endl;
			return false;
		}
		mazeFile.close();
		return true;
	}

	return false;
}

/// <summary>
/// Function to check if file is empty. Code used from https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
/// </summary>
/// <param name="pFile">taking filestream</param>
/// <returns> Return TRUE if file is empty otherwise FALSE if file is still has date in it</returns>
bool Maze::is_empty(ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

/// <summary>
/// Functions for listing the maze to the console
/// </summary>
void Maze::PrintMaze()
{

	for (int i = 0; i < sizeX; i++)
	{

		for (int j = 0; j < sizeY; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}
}


/// <summary>
/// Functions for entering the path to the maze 
/// </summary>
void Maze::WritePath()
{
	for (auto point : path)
	{
		maze[get<0>(point)][get<1>(point)] = 4;
	}
	maze[startX][startY] = 2;
}

/// <summary>
/// Function, which create new file with correct path in the maze, "solved" added before name
/// </summary>
/// <param name="filename">Name of the uploaded file</param>
/// <returns>Returns TRUE if everything went right, FALSE if file couldn't be opened</returns>
bool Maze::WriteFile(string filename)
{
	ofstream mazeFile("solved" + filename);
	if (mazeFile.is_open())
	{
		for (int i = 0; i < sizeX; i++)
		{
			for (int j = 0; j < sizeY; j++)
			{
				mazeFile << maze[i][j];
			}
			mazeFile << endl;
		}
		mazeFile.close();
		return true;
	}
	return false;
}
