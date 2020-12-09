/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "player.h"

Player::Player() : Entity() {

	time.start();

	velocity = Vector2();
	acceleration = Vector2(0.0, 0.0);
	mousePosition = Vector2();
	direction = Vector2();
	speed = 50.0;
	topspeed = 8.0;
	distance = 0.0;

	this->addSpriteSheet("assets/kameleon/kameleonAnimated.tga", 2, 4);
	this->sprite()->filter(0);
	this->scale = Point2(5, 5);
	this->sprite()->frame(6);

	/*
	0: tongue1 right
	1: tongue1 left

	2: tongue2 right
	3: tongue2 left

	4: walk right
	5: walk left

	6: idle right
	7: idle left
	*/
}

Player::~Player() {
}

void Player::update(float deltaTime) {
	//movement(deltaTime, "key"); //click or key
	animation();

	if (tongueIsStickedOut) {

		if (facing == "right") { this->sprite()->frame(0); } else { this->sprite()->frame(1); }

		if (time.seconds() - timeFirstStickedOutTongue > 0.1) {
			if (facing == "right") { this->sprite()->frame(2); } else { this->sprite()->frame(3); }
		}
		if (time.seconds() - timeFirstStickedOutTongue > 0.3) {
			if (facing == "right") { this->sprite()->frame(0); } else { this->sprite()->frame(1); }
		}
		if (time.seconds() - timeFirstStickedOutTongue > 0.4) {
			tongueIsStickedOut = false;
			if (facing == "right") { this->sprite()->frame(0); }
			if (facing == "right") { this->sprite()->frame(6); } else { this->sprite()->frame(7); }
		}
	}
}

void Player::animation() {

	if (isMoving) {
		if (time.seconds() > nextActionTime) {
			nextActionTime += 0.4;

			if (facing == "right") { //right
				if (this->sprite()->frame() == 5 || this->sprite()->frame() == 4) {
					this->sprite()->frame(6);
				}
				else if (this->sprite()->frame() == 7 || this->sprite()->frame() == 6) {
					this->sprite()->frame(4);
				}
			}

			else if (facing == "left") { //left
				facing = "left";
				if (this->sprite()->frame() == 5 || this->sprite()->frame() == 4) {
					this->sprite()->frame(7);
				}
				else if (this->sprite()->frame() == 7 || this->sprite()->frame() == 6) {
					this->sprite()->frame(5);
				}
			}
		}
	}

	else if (!isMoving) {
		if (facing == "right") {
			this->sprite()->frame(6);
		}
		else { this->sprite()->frame(7); }
	}
}

void Player::moveByKey(float dt, Vector2 dir, bool _isMoving, string _facing) {
	speed = 250.0;
	position += dir * speed * dt;

	isMoving = _isMoving;
	facing = _facing;
}

void Player::moveByClick(float dt) {

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

		//Animation
		isMoving = false;
	}

	if (distance > 1.5 && distance <= 8.0) { //Slowing down
		acceleration *= 0.999;
		velocity *= 0.999;

		//Animation
		isMoving = false;
	}

	if (distance > 8.0) { //Moving

		//Velocity & acceleration
		velocity += acceleration;
		if (velocity.x > topspeed || velocity.x < -topspeed || velocity.y > topspeed || velocity.y < -topspeed) {
			velocity -= acceleration;
		}

		//Move
		position += velocity * speed * dt;


		//Animation
		isMoving = true;
		if (velocity.x > 0) {
			facing = "right";
		}
		else { facing = "left"; }
	}
}

void Player::consume() {
	tongueIsStickedOut = true;
	timeFirstStickedOutTongue = time.seconds();
}


void Player::newDestination(Vector2 d) {
	finalDestination = d;
	velocity *= 0;
}

