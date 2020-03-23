/*
 *  File: main.cpp
 *  Author: Tala Karaki
 *
 */

#include "Maze.h"
#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;


int maze20(bool maze)
{
	if (maze)
	{
		Maze maze(20, 20);
		maze.display();
	}

	return(0);
}

int maze50(bool maze)
{
	if (maze)
	{
		Maze maze(100, 50);
		maze.display();
	}

	return(0);
}

int main(int argc, char* argv[])
{
	int retState = 0;
	bool maze = false;
	bool bigmaze = false;

	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "--maze")) {
			cout << " [x] Printing 20x20 Maze... " << endl;
			maze = true;
		}
		else if (!strcmp(argv[i], "--bigmaze")) {
			cout << " [x] Printing 50x100 Maze... " << endl;
			bigmaze = true;
		}
	}

	if (maze || bigmaze) {
		retState = maze20(maze);  
		retState = maze50(bigmaze);
	}
	else
	{
		cout << " [x] Running in normal mode. " << endl;
    }
	
	cout << " [x] Program complete. " << endl;
	
	return(retState);
}


