/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "camouflagegauge.h"

Camouflagegauge::Camouflagegauge() : Entity() {

	this->addSprite("assets/camouflageButton.tga");

	overlappingSpace = new Text();
	this->addChild(overlappingSpace);
}

Camouflagegauge::~Camouflagegauge() {
	this->removeChild(overlappingSpace);
	delete overlappingSpace;
}

void Camouflagegauge::update(float deltaTime) {

}


