#include "enemy1.h"

Enemy1::Enemy1() : Enemy() {

	actionDistance = 250;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(3, 3);
	mirror = scale.x;
}

Enemy1::~Enemy1() {

}

void Enemy1::update(float deltaTime) {

}

void Enemy1::attack(Vector2 pos, Vector2 dir) {

	if (bulletCooldown > 250) {

		if (scale.x < 0) { dir.x *= -1; }

		std::cout << "Shoot bullet (position:"<<pos<<", direction:"<<dir<<")\n";
		//addBullet(position, direction);

		bulletCooldown = 0;
	}

	bulletCooldown++;
}

