/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "map.h"

Map::Map() : Entity() {

	gridwidth = 64;
	gridheight = 16;
	cellwidth = 64;
	cellheight = 64;

	grid = new BasicEntity();
	grid->addGrid("assets/mytileset.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);

	int tileCounter = 0;

	int w = 32;
	int h = 16;

	//Loop through tiles
	for (int x = 0; x < gridwidth; x++) {
		for (int y = 0; y < gridheight; y++) {

			Sprite* tile = grid->spritebatch()[tileCounter];
			tile->color = RGBAColor(255, 255, 255, 255);
			tile->frame(0);
			tileCounter++;
		}
	}

	addChild(grid);

	for (int i = 0; i < grid->spritebatch().size(); i++) {
		int f = 0;
		if (level[i] == "d") { f = 1; }
		if (level[i] == "b") { f = 2; }
		if (level[i] == "w") { f = 3; }
		if (level[i].at(0) == 'c') {
			f = 4;
			grid->spritebatch()[i]->color = WHITE;

			if (level[i].length() > 1) {
				if (level[i].at(1) == 'r') { grid->spritebatch()[i]->color = RED; }
				if (level[i].at(1) == 'o') { grid->spritebatch()[i]->color = ORANGE; }
				if (level[i].at(1) == 'y') { grid->spritebatch()[i]->color = YELLOW; }
				if (level[i].at(1) == 'g') { grid->spritebatch()[i]->color = GREEN; }
				if (level[i].at(1) == 'b') { grid->spritebatch()[i]->color = BLUE; }
				if (level[i].at(1) == 'm') { grid->spritebatch()[i]->color = MAGENTA; }
			}
		}
		grid->spritebatch()[i]->filter(0);
		grid->spritebatch()[i]->frame(f);
	}
}

Map::~Map() {
	removeChild(grid);
	delete grid;
	delete[] level;
}

int Map::findMostOverlappedTile(Vector2 position, Vector2 size, int camouflage, int facing) {

	float mostOverlapped = -9999;
	int tileCounter = 0;
	float totalOverlapped = 0;

	float totalOverlappedX = 0;
	float totalOverlappedY = 0;

	size.x -= 40;

	// Staart & hoofd rekenen niet mee, 1 tile is niet genoeg overlapping als het alleen gevult zou zijn met je staart
	if (facing == 0) { position.x -= 0; size.x -= 20; }
	if (facing == 1) { position.x += 0; size.x -= 20; }
	position.y += 10;
	size.y -= 20;
	
	//Loop through tiles
	for (int x = 0; x < gridwidth; x++) {
		for (int y = 0; y < gridheight; y++) {

			//Check if camouflage is correct
			float dist = CalculateDistance(grid->spritebatch()[tileCounter]->spriteposition, position);

			if (grid->spritebatch()[tileCounter]->frame() == camouflage && dist < 130) {

				//Get overlap
				float overlapped = -9999;
				float overlappedX = -9999;
				float overlappedY = -9999;
				//Together
				float togetherX = cellwidth + size.x;
				float togetherY = cellheight + size.y;
				//Total
				float farestRight = 0;
				float farestLeft = 0;
				float farestTop = 0;
				float farestBottom = 0;

				float playerRight = position.x + size.x / 2;
				float tileRight = grid->spritebatch()[tileCounter]->spriteposition.x + cellwidth / 2;
				float playerLeft = position.x - size.x / 2;
				float tileLeft = grid->spritebatch()[tileCounter]->spriteposition.x - cellwidth / 2;
				float playerTop = position.y - size.y / 2;
				float tileTop = grid->spritebatch()[tileCounter]->spriteposition.y - cellheight / 2;
				float playerBottom = position.y + size.y / 2;
				float tileBottom = grid->spritebatch()[tileCounter]->spriteposition.y + cellheight / 2;

				if (playerTop < tileTop) { farestTop = playerTop; }
				if (playerTop > tileTop) { farestTop = tileTop; }
				if (playerBottom > tileBottom) { farestBottom = playerBottom; }
				if (playerBottom < tileBottom) { farestBottom = tileBottom; }

				if (playerRight > tileRight) { farestRight = playerRight; } // player is right
				if (playerRight < tileRight) { farestRight = tileRight; } // tile is right
				if (playerLeft < tileLeft) { farestLeft = playerLeft; } // player is left
				if (playerLeft > tileLeft) { farestLeft = tileLeft; } // tile is left

				float totalX = farestRight - farestLeft;
				float totalY = farestBottom - farestTop;

				overlappedX = togetherX - totalX;
				overlappedY = togetherY - totalY;
				 
				overlapped = round((overlappedX * overlappedY) / 100);
				if (overlappedX < 0 && overlappedY < 0) { overlapped *= -1; }

				if (overlapped > 0) {
					totalOverlapped += overlapped;
				}
			}

			tileCounter++;
		}
	}

	return totalOverlapped;
}

float Map::CalculateDistance(Vector2 p1, Vector2 p2)
{
	float diffY = p1.y - p2.y;
	float diffX = p1.x - p2.x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}


void Map::update(float deltaTime) {

}