/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "player.h"

Player::Player(Vector2 wp) : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;

	position = wp;

	finalDestination = Vector2(wp);
	mousePosition = Vector2();
	distance = 0.0;
	magnitude = 0.0;
	
	speed = 100.0;

	std::cout << "finalDestination: " << this->worldposition();
}

Player::~Player()
{

}

void Player::update(float deltaTime)
{
	// ###############################################################
	// Movement
	// ###############################################################

	//Get mouseposition
	mousePosition = Vector2((float)input()->getMouseX(), (float)input()->getMouseY());

	//If left mouse down
	if (input()->getMouseDown(0)) {
		
		std::cout << "finalDestination: " << finalDestination;

		finalDestination = mousePosition;
	}

	//get direction
	dir = (finalDestination - Vector2(position.x, position.y));
	//get distance
	distance = sqrt(dir.x * dir.x + dir.y * dir.y);
	//normalize dir
	dir = Vector2(dir.x / distance, dir.y / distance);

	if (distance >= 2.0) {
		position += dir * deltaTime * speed;
	}
}
