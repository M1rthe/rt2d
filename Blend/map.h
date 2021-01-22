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
	vector<int> tilesWithCollision;

private:
	BasicEntity *grid;

	string* level = new string[2048]{ //64 x 32
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","fbt","fbtF","tsb","tsb","tsb","fbt","fbtF","tsb","fbt","fbtF","tsb","tsb","tsb","fbt","fbtF","tsb","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","fbb","fbbF","tsb","tsb","tsb","fbb","fbbF","tsb","fbb","fbbF","tsb","tsb","tsb","fbb","fbbF","tsb","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","tsb","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tsb","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","tsb","f","f","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","fdt","fdtF","tbr","tbr","tbr","tbr","tbr","f","f","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","fdb","fdbF","tbr","tbr","tbr","tbr","tbr","f","f","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","fpl","fpl","fpl","fpl","tbr","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","fpl","fpl","fpl","fpl","tbr","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","tcw","tcw","tcw","tbr","tbr","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","fdt","fdtF","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","tbr","fdb","fdbF","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	};
	float CalculateDistance(Vector2 p1, Vector2 p2);
};

#endif /* MAP_H */