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
	speed = 50.0;
	topspeed = 8.0;
	distance = 0.0;
}

Player::~Player() {

}

void Player::update(float deltaTime) {
	movement(deltaTime);
}

void Player::movement(float dt) {

	//Get mouseposition
	mousePosition = Vector2((float)input()->getMouseX(), (float)input()->getMouseY());

	//get direction
	direction = (finalDestination - Vector2(position.x, position.y));
	//get distance
	distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	//normalize dir
	acceleration = Vector2(direction.x / distance, direction.y / distance);


	if (distance <= 1.5) { //Standing still
		acceleration *= 0;
		velocity *= 0;
		position = finalDestination;
	}
	if (distance > 1.5 && distance <= 8.0) { //Slowing down
		acceleration *= 0.999; 
		velocity *= 0.999;
	}
	if (distance > 8.0) { //Moving

		//Velocity & acceleration
		velocity += acceleration;
		if (velocity.x > topspeed || velocity.x < -topspeed || velocity.y > topspeed || velocity.y < -topspeed) {
			velocity -= acceleration;
		}

		//Move
		position += velocity * speed * dt; 
	}
}

void Player::newDestination(Vector2 d) {
	finalDestination = d;
	finalDestination = mousePosition;
	velocity *= 0;
}

