#include <iostream>
#include <vector>
#include <fstream>
#include "Maze.h"
using namespace std;







int main(int argc, char* argv[])
{

	auto maze = new Maze();

	if (!maze->ReadFile("maze.txt"))
	{ 
		cout << "Something is wrong with file" << endl;
		exit(EXIT_FAILURE);
	}
		
		
	maze->PrintMaze();
	cout << maze->FindPath() << endl;
	maze->WritePath();
	maze->WriteFile("maze.txt");



	exit(EXIT_SUCCESS);
}