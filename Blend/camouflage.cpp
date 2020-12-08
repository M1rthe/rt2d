/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "camouflage.h"

Camouflage::Camouflage(int _type) : Entity() {
	type = _type;

	this->addSpriteSheet("assets/mytileset.tga", 8, 8);
	this->sprite()->filter(0);
	this->scale = Point2(2, 2);
}

Camouflage::~Camouflage() {

}

void Camouflage::update(float deltaTime) {

}

void Camouflage::setCamouflage(int tile) {
	this->sprite()->frame(tile);
	if (tile == 4) { this->sprite()->color = RGBAColor(51, 170, 0, 255); }
}



