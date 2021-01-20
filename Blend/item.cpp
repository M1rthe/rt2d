#include "item.h"

Item::Item(string filename) : Entity() {

	name = filename;

	this->addSprite("assets/Items/"+ filename +".tga");
	this->sprite()->filter(0);
	this->scale = Point2(2, 2);
}

Item::~Item() {

}

void Item::update(float deltaTime) {

}


