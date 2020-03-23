# MazeGenerator
This program generates a maze using disjoint sets and outputs an svg file displaying it.

First a grid of cells is created. Initially, each cell is in a separate set. Then a cell and a border(top,bottom,right,left) are randomly selected. After finding a border and checking if the two adjacent cells are not already in the same set, the wall connecting them is removed. The cells are then added to the same set. After all cells have been traversed and combined into the same set, there will only be one set. The maze will be printed in a svg file.
