#include "enemy2.h"

Enemy2::Enemy2() : Enemy() {

	actionDistance = 100;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(3, 3);
	mirror = scale.x;
	attackCooldown = 3.0;
}

Enemy2::~Enemy2() {

}

void Enemy2::update(float deltaTime) {

}

void Enemy2::attack() {
	
	if (time.seconds() - timeFirstAttacked > attackCooldown) {

		isAttackedThisFrame = true;
		timeFirstAttacked = time.seconds();

		std::cout << "Got hit by Enemy2\n";
	}
}
