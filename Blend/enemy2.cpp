#include "enemy2.h"

Enemy2::Enemy2() : Enemy() {

	actionDistance = 100;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(3, 3);
	mirror = scale.x;
	attackCooldown = 400;
}

Enemy2::~Enemy2() {

}

void Enemy2::update(float deltaTime) {

}

void Enemy2::attack() {
	if (attackCooldownCounter > attackCooldown) {
		std::cout << "Got hit by Enemy2\n";
	}
}
