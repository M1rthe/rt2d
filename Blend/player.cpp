/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "player.h"

Player::Player() : Entity() {
	this->addSprite("assets/square.tga"); 
	this->sprite()->color = RED;

	velocity = Vector2();
	acceleration = Vector2(0.0, 0.0);
	mousePosition = Vector2();
	direction = Vector2();
	speed = 100.0;
	topspeed = 8.0;
	distance = 0.0;
}

Player::~Player() {

}

void Player::update(float deltaTime) {
	// ###############################################################
	// Movement
	// ###############################################################
	movement(deltaTime);

}

void Player::movement(float dt) {

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
	acceleration = direction / 100;

	if (distance >= 2.0) {

		//Velocity & acceleration
		velocity += acceleration;
		if (velocity.x > topspeed || velocity.x < -topspeed || velocity.y > topspeed || velocity.y < -topspeed) {
			velocity -= acceleration;
		}

		//Move
		position += velocity * dt * speed;
	}
}

