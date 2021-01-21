/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "enemy.h"

Enemy::Enemy() : Entity() {

	time.start();

	actionDistance = 250;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(3, 3);
	mirror = scale.x;
}

Enemy::~Enemy() {

}

void Enemy::update(float deltaTime) {

}

Vector2 Enemy::ai(float deltaTime, Vector2 playerPosition) {

	isAttackedThisFrame = false;

	float speed = 80;
	float distance;
	Vector2 direction = Vector2(0, 0);

	//get direction
	direction = (playerPosition - position);
	
	//get distance
	distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	//normalize dir
	direction = Vector2(direction.x / distance, direction.y / distance);

	if (distance > actionDistance) {
		position += direction * speed * deltaTime;
	}
	else {
		//if (!isAttacking) { timeFirstAttacked = time.seconds(); std::cout << "setting timeFirstAttacked\n"; }
		attack();
	}

	//Face direction
	if (direction.x > 0 && distance > 5) { scale.x = mirror * -1; }
	else { scale.x = mirror; }

	return direction;
}

void Enemy::attack() { }

Rectangle Enemy::getRect() {
	//Only legs
	/*
	return Rectangle(
		position.x + sprite()->width() + 20,
		position.y - sprite()->height() + 160,
		sprite()->width() + 20, 
		sprite()->height() - 55
	);
	*/
	float scaleX = scale.x;
	if (scaleX < 0) { scaleX *= -1; }

	return Rectangle(
		position.x - (sprite()->width() * scaleX / 2),
		position.y + (sprite()->height() * scale.y / 2) - 20,
		sprite()->width() * scaleX,
		20
	);
}

