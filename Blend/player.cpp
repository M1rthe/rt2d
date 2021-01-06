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
}

void Player::animation() {

	//Tongue
	if (tongueIsStickedOut) {
		if (facing == RIGHT) { this->sprite()->frame(0); }
		if (facing == LEFT) { this->sprite()->frame(1); }

		if (time.seconds() - timeFirstStickedOutTongue > 0.1) {
			if (facing == RIGHT) { this->sprite()->frame(2); }
			if (facing == LEFT) { this->sprite()->frame(3); }
		}
		if (time.seconds() - timeFirstStickedOutTongue > 0.3) {
			if (facing == RIGHT) { this->sprite()->frame(0); }
			if (facing == LEFT) { this->sprite()->frame(1); }
		}
		if (time.seconds() - timeFirstStickedOutTongue > 0.4) {
			//if (facing == "right") { this->sprite()->frame(0); }
			if (facing == RIGHT) { this->sprite()->frame(6); }
			if (facing == LEFT) { this->sprite()->frame(7); }
			tongueIsStickedOut = false;
		}
	}
	//Move
	if (isMoving) {
		if (time.seconds() > nextActionTime) {
			nextActionTime += 0.4;

			if (facing == RIGHT) { //right
				if (this->sprite()->frame() == 5 || this->sprite()->frame() == 4) {
					this->sprite()->frame(6);
				}
				else if (this->sprite()->frame() == 7 || this->sprite()->frame() == 6) {
					this->sprite()->frame(4);
				}
			}

			else if (facing == LEFT) { //left
				facing = LEFT;
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
		if (facing == RIGHT) {
			this->sprite()->frame(6);
		}
		else { this->sprite()->frame(7); }
	}
}

void Player::moveByKey(float dt, Vector2 dir) {
	speed = 250.0;
	dir.normalize();
	position += dir * speed * dt;
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
			facing = RIGHT;
		}
		else { facing = LEFT; }
	}
}

void Player::check4input(float dt, Map* map, bool moveWithKeys) {
	//Consume
	if (input()->getKeyUp(KeyCode::C)) {
		consume();
	}
	//WASD
	if (moveWithKeys) {

		Vector2 dir = Vector2();
		isMoving = false;

		//Movement WASD
		if (input()->getKey(KeyCode::W) || input()->getKey(KeyCode::Up)) {

			if (position.y + (scale.y * sprite()->height() / 2) - 10 >= map->position.y + SHEIGHT / 2) {//+ (player->scale.y * player->sprite()->height())       //+ ((map->cellheight * map->gridheight) / 2)
				dir.y -= 1;
				isMoving = true;
			}
		}
		if (input()->getKey(KeyCode::S) || input()->getKey(KeyCode::Down)) {
			if (position.y + (scale.y * sprite()->height() / 2) - 10 <= map->position.y - SHEIGHT / 2 + (map->cellheight * map->gridheight)) {
				dir.y += 1;
				isMoving = true;
			}
		}
		if (input()->getKey(KeyCode::D) || input()->getKey(KeyCode::Right)) {
			if (position.x + (scale.x * sprite()->width() / 2) - 45 <= map->position.x - SWIDTH / 2 + (map->cellwidth * map->gridwidth)) {
				dir.x += 1;
				facing = RIGHT;
				isMoving = true;
			}
		}
		if (input()->getKey(KeyCode::A) || input()->getKey(KeyCode::Left)) {
			if (position.x + (scale.x * sprite()->width() / 2) - 50 >= map->position.x + SWIDTH / 2) { // (map->cellwidth * map->gridwidth)
				dir.x -= 1;
				facing = LEFT;
				isMoving = true;
			}
		}
		moveByKey(dt, dir);
	}
	else {
		//Limit click to go movement
		if (position.y + (scale.y * sprite()->height() / 2) - 10 < map->position.y + SHEIGHT / 2) { //top
			finalDestination.y = map->position.y + SHEIGHT / 2 - (scale.y * sprite()->height() / 2) + 10;
			position.y = map->position.y + SHEIGHT / 2 - (scale.y * sprite()->height() / 2) + 10;
		}
		if (position.y + (scale.y * sprite()->height() / 2) - 10 > map->position.y - SHEIGHT / 2 + (map->cellheight * map->gridheight)) { //bottom
			finalDestination.y = map->position.y - SHEIGHT / 2 + (map->cellheight * map->gridheight) - (scale.y * sprite()->height() / 2) + 10;
			position.y = map->position.y - SHEIGHT / 2 + (map->cellheight * map->gridheight) - (scale.y * sprite()->height() / 2) + 10;
		}
		if (position.x + (scale.x * sprite()->width() / 2) - 45 > map->position.x - SWIDTH / 2 + (map->cellwidth * map->gridwidth)) { //right
			finalDestination.x = map->position.x - SWIDTH / 2 + (map->cellwidth * map->gridwidth) - (scale.x * sprite()->width() / 2) + 45;
			position.x = map->position.x - SWIDTH / 2 + (map->cellwidth * map->gridwidth) - (scale.x * sprite()->width() / 2) + 45;
		}
		if (position.x + (scale.x * sprite()->width() / 2) - 50 < map->position.x + SWIDTH / 2) { //left
			finalDestination.x = map->position.x + SWIDTH / 2 - (scale.x * sprite()->width() / 2) + 50;
			position.x = map->position.x + SWIDTH / 2 - (scale.x * sprite()->width() / 2) + 50;
		}
		moveByClick(dt);
	}
}

void Player::clickCamouflage(int c) {
	if (c == 1) { addSpriteSheet("assets/kameleon/kameleonAnimatedGrass.tga", 2, 4); camouflageFrame = 0; }
	if (c == 2) { addSpriteSheet("assets/kameleon/kameleonAnimatedBricks.tga", 2, 4); camouflageFrame = 2; }
	if (c == 3) { addSpriteSheet("assets/kameleon/kameleonAnimated.tga", 2, 4); camouflageFrame = 65; }

	sprite()->filter(0);
	if (facing == RIGHT) { sprite()->frame(6); }
	if (facing == LEFT) { sprite()->frame(7); }
}


void Player::consume() {
	tongueIsStickedOut = true;
	timeFirstStickedOutTongue = time.seconds();
}


void Player::newDestination(Vector2 d) {
	finalDestination = d;
	velocity *= 0;
}