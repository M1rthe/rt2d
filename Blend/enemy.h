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
	Vector2 ai(float deltaTime, Vector2 playerPosition);
	//Variables
	float mirror;
	int actionDistance;
	bool isAttacking = false;
	int attackCooldown = 0;
	int attackCooldownCounter = 0;

private:

};

#endif /* ENEMY_H */
