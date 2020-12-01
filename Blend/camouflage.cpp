/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "camouflage.h"

Camouflage::Camouflage(int _type) : Entity() {
	type = _type;

	std::cout << "add sprite to camouflage" << type << "\n";

	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;
}

Camouflage::~Camouflage() {

}

void Camouflage::update(float deltaTime) {

}


