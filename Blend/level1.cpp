/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "level1.h"

Level1::Level1() : Scene() {

	// start the timer.
	t.start();

	//Layers
	for (unsigned int i = 0; i <= topLayer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	instantiate();

	e1 = new Enemy1();
	enemies.push_back(e1);

	e2 = new Enemy2();
	enemies.push_back(e2);

	e3 = new Enemy1();
	enemies.push_back(e3);

	Item* donut = new Item("Donut");
	items.push_back(donut);
	donut->position = Vector2(1600, 1300);

	reset();

	layers[0]->addChild(map);
	layers[1]->addChild(donut);
	layers[2]->addChild(player);
	layers[3]->addChild(e1);
	layers[3]->addChild(e2);
	layers[3]->addChild(e3);
	layers[5]->addChild(hud);
	layers[5]->addChild(winOrDie);
}

Level1::~Level1() {
	//Delete (new)
	delete map;
	delete player;
	delete hud;
	delete winOrDie;
	delete e1;
	delete e2;
	delete e3;

	//Enemies
	enemies.clear();

	//Bullets
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i];
		bullets[i] = nullptr;
	}
	bullets.clear();

	//Items
	for (int i = 0; i < items.size(); i++) {
		delete items[i];
		items[i] = nullptr;
	}
	items.clear();

	//Layers (Map[0] - items[1] - player[2] - enemy[3] - bullets[4] - HUD[5])
	for (int i = 0; i < layers.size(); i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = nullptr;
	}
	layers.clear();
}

void Level1::addBullet(Vector2 pos, Vector2 dir) {
	Bullet* bullet = new Bullet(dir);
	bullet->position = pos;
	bullets.push_back(bullet);
	layers[4]->addChild(bullet);
}

void Level1::instantiate() {
	map = new Map();
	player = new Player();
	hud = new Hud();
	winOrDie = new Text();
}

void Level1::reset() {
	//Player
	player->position = Vector2(700, 1300);
	player->finalDestination = player->position;
	player->clickCamouflage(1);
	currentCamouflage = 1;
	//Hud
	hud->mission->message("Eat the donut laying in the police station, by pressing 'c'. Then get away.");
	winOrDie->scale = Vector2(4, 4);
	//Enemy
	e1->position = Vector2(1800, 830);
	e2->position = Vector2(1750, 1200);
	e3->position = Vector2(1200, 1530);

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->canSeePlayer = false;
	}
	//Booleans
	moveByKey = true;
	//map
	map->changeTiles("tdt", "fdto");
	map->changeTiles("tdb", "fdbo");
	map->changeTiles("tdtF", "fdtoF");
	map->changeTiles("tdbF", "fdboF");
	map->calculateTiles();
	//Set stuff
	player->colliders = map->tilesWithCollider;
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->colliders = map->tilesWithCollider;
	}
}

