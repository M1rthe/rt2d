/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef BULLET_H
#define BULLET_H

#include <rt2d/entity.h>
#include "collider.h"

class Bullet : public Entity {

public:

	Bullet(Vector2 _startPosition, Vector2 _direction);
	virtual ~Bullet();
	virtual void update(float deltaTime);

	Rectangle getRect();

private:
	Vector2 startPosition;
	Vector2 direction;
};

#endif /* BULLET_H */
