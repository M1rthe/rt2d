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

Vector2 Enemy::ai(float deltaTime, Vector2 playerPosition, bool playerIsCamouflaged) {

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

	if (canSeePlayer) {
		if (distance > actionDistance) {
			//x
			oldPosition = position;
			position.x += direction.x * speed * deltaTime;
			collided = false;
			for (int i = 0; i < colliders.size(); i++) { //Not moving (tiles)
				bool collidedBoolX = Collider::rectangle2rectangle(getRect(), colliders[i]);
				if (collidedBoolX) { collided = collidedBoolX; }
			}
			if (collided) { position = oldPosition; }

			//y
			oldPosition = position;
			position.y += direction.y * speed * deltaTime;
			collided = false;
			for (int i = 0; i < colliders.size(); i++) { //Not moving (tiles)
				bool collidedBoolY = Collider::rectangle2rectangle(getRect(), colliders[i]);
				if (collidedBoolY) { collided = collidedBoolY; }
			}
			if (collided) { position = oldPosition; }
		}
		else {
			attack();
		}

		//Face direction
		if (distance > 5) { 
			if (playerPosition.x > position.x) { scale.x = mirror * -1; }
			else { scale.x = mirror; }
		} 
	}

	//CanSeePlayer??
	canSeePlayer = playerIsCamouflaged; //Camouflage working?

	if (distance > 800) { canSeePlayer = false; } //Within enemy renderdistance?

	//In their view?
	if (scale.x < 0 && playerPosition.x < position.x) { canSeePlayer = false; }
	if (scale.x > 0 && playerPosition.x > position.x) { canSeePlayer = false; }

	if (distance < 130) { canSeePlayer = true; } //So nearby they can hear you?

	//Walls between you?
	for (int i = 0; i < colliders.size(); i++) {

		float x1L = colliders[i].x;
		float y1L = colliders[i].y;
		float x2L = colliders[i].x;
		float y2L = colliders[i].y + colliders[i].height;

		float x1R = colliders[i].x + colliders[i].width;
		float y1R = colliders[i].y;
		float x2R = colliders[i].x + colliders[i].width;
		float y2R = colliders[i].y + colliders[i].height;

		float x1T = colliders[i].x;
		float y1T = colliders[i].y;
		float x2T = colliders[i].x + colliders[i].width;
		float y2T = colliders[i].y;

		float x1B = colliders[i].x;
		float y1B = colliders[i].y + colliders[i].height;
		float x2B = colliders[i].x + colliders[i].width;
		float y2B = colliders[i].y + colliders[i].height;

		float x3 = position.x;
		float y3 = position.y;
		float x4 = position.x + direction.x;
		float y4 = position.y + direction.y;

		if (cast(playerPosition, x1L, y1L, x2L, y2L, x3, y3, x4, y4) ||
			cast(playerPosition, x1R, y1R, x2R, y2R, x3, y3, x4, y4) ||
			cast(playerPosition, x1T, y1T, x2T, y2T, x3, y3, x4, y4) ||
			cast(playerPosition, x1B, y1B, x2B, y2B, x3, y3, x4, y4)) {

			canSeePlayer = false;
		}
	}

	return direction;
}

void Enemy::attack() { }

Rectangle Enemy::getRect() {
	float scaleX = scale.x;
	if (scaleX < 0) { scaleX *= -1; }

	return Rectangle(
		position.x - (sprite()->width() * scaleX / 2),
		position.y + (sprite()->height() * scale.y / 2) - 20,
		sprite()->width() * scaleX,
		20
	);
}

bool Enemy::cast(Vector2 playerPos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) { //Is blocking view?

	bool blockingView = false;

	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0) { // denominator can't be zero
		blockingView = false;
	}
	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

	if (t > 0 && t < 1 && u > 0) {
		Vector2 pt;
		pt.x = x1 + t * (x2 - x1);
		pt.y = y1 + t * (y2 - y1);
		if (playerPos < pt) {
			blockingView = true;
		}
	}

	return blockingView;
}

