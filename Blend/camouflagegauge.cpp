/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "camouflagegauge.h"

Camouflagegauge::Camouflagegauge() : Entity() {

	this->addSprite("assets/square.tga");
	this->sprite()->color = BLUE;
}

Camouflagegauge::~Camouflagegauge() {

}

void Camouflagegauge::update(float deltaTime) {

}


