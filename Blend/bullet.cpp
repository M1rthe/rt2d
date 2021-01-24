/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "bullet.h"

Bullet::Bullet(Vector2 _direction) : Entity() {

	direction = _direction;

	this->addSprite("assets/Bullet.tga");
	this->sprite()->color = RED;
	this->sprite()->filter(0);

	this->rotation.z = atan2(direction.y, direction.x);
}

Bullet::~Bullet() {

}

void Bullet::update(float deltaTime) {
	position += direction * deltaTime * 200;
}

Rectangle Bullet::getRect() {
	return Rectangle(
		position.x,
		position.y,
		sprite()->width() * scale.x,
		sprite()->height() * scale.y
	);
}




