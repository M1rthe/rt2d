/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "hud.h"

Hud::Hud() : Entity() {

	mission = new Text();
	camouflage1 = new Camouflage();
	camouflage2 = new Camouflage();
	camouflage3 = new Camouflage();
	camouflagegauge = new Camouflagegauge();

	addChild(mission);
	addChild(camouflage1);
	addChild(camouflage2);
	addChild(camouflage3);
	addChild(camouflagegauge);

	margin = SWIDTH * 0.07;
	size = 128;

	mission->scale = Point2(0.5, 0.5);

	mission->position = Vector2(margin, margin);
	camouflage1->position = Vector2(SWIDTH - (margin * 1) - (size/2 * 0.0), SHEIGHT - margin);
	camouflage2->position = Vector2(SWIDTH - (margin * 2) - (size/2 * 1.0), SHEIGHT - margin);
	camouflage3->position = Vector2(SWIDTH - (margin * 3) - (size/2 * 2.0), SHEIGHT - margin);
	camouflagegauge->position = Vector2(margin, SHEIGHT - margin);

	camouflage1->setCamouflage(13);
	camouflage2->setCamouflage(2);
	camouflage3->setCamouflage(4);
}

Hud::~Hud() {

	this->removeChild(mission);
	this->removeChild(camouflage1);
	this->removeChild(camouflage2);
	this->removeChild(camouflage3);
	this->removeChild(camouflagegauge);

	delete mission;
	delete camouflage1;
	delete camouflage2;
	delete camouflage3;
	delete camouflagegauge;
}

void Hud::update(float deltaTime) {

}




