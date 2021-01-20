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

 /// @brief The MyEntity class is the Entity implementation.
class Bullet : public Entity
{
public:

	/// @brief Constructor
	Bullet(Vector2 _startPosition, Vector2 _direction);
	/// @brief Destructor
	virtual ~Bullet();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	Vector2 startPosition;
	Vector2 direction;
};

#endif /* BULLET_H */
