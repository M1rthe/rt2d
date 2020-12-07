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
#include <cmath>
#include <rt2d/pointx.h>
#include "grid.h"
#include <rt2d/timer.h>
#include <string>
using namespace std;

/// @brief The MyEntity class is the Entity implementation.
class Player : public Entity
{
public:


	/// @brief Constructor
	Player();
	/// @brief Destructor
	virtual ~Player();

	Vector2 finalDestination;
	string facing = "right";
	bool isMoving = false;
	void newDestination(Vector2 d);
	void consume();
	void moveByClick(float dt);
	void moveByKey(float dt, Vector2 dir);

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:

	void animation();

	Timer time;
	double nextActionTime = 0.0;
	double timeFirstStickedOutTongue = 0.0;
	bool tongueIsStickedOut = false;

	Vector2 velocity;
	Vector2 acceleration;
	Vector2 mousePosition;
	Vector2 direction;
	float speed;
	float topspeed;
	float distance;
};

#endif /* PLAYER_H */
