/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "map.h"

 Map::Map() : Entity() {
	
	 std::cout << "test\n\n";

	tilesetSprite = new Sprite();
	tilesetSprite->setupSpriteTGAPixelBuffer("assets/TileSet_not_compressed.tga", 0, 0); 
	PixelBuffer* tileset = tilesetSprite->texture()->pixels();
	int w = tileset->width;
	int h = tileset->height;
	
	std::cout << "\n\width: " << w << " (" << (w / 32) << " tiles)\n";
	std::cout << "height: " << h << " (" << (h / 32) << " tiles)\n\n";
}

Map::~Map() {
	delete tilesetSprite;
}

void Map::update(float deltaTime) {

}


