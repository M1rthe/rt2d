#include "camouflage.h"

Camouflage::Camouflage() : Entity() {

	addSpriteSheet("assets/mytileset.tga", 8, 8);
	sprite()->filter(0);
	scale = Point2(2, 2);
}

Camouflage::~Camouflage() {

}

void Camouflage::update(float deltaTime) {

}

void Camouflage::setCamouflage(int tile) {
	sprite()->frame(tile);
	if (tile == 4) { sprite()->color = RGBAColor(51, 170, 0, 255); }
}



