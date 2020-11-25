/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>
#include <cmath>

/// @brief The MyEntity class is the Entity implementation.
class Player : public Entity
{
public:

	Vector2 velocity;
	Vector2 acceleration;
	float topspeed;

	Vector2 finalDestination;
	Vector2 mousePosition;
	Vector2 direction;
	float distance;
	float magnitude;
	/// @brief Constructor
	Player();
	/// @brief Destructor
	virtual ~Player();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
	float speed;
};

#endif /* PLAYER_H */
