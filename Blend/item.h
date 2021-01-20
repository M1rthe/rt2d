/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef ITEM_H
#define ITEM_H

#include <rt2d/entity.h>
#include <string>
#include "collider.h"

using namespace std;

 /// @brief The MyEntity class is the Entity implementation.
class Item : public Entity
{
public:

	Item(string filename);
	virtual ~Item();
	virtual void update(float deltaTime);

	string name;

private:

};

#endif /* ITEM_H */
