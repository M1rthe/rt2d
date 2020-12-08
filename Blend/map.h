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

 /// @brief The MyEntity class is the Entity implementation.
class Map : public Entity
{
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

private:
	BasicEntity* grid;
};

#endif /* MAP_H */
