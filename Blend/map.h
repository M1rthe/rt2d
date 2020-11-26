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
#include <rt2d/sprite.h>

 /// @brief The MyEntity class is the Entity implementation.
class Map : public Entity
{
public:

	/// @brief Constructor
	Map();
	/// @brief Destructor
	virtual ~Map();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	Sprite *tilesetSprite;
};

#endif /* MAP_H */
