/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>

 /// @brief The MyEntity class is the Entity implementation.
class Camouflage : public Entity
{
public:

	int type;

	/// @brief Constructor
	Camouflage(int _type);
	/// @brief Destructor
	virtual ~Camouflage();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:

};

#endif /* CAMOUFLAGE_H */
