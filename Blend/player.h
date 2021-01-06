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
#include "basicentity.h"
#include <rt2d/timer.h>
#include <string>
#include "map.h"
using namespace std;


#define LEFT 0 
#define RIGHT 1

/// @brief The MyEntity class is the Entity implementation.
class Player : public Entity
{
public:

	/// @brief Constructor
	Player();
	/// @brief Destructor
	virtual ~Player();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void check4input(float dt, Map* map, bool moveWithKeys);
	void clickCamouflage(int c);
	void newDestination(Vector2 d);

	int camouflageFrame = 65; //doesnt exists, so its just green, default cameleon
	Vector2 finalDestination;
	int facing = RIGHT;

private:

	void animation();
	void consume();
	void moveByClick(float dt);
	void moveByKey(float dt, Vector2 dir);

	Timer time;
	double nextActionTime = 0.0;
	double timeFirstStickedOutTongue = 0.0;
	bool tongueIsStickedOut = false;

	Vector2 direction;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 mousePosition;
	float speed;
	float topspeed;
	float distance;
	bool isMoving = false;
};

#endif /* PLAYER_H */