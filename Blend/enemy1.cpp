#include "enemy1.h"

Enemy1::Enemy1() : Enemy() {

	actionDistance = 250;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(3, 3);
	mirror = scale.x;
	attackCooldown = 250;
}

Enemy1::~Enemy1() {

}

void Enemy1::update(float deltaTime) {

}

void Enemy1::attack() {
	if (attackCooldownCounter > attackCooldown) {
		std::cout << "Got shot by Enemy1\n";
	}
}

