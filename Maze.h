/*
 *  File: Maze.h
 *  Author: Tala Karaki
 *  Description: This class produces a maze using disjoint sets.
                 First a grid of cells is created, and then a cell and a border(top,bottom,right,left) are randomly selected.
				 Initially, each cell is in a separate set. After finding a border, the wall between the selected cell and its 
				 adjacent cell is removed by checking if its in the same set. The cells are then combined by a set union.
 				 After all cells have been traversed and combined into one set, there will only be one set and the maze will be printed in a svg file.
 *
 */

#pragma once

#include <iostream>
#include <stdlib.h> 
#include <string>
#include <vector>

#include "DisjointSet.h"
#include "simple_svg_1.0.0.hpp"


using namespace svg;


typedef struct cell {
	int x=0;
	int y=0;
	int indexNum=-1;
	bool top=true;
	bool right = true;
	bool bottom = true;
	bool left = true;
}Cell;


class Maze
{

private:

	int rows;
	int columns;
	int cellCount;
	int size = 25;
	vector<vector<Cell>> grid;
	DisjointSet set;


public:
	
	/*
	 *  Basic constructor
	 */
	Maze(int width, int height)
	{
		this->rows = width;
		this->columns = height;
		this->cellCount = width * height;

		//create a disjoint set object with corresponding number of cells in the maze
		DisjointSet mySet(cellCount);
		this->set = std::move(mySet);

		//initialize grid with cells
		vector<Cell> cols(0);
		int countID = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Cell c;
				c.indexNum = countID++;
				c.x=i,c.y=j;
				cols.push_back(c);
			}
			grid.push_back(cols);
			cols.resize(0);
		}

		draw();

	}

	/*
	 *  Return whether 2 pairs of cell coordinates are present in the grid
	 */
	bool checkWalls(int x1, int y1, int x2, int y2)
	{
		if (x1 < 0 || y1 < 0 ||
			x2 < 0 || y2 < 0 ||
			x1 >= rows || y1 >= columns ||
			x2 >= rows || y2 >= columns)
		{
			return false;
		}

		return true;
	}
	
	/*
	 *  Return whether two cells have joined the same set
	 */
	bool checkSets(int x1, int y1, int x2, int y2)
	{
		int cell1 = grid[x1][y1].indexNum;
		int cell2 = grid[x2][y2].indexNum;

		if (set.find(cell1) != set.find(cell2)) {
			set.unionSets(cell1, cell2);
			return true;
		}

		return false;
	}

	/*
	 *  Draws a maze by looping through all cells and randomly removing walls based on whether they are in the same set
	 */
	void draw()
	{
		// remove walls for start and finish cells
		grid[0][0].left = false;
		grid[rows-1][columns-1].right = false;

		//loop through all cells until they are all combined into one set 
		while (this->set.getNumSets() > 1) {


		// randomly select a cell and a border and remove wall between its adjacent cell by setting it to false 
		int x = rand() % (rows);
		int y = rand() % (columns);
		int border = rand() % 4;

		if (border == 3 && checkWalls(x, y, x, y + 1) && checkSets(x, y, x, y + 1))
		{
			grid[x][y+1].top = false;
			grid[x][y].bottom = false;
		}
		
		else if (border == 2 && checkWalls(x, y, x + 1, y) && checkSets(x, y, x + 1, y))
		{
			grid[x+1][y].left = false;
			grid[x][y].right = false;
		}
		
		else if (border == 1 && checkWalls(x, y, x, y - 1) && checkSets(x, y, x, y - 1))
		{
			grid[x][y].top = false;
			grid[x][y-1].bottom = false;
		}
		
		else if (border == 0 && checkWalls(x, y, x - 1, y) && checkSets(x, y, x - 1, y))
		{
			grid[x][y].left = false;
			grid[x-1][y].right = false;
		}

		}
			
	}

	/*
	 *  Display the maze in a svg file
	 */
	void display()
	{
		Dimensions dimensions(4000, 5000);
		Document doc("maze.svg", Layout(dimensions, Layout::TopLeft, 1, Point(100, 100)));

		//print title
		doc << Text(Point(185, -10), "MAZE", Fill(Color::Black), Font(44.0, "Verdana"), Stroke(.9, Color::Black));

		// print all walls that are still true by looping through all cells in grid 
		for (vector <Cell>row : grid) {
			for (Cell cl : row) {
				int posX = cl.x * size;
				int posY = cl.y * size;

				if (cl.top)
				{
					doc << Line(Point(posX, posY), Point(posX + size, posY), Stroke(1.5, Color::Black));
				}

				if (cl.bottom)
				{
					doc << Line(Point(posX, posY + size), Point(posX + size, posY + size), Stroke(1.5, Color::Black));
				}

				if (cl.right)
				{
					doc << Line(Point(posX + size, posY), Point(posX + size, posY + size), Stroke(1.5, Color::Black));
				}

				if (cl.left)
				{
					doc << Line(Point(posX, posY), Point(posX, posY + size), Stroke(1.5, Color::Black));
				}

			}

		}

		doc.save();
	}

};
