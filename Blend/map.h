/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef MAP_H
#define MAP_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>
#include "basicentity.h"
#include <string>
using namespace std;

#define DIRT 1 
#define GRASS 2
#define WATER 3 
#define COLOR 4

/// @brief The MyEntity class is the Entity implementation.
class Map : public Entity {
public:

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;

	/// @brief Constructor
	Map();
	/// @brief Destructor
	virtual ~Map();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	int findMostOverlappedTile(Vector2 position, Vector2 size, int camouflage, int facing);

private:
	BasicEntity *grid;
	string* level = new string[1024]{ //64 x 16
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","d","d","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","cb",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","d","d","w","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","d","b","w","c","cr","co","cy","cg","cb","cm","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	/*
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cb",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","g","g","g","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","g","g","g","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	"cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw","cw",
	*/
	};
	float CalculateDistance(Vector2 p1, Vector2 p2);
};

#endif /* MAP_H */