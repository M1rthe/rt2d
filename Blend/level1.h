/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef LEVEL1_H
#define LEVEL1_H

#include <rt2d/scene.h>
#include <rt2d/camera.h>
#include "player.h"
#include "map.h"
#include "hud.h"

 /// @brief The MyScene class is the Scene implementation.
class Level1 : public Scene
{
public:

	Hud* hud;

	/// @brief Constructor
	Level1();
	/// @brief Destructor
	virtual ~Level1();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/// @brief the rotating square in the middle of the screen
	Map* map;
	Player* player;
	/// @brief a Timer to rotate the color every n seconds
	Timer t;
	int currentCamouflage = 1;
	bool moveByKey = true;

	Vector2 mousePosition;
	bool mouseIsOn(Vector2 position, Vector2 withinPos, Vector2 s);
};

#endif /* LEVEL1_H */
