/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "bullet.h"

Bullet::Bullet(Vector2 _startPosition, Vector2 _direction) : Entity() {

	startPosition = _startPosition;
	direction = _direction;

	position = startPosition;

	this->addSprite("assets/Bullet.tga");
	this->sprite()->color = RED;
	this->sprite()->filter(0);

	this->rotation.z = atan2(direction.y, direction.x);
	/*
	yx = NOPE
	yz = NOPE
	xy = NOPE
	xz = NOPE
	zx = NOPE
	zy = NOPE
	*/

	//direction.getAngleDeg();
	//this->scale = Point2(0.5, 0.5);
}

Bullet::~Bullet() {

}

void Bullet::update(float deltaTime) {
	position += direction * deltaTime * 100;
}




