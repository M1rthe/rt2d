/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "camouflage.h"

Camouflage::Camouflage(int _type) : Entity() {
	type = _type;

	this->addSprite("assets/camouflageButton.tga");
}

Camouflage::~Camouflage() {

}

void Camouflage::update(float deltaTime) {

}

void Camouflage::setCamouflage(string tile) {

}



