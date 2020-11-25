/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "player.h"

Player::Player() : Entity()
{
	this->addSprite("assets/square.tga"); 
	this->sprite()->color = RED;

	velocity = Vector2();
	acceleration = Vector2(0.0, 0.0);
	topspeed = 10.0;

	finalDestination = position;
	mousePosition = Vector2();
	direction = Vector2();
	distance = 0.0;
	magnitude = 0.0;
	
	speed = 100.0;

	std::cout << "\n position constructor: " << position << "\n";
	std::cout << "worldpos constructor: " << this->worldposition() << "\n\n";
}

Player::~Player()
{

}

void Player::update(float deltaTime)
{
	std::cout << "position update: " << position << "\n";
	std::cout << "worldpos update: " << this->worldposition() << "\n";

	// ###############################################################
	// Movement
	// ###############################################################

	//Get mouseposition
	mousePosition = Vector2((float)input()->getMouseX(), (float)input()->getMouseY());

	//If left mouse down
	if (input()->getMouseDown(0)) {
		
		finalDestination = mousePosition; 
		velocity *= 0;
	}

	//get direction
	direction = (finalDestination - Vector2(position.x, position.y));
	//get distance
	distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	//normalize dir
	direction = Vector2(direction.x / distance, direction.y / distance);
	acceleration = direction / 250;

	if (distance >= 2.0) {

		//Velocity & acceleration
		velocity += acceleration;
		if (velocity.x > topspeed || velocity.y > topspeed)
		{
			velocity = Vector2(topspeed, topspeed);
		}
		position += velocity;

		velocity *= 0.993;

		//Move
		position += direction * deltaTime * speed;
	}
}
