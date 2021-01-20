#include "enemy2.h"

Enemy2::Enemy2() : Enemy() {

	actionDistance = 100;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(3, 3);
	mirror = scale.x;
}

Enemy2::~Enemy2() {

}

void Enemy2::update(float deltaTime) {

}

void Enemy2::attack(Vector2 pos, Vector2 dir) {
	std::cout << "attack by enemy2\n";
}
