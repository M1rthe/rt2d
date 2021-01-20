/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "bullet.h"

Bullet::Bullet(Vector2 _startPosition, Vector2 _direction) : Entity() {

	startPosition = _startPosition;
	direction = _direction;

	this->addSprite("assets/Bullet.tga");
	this->sprite()->color = RED;
	this->sprite()->filter(0);

	this->rotation.z = direction.getAngleDeg() + 90;
	//this->scale = Point2(0.5, 0.5);

	std::cout << "Bullet Added: startPosition:" << startPosition << ", direction:" << direction << "\n";
}

Bullet::~Bullet() {

}

void Bullet::update(float deltaTime) {
	position += direction * deltaTime * 20;
}




