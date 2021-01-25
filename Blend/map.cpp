/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "map.h"

Map::Map() : Entity() {

	gridwidth = 64;
	gridheight = 32;
	cellwidth = 64;
	cellheight = 64;

	grid = new BasicEntity();
	grid->addGrid("assets/mytileset.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);

	int tileCounter = 0;

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

	calculateTiles();
}

Map::~Map() {
	removeChild(grid);
	delete grid;
	delete[] level;
	tilesWithCollision.clear();
}

void Map::update(float deltaTime) {

}

void Map::changeTiles(string find, string replaceString) {

	for (int i = 0; i < grid->spritebatch().size(); i++) {

		if (find == level[i]) {
			std::cout << "i: "<<i<<"\n";
			level[i] = replaceString;
		}
	}
}

void Map::calculateTiles() {

	reloadedMap = true;

	tilesWithCollision.clear();
	tilesWithCollider.clear();

	for (int i = 0; i < grid->spritebatch().size(); i++) {

		//Collision (t or f)
		if (level[i].length() > 0) {
			if (level[i].at(0) == 't') { 
				tilesWithCollision.push_back(i);
			}
		}

		int f = 0; //Grass

		if (level[i].length() > 1) {
			if (level[i].at(1) == 'd') {
				if (level[i].length() > 2) {
					if (level[i].at(2) == 'i') { f = 1; } //DIrt
					if (level[i].at(2) == 't') {
						f = 11;
						if (level[i].length() > 3) {
							if (level[i].at(3) == 'o') { f = 14; } //DoorOpen 14
						}
					} //DoorTop		//11
					if (level[i].at(2) == 'b') {
						f = 12;
						if (level[i].length() > 3) {
							if (level[i].at(3) == 'o') { f = 14; } //DoorOpen 14
						}
					} //DoorBottom		//12
				}
			}
			if (level[i].at(1) == 'b') {
				if (level[i].length() > 2) {
					if (level[i].at(2) == 'r') { f = 2; } //BRicks
					if (level[i].at(2) == 't') { f = 8; } //BarsTop
					if (level[i].at(2) == 'b') { f = 9; } //BarsBottom
					if (level[i].at(2) == 'u') { f = 13; } //BUsh
				}
			}
			if (level[i].at(1) == 'w') {
				if (level[i].length() > 2) {
					if (level[i].at(2) == 'a') { f = 3; } //WAter
				}
			}
			if (level[i].at(1) == 's') {
				if (level[i].length() > 2) {
					if (level[i].at(2) == 'b') { f = 5; } //StoneBricks
					if (level[i].at(2) == 't') { f = 7; } //STone
				}
			}
			if (level[i].at(1) == 'p') {
				if (level[i].length() > 2) {
					if (level[i].at(2) == 'l') { f = 10; } //PLanks
				}
			}
			if (level[i].at(1) == 'l') {
				if (level[i].length() > 2) {
					if (level[i].at(2) == 'u') { f = 6; } //LUchtrooster
				}
			}
			if (level[i].at(1) == 'c') { //Color
				f = 4;
				grid->spritebatch()[i]->color = WHITE;

				if (level[i].length() > 2) {
					//Color
					if (level[i].at(2) == 'r') { grid->spritebatch()[i]->color = RED; }
					if (level[i].at(2) == 'o') { grid->spritebatch()[i]->color = ORANGE; }
					if (level[i].at(2) == 'y') { grid->spritebatch()[i]->color = YELLOW; }
					if (level[i].at(2) == 'g') { grid->spritebatch()[i]->color = GRAY; }
					if (level[i].at(2) == 'b') { grid->spritebatch()[i]->color = BLUE; }
					if (level[i].at(2) == 'm') { grid->spritebatch()[i]->color = MAGENTA; }
				}
			}
		}

		if (level[i].at(level[i].length() - 1) == 'F') { grid->spritebatch()[i]->spritescale.x = -1; } else { grid->spritebatch()[i]->spritescale.x = 1; }

		grid->spritebatch()[i]->filter(0);
		grid->spritebatch()[i]->frame(f);
	}

	for (int j = 0; j < tilesWithCollision.size(); j++) {
		tilesWithCollider.push_back(getRectTile(j)); // NO getRectTile(tilesWithCollision[j]), tilesWithCollision happens in function itself
	}
}

int Map::findMostOverlappedTile(Vector2 pos, Vector2 size, int camouflage, int facing) {

	float mostOverlapped = -9999;
	int tileCounter = 0;
	float totalOverlapped = 0;

	float totalOverlappedX = 0;
	float totalOverlappedY = 0;

	size.x -= 40;

	// Staart & hoofd rekenen niet mee, 1 tile is niet genoeg overlapping als het alleen gevult zou zijn met je staart
	if (facing == 0) { pos.x += 5; size.x -= 10; }
	if (facing == 1) { pos.x -= 5; size.x -= 10; }
	pos.y += 10;
	size.y -= 40;
	
	//Loop through tiles
	for (int x = 0; x < gridwidth; x++) {
		for (int y = 0; y < gridheight; y++) {

			//Check if camouflage is correct
			float dist = CalculateDistance(grid->spritebatch()[tileCounter]->spriteposition, pos);

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

				float playerRight = pos.x + size.x / 2;
				float tileRight = grid->spritebatch()[tileCounter]->spriteposition.x + cellwidth / 2;
				float playerLeft = pos.x - size.x / 2;
				float tileLeft = grid->spritebatch()[tileCounter]->spriteposition.x - cellwidth / 2;
				float playerTop = pos.y - size.y / 2;
				float tileTop = grid->spritebatch()[tileCounter]->spriteposition.y - cellheight / 2;
				float playerBottom = pos.y + size.y / 2;
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
				 
				overlapped = round((overlappedX * overlappedY) / 10);
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

Rectangle Map::getRectTile(int tile) {

	/*
	return Rectangle(
		grid->spritebatch()[tilesWithCollision[tile]]->spriteposition.x + cellwidth,
		grid->spritebatch()[tilesWithCollision[tile]]->spriteposition.y - 5,
		cellwidth / 2,
		cellheight / 2
	);
	*/

	return Rectangle(
		grid->spritebatch()[tilesWithCollision[tile]]->spriteposition.x - (cellwidth / 2),
		grid->spritebatch()[tilesWithCollision[tile]]->spriteposition.y - (cellheight / 2),
		cellwidth,
		cellheight
	);
}
