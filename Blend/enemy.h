/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <rt2d/entity.h>
#include "collider.h"
#include "basicentity.h"
#include "bullet.h"
#include <rt2d/timer.h>

using namespace std;

 /// @brief The MyEntity class is the Entity implementation.
class Enemy : public Entity {

public:

	//Standard entity function
	Enemy(); 
	virtual ~Enemy();
	virtual void update(float deltaTime);

	//Functions
	Rectangle getRect();
	virtual void attack();
	Vector2 ai(float deltaTime, Vector2 playerPosition, bool playerIsCamouflaged);
	//Variables
	float mirror;
	int actionDistance;
	bool isAttackedThisFrame = false;

	double attackCooldown = 0.0;
	double timeFirstAttacked = 0.0;
	Timer time;

	Vector2 oldPosition;
	bool collided;

	vector<Rectangle> colliders;

private:
	bool cast(Vector2 playerPos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	bool canSeePlayer = false;
};

#endif /* ENEMY_H */
