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
#include "collider.h"
using namespace std;

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

	vector<Rectangle> tilesWithCollider;
	int findMostOverlappedTile(Vector2 position, Vector2 size, int camouflage, int facing);
	Rectangle getRectTile(int tile);

private:
	BasicEntity *grid;
	vector<int> tilesWithCollision;

	string* level = new string[2048]{ //64 x 32
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","bt","bt","bt","bt","bt","bt","bt","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","bt","cfw","cfw","cfw","cfw","cfw","bt","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","bt","cfw","cfw","cfw","cfw","cfw","bt","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","bt","cfw","cfw","cfw","cfw","cfw","bt","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","bt","bt","cfw","cfw","cfw","bt","bt","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
	"g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g","g",
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