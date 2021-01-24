#include "camouflagegauge.h"

Camouflagegauge::Camouflagegauge() : Entity() {

	addSpriteSheet("assets/camouflageButton.tga", 1, 2);
	sprite()->filter(0);
}

Camouflagegauge::~Camouflagegauge() {

}

void Camouflagegauge::update(float deltaTime) {

}

void Camouflagegauge::isHidden(bool hidden) {
	if (hidden) {
		sprite()->frame(1);
	}
	else { sprite()->frame(0);  }
}

