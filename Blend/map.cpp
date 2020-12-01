/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "map.h"

 Map::Map() : Entity() {
	
	gridwidth = 256;
	gridheight = 256;
	cellwidth = 32;
	cellheight = 32;

	grid = new Grid();
	//grid->addGrid("assets/defaultgray.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);
	grid->addGrid("assets/TileSet_not_compressed.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);
	tilesetSprite = new Sprite();

	int tileCounter = 0;

	int w = 128;
	int h = 64;

	//Loop through tiles
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {

			Sprite* tile = grid->spritebatch()[tileCounter];
			tile->color = RGBAColor(255, 255, 255, 255);
			//tile->frame(1);
			tileCounter++;
		}
	}

	addChild(grid);

	/*
	tilesetSprite->setupSpriteTGAPixelBuffer("assets/TileSet_not_compressed.tga", 0, 0); 
	PixelBuffer* tileset = tilesetSprite->texture()->pixels();
	int w = tileset->width;
	int h = tileset->height;
	*/
}

Map::~Map() {
	delete tilesetSprite;
	delete grid;
}

void Map::update(float deltaTime) {

}


