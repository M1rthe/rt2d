/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef HUD_H
#define HUD_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>
#include <rt2d/text.h>
#include "camouflage.h"
#include "camouflagegauge.h"

 /// @brief The MyEntity class is the Entity implementation.
class Hud : public Entity
{
public:

	/// @brief Constructor
	Hud();
	/// @brief Destructor
	virtual ~Hud();

	Text* mission;
	Camouflage* camouflage1;
	Camouflage* camouflage2;
	Camouflage* camouflage3;
	Camouflagegauge* camouflagegauge;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void clickedCamouflage1();
	void clickedCamouflage2();
	void clickedCamouflage3();

private:

	float margin;
	int size;
};

#endif /* HUD_H */
