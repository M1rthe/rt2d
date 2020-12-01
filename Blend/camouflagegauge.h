/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef CAMOUFLAGEGAUGE_H
#define CAMOUFLAGEGAUGE_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>

 /// @brief The MyEntity class is the Entity implementation.
class Camouflagegauge : public Entity
{
public:

	/// @brief Constructor
	Camouflagegauge();
	/// @brief Destructor
	virtual ~Camouflagegauge();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:

};

#endif /* CAMOUFLAGEGAUGE_H */
