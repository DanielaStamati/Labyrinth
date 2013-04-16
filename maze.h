#pragma once
#include <string.h>
#include <iostream>
#include <ostream>
#include "coordinates.h"
#include <math.h>
#include <vector>
#include "Vector3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

class Maze{

private:
  //reading the input
	void readInput(char*);

public:
	Maze(char*);
	Maze();
	std::vector<std::vector<char> > map;
	int n,m;
	friend std::ostream& operator<<(std::ostream, const Maze&);


	//red portal
	Vector3D portal;
	char portalRot;

	//blue portal
	Vector3D bluePortal;
    char bluePortalRot;

	//special powers
	Vector3D specialPower;
	bool sp;

	//player
	Vector3D character;

	//walls
	bool wall(Vector3D,float);

	bool checkCeilFloor;
	
	//rendering the maze
	void renderMap();
	void renderPlayer();
	void renderPortal();
	void renderSpecialPower();

};

