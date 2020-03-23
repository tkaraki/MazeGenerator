/*
 *  File: DisjointSet.h
 *  Author: Tala Karaki
 *  Description: This class implememts the algorithm for disjoint sets.
 *
 */

#pragma once

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include <stack>



using namespace std;


class DisjointSet
{
private:
	vector<int> sets;
	int numSets;

public:

	/**
	* Basic Constructur.
	* Initially set all elements to -1 because they are alone.
	*/
	DisjointSet(int numElements=1) {
	
		sets.resize(numElements);
		numSets = numElements;

		for (int i = 0; i < numElements; i++)
		{
			sets[i] = -1;
		}
	}

	/**
	* Return the number of sets.
	*/
	int getNumSets()
	{
		return numSets;

	}

	/**
 	* Perform a find with path compression.
	* Return the set containing x.
	*/
	int find(int x)
	{
		if (sets[x] < 0)
			return x;
		else
			return sets[x] = find(sets[x]);
	}

	/**
        * Union two disjoint sets by rank.
	* root1 is the root of set 1.
	* root2 is the root of set 2.
	*/
	void unionSets(int root1, int root2)
	{
		int i = find(root1);
		int j = find(root2);

		if (sets[j] < sets[i]) // root2 is deeper
			sets[i] = j; // Make root2 new root
		else
		{
			if (sets[i] == sets[j])
				--sets[i]; // Update height if same
			sets[j] = i; // Make root1 new root
		}

		numSets--; //update number of sets
	}


 };

#endif
