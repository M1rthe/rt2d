#include "enemy1.h"

Enemy1::Enemy1() : Enemy() {

	type = 1;

	actionDistance = 250;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(3, 3);
	mirror = scale.x;
	attackCooldown = 1.5;
}

Enemy1::~Enemy1() {

}

void Enemy1::update(float deltaTime) {

}

void Enemy1::attack() {
	
	if (time.seconds() - timeFirstAttacked >= attackCooldown) {

		isAttackedThisFrame = true;
		timeFirstAttacked = time.seconds();

		std::cout << "Got shot by Enemy1\n";
	}
}