void Level1::update(float deltaTime) {

	if (!Collider::rectangle2rectangle(player->getRect(0), Rectangle(928, 416, 1088, 1152))) {
		if (hasDonut) {
			win();
		}
	}

	if (map->reloadedMap) {
		map->reloadedMap = false;
		//std::cout << "\nRELOAD MAP\n\n";
		player->colliders = map->tilesWithCollider;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->colliders = map->tilesWithCollider;
		}
	}

	layers[4]->ddClear();

	/*for (int i = 0; i < enemies.size(); i++) {
		for (int castI = 0; castI <= 5; castI++) {
			int h = enemies[i]->sprite()->height() * enemies[i]->scale.y;

			Vector2 _enemyPos = Vector2(enemies[i]->position.x + (enemies[i]->getRect().width / 2), enemies[i]->position.y - (h - (h / 6 * (castI+0.5))));
			_enemyPos.y += h / 2;
			layers[4]->ddLine(player->position, _enemyPos, RED);
		}
	}*/

	this->hud->position = Point(player->position.x - SWIDTH / 2, player->position.y - SHEIGHT / 2);
	winOrDie->position = Point(player->position.x - SWIDTH / 2 + offSetWinDie, player->position.y);

	// ###############################################################
	// Item collision
	// ###############################################################

	for (int i = items.size() - 1; i >= 0; i--) {

		Point playerPos = Point2(player->position.x - ((player->sprite()->width()*player->scale.x / 2)*0.65), player->position.y);
		if (player->facing == RIGHT) { playerPos = Point2(player->position.x + ((player->sprite()->width() * player->scale.x / 2) * 0.65), player->position.y); }
		
		Point2 idk = (playerPos - items[i]->position);
		float dist = sqrt(idk.x * idk.x + idk.y * idk.y);

		if (dist < 30) {
			if (items[i]->name == "Donut") {
				if (player->tongueIsStickedOut) {
					hasDonut = true;
					//
					map->changeTiles("fdto", "tdt");
					map->changeTiles("fdbo", "tdb");
					map->changeTiles("fdtoF", "tdtF");
					map->changeTiles("fdboF", "tdbF");
					//std::cout << "SHOULD RELOAD MAP\n";
					map->calculateTiles();
					//Delete
					layers[1]->removeChild(items[i]);
					delete items[i];
					items.erase(items.begin() + i);
				}
			}
		}
	}

	// ###############################################################
	// Bullets
	// ###############################################################
	for (int i = bullets.size() - 1; i >= 0; i--) {

		if (!dead) {
			bool removeBullet = false;

			//Collision with player
			if (Collider::rectangle2rectangle(player->getRect(1), bullets[i]->getRect())) {
				die();
			}
			else {

				//Collision with walls
				bool test = false;
				for (int ii = 0; ii < map->tilesWithCollider.size(); ii++) {

					if (Collider::rectangle2rectangle(map->tilesWithCollider[ii], bullets[i]->getRect())) {
						if (bullets[i]->collision) {
							removeBullet = true;
							//std::cout << "Remove bullet\n";
						}
						test = true;
					}

					/*if (!Collider::rectangle2rectangle(map->tilesWithCollider[ii], bullets[i]->getRect())) {
						bullets[i]->collision = true;
						std::cout << "Bullet collides again after being in the air & not in spawn\n";
					}*/
				}
				if (!test) {
					bullets[i]->collision = true;
				}

				//Delete bullets the player can't see
				Point3 idk = (player->position - bullets[i]->position);
				float dist = sqrt(idk.x * idk.x + idk.y * idk.y);

				if (dist > 1000) {
					removeBullet = true;
				}

				if (removeBullet) {
					layers[4]->removeChild(bullets[i]);
					delete bullets[i];
					bullets.erase(bullets.begin() + i);
				}
			}
		}
	}

	// ###############################################################
	// Hidden Or Not
	// ###############################################################	
	int overlapping = map->findMostOverlappedTile(Vector2(player->position.x, player->position.y), Vector2(player->scale.x * player->sprite()->size.x, player->scale.y * player->sprite()->size.y), player->camouflageFrame, player->facing);
	if (overlapping > 45) { 
		hud->camouflagegauge->isHidden(true);
	} 
	if (overlapping <= 45) {
		hud->camouflagegauge->isHidden(false);
	}	

	// ###############################################################
	// Enemies
	// ###############################################################
	for (int i = 0; i < enemies.size(); i++) {

		//enemies[i]->playerCollider = player->getRect(1);

		//AI
		Vector2 direction = enemies[i]->ai(deltaTime, player->getRect(1), overlapping <= 45, player->isMoving);

		//Shooting
		if (enemies[i]->shootThisFrame && !dead && !won) {
			addBullet(enemies[i]->position, direction);
		}
		if (enemies[i]->stabThisFrame && !dead && !won) {
			//std::cout << "DIE\n";
			die();
		}

		//Layers
		if (player->getRect(0).y > enemies[i]->getRect().y) {
			layers[2]->addChild(enemies[i]);
			layers[3]->addChild(player);
		}
		else {
			layers[2]->addChild(player);
			layers[3]->addChild(enemies[i]);
		}
	}

	// ###############################################################
	// Manage Mouse Events
	// ###############################################################

	if (!dead) {
		player->check4input(deltaTime, map, true);

		mousePosition = Vector2(Vector2(input()->getMouseX() + camera()->position.x - SWIDTH / 2, input()->getMouseY() + camera()->position.y - SHEIGHT / 2));

		if (input()->getKeyUp(KeyCode::Escape)) {
			this->stop();
		}

		if (input()->getMouseDown(0)) {

			if (mouseIsOn(mousePosition, hud->camouflage1->position + hud->position, Vector2(hud->camouflage1->sprite()->width() * hud->camouflage1->scale.x, hud->camouflage1->sprite()->height() * hud->camouflage1->scale.y))) {
				if (currentCamouflage != 1) {
					player->clickCamouflage(1);
					currentCamouflage = 1;
				}
			}
			else if (mouseIsOn(mousePosition, hud->camouflage2->position + hud->position, Vector2(hud->camouflage2->sprite()->width() * hud->camouflage2->scale.x, hud->camouflage2->sprite()->height() * hud->camouflage2->scale.y))) {
				if (currentCamouflage != 2) {
					player->clickCamouflage(2);
					currentCamouflage = 2;
				}
			}
			else if (mouseIsOn(mousePosition, hud->camouflage3->position + hud->position, Vector2(hud->camouflage3->sprite()->width() * hud->camouflage3->scale.x, hud->camouflage3->sprite()->height() * hud->camouflage3->scale.y))) {
				if (currentCamouflage != 3) {
					player->clickCamouflage(3);
					currentCamouflage = 3;
				}
			}
			else if (mouseIsOn(mousePosition, hud->camouflagegauge->position + hud->position, Vector2(hud->camouflage3->sprite()->width(), hud->camouflage3->sprite()->height()))) {

			}
			else {
				player->newDestination(mousePosition);
			}
		}
	}


	// ###############################################################
	// Camera
	// ###############################################################

	this->camera()->position = player->position;
	this->camera()->position.z = 650;

	// ###############################################################
	// Quit
	// ###############################################################
	if (won && t.seconds() > timeQuit) {
		stop();
	}

	if (dead && t.seconds() > timeOfDead) {
		//std::cout << "Respawn\n";
		dead = false;
		timeOfDead = 0;
		winOrDie->clearMessage();

		reset();
	}
}

bool Level1::mouseIsOn(Vector2 mousePos, Vector2 entityPos, Vector2 s) {

	if (mousePos.x >= entityPos.x - s.x / 2 &&
		mousePos.x <= entityPos.x + s.x / 2 &&
		mousePos.y >= entityPos.y - s.y / 2 &&
		mousePos.y <= entityPos.y + s.y / 2) {

		return true;
	}

	return false;
}

void Level1::die() {
	if (!dead) {

		offSetWinDie = 192;
		winOrDie->message("YOU DIED");
		dead = true;

		for (int i = 0; i < bullets.size(); i++) {
			layers[4]->removeChild(bullets[i]);
			delete bullets[i];
			bullets[i] = nullptr;
		}
		bullets.clear();

		timeOfDead = t.seconds() + 3;
	}
}

void Level1::win() {
	if (!won) {
		offSetWinDie = 128;
		winOrDie->message("YOU WON!!");
		won = true;

		/*for (int i = bullets.size() - 1; i >= 0; i--) {
			layers[4]->removeChild(bullets[i]);
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
		bullets.clear();*/

		timeQuit = t.seconds() + 3;
	}
}
