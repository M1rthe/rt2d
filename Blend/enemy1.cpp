#include "enemy1.h"

Enemy1::Enemy1() : Enemy() {

	actionDistance = 250;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	mirror = scale.x;
	attackCooldown = 1.5;
}

Enemy1::~Enemy1() {

}

void Enemy1::update(float deltaTime) {

}

void Enemy1::attack() {
	
	if (time.seconds() - timeFirstAttacked >= attackCooldown) {

		shootThisFrame = true;
		timeFirstAttacked = time.seconds();

		std::cout << "Shoot animation\n";
	}
}

