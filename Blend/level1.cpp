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
	reset();

	Enemy1* e1 = new Enemy1();
	enemies.push_back(e1);
	e1->position = Vector2(2800, 1300);
	layers[2]->addChild(e1);

	/*
	Enemy2* e2 = new Enemy2();
	enemies.push_back(e2);
	e2->position = Vector2(2600, 1500);
	layers[2]->addChild(e2);
	*/

	Item* donut = new Item("Donut");
	items.push_back(donut);
	donut->position = Vector2(2100, 1500);
	layers[0]->addChild(map);
	layers[1]->addChild(donut);
	layers[2]->addChild(player);
	layers[5]->addChild(hud);
}


Level1::~Level1()
{
	//RemoveChild (addChild)
	/*
	this->removeChild(map);
	this->removeChild(player);
	this->removeChild(hud);
	*/

	//Delete (new)
	delete map;
	delete player;
	delete hud;

	//Enemies
	for (int i = 0; i < enemies.size(); i++) {
		//this->removeChild(enemies[i]);
		delete enemies[i]; 
		enemies[i] = nullptr; 
	}
	enemies.clear();

	//Bullets
	for (int i = 0; i < bullets.size(); i++) {
		//this->removeChild(bullets[i]);
		delete bullets[i];
		bullets[i] = nullptr;
	}
	bullets.clear();

	//Items
	for (int i = 0; i < items.size(); i++) {
		//this->removeChild(items[i]);
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
	std::cout << "addBullet(pos:"<<pos<<", dir:"<<dir<<")\n";
	Bullet* bullet = new Bullet(pos, dir);
	bullets.push_back(bullet);
	layers[4]->addChild(bullet);
}

void Level1::instantiate() {
	map = new Map();
	player = new Player();
	hud = new Hud();
}

void Level1::reset() {
	//Player
	player->position = Vector2(3000, 1500);
	player->finalDestination = player->position;
	//Hud
	hud->mission->message("mission");
	//Booleans
	moveByKey = true;
	//Set stuff
	player->colliders = map->tilesWithCollider;
}

void Level1::update(float deltaTime) {

	// ###############################################################
	// Item collision
	// ###############################################################
	//layers[4]->ddClear();

	for (int i = items.size() - 1; i >= 0; i--) {

		Point playerPos = Point2(player->position.x - ((player->sprite()->width()*player->scale.x / 2)*0.65), player->position.y);
		if (player->facing == RIGHT) { playerPos = Point2(player->position.x + ((player->sprite()->width() * player->scale.x / 2) * 0.65), player->position.y); }
		
		//layers[4]->ddLine(playerPos, items[i]->position, RED);

		Point2 idk = (playerPos - items[i]->position);
		float dist = sqrt(idk.x * idk.x + idk.y * idk.y);

		if (dist < 30) {
			if (items[i]->name == "Donut") {
				if (player->tongueIsStickedOut) {
					std::cout << "Eated donut\n";
					//Delete
					layers[1]->removeChild(items[i]);
					delete items[i];
					items.erase(items.begin() + i);
				}
			}
			std::cout << "\n####################\n";
		}
	}

	// ###############################################################
	// Bullets
	// ###############################################################
	for (int i = bullets.size() - 1; i >= 0; i--) {

		Point3 idk = (player->position - bullets[i]->position);
		float dist = sqrt(idk.x * idk.x + idk.y * idk.y);

		if (dist > 1000) { //Delete bullets the player can't see
			layers[4]->removeChild(bullets[i]);
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
	// ###############################################################
	// Enemies
	// ###############################################################
	for (int i = 0; i < enemies.size(); i++) {

		//Collision
		player->movingColliders.clear();
		player->movingColliders.push_back(enemies[i]->getRect());
		//Layers
		if (player->position.y > enemies[i]->position.y + 50) {
			layers[2]->addChild(enemies[i]);
			layers[3]->addChild(player);
		}
		else {
			layers[2]->addChild(player);
			layers[3]->addChild(enemies[i]);
		}
	}

	// ###############################################################
	// Hidden Or Not
	// ###############################################################	
	int overlapping = map->findMostOverlappedTile(Vector2(player->position.x, player->position.y), Vector2(player->scale.x * player->sprite()->size.x, player->scale.y * player->sprite()->size.y), player->camouflageFrame, player->facing);
	if (overlapping > 45) { 
		hud->camouflagegauge->overlappingSpace->message("HIDDEN");
	} 
	if (overlapping <= 45) {
		hud->camouflagegauge->overlappingSpace->message("NOT HIDDEN");
		for (int i = 0; i < enemies.size(); i++) {

			//AI
			Vector2 direction = enemies[i]->ai(deltaTime, player->position);

			//Shooting
			if (enemies[i]->isAttacking) {
				if (enemies[i]->attackCooldownCounter > enemies[i]->attackCooldown) {
					//if (enemies[i]->scale.x < 0) { direction.x *= -1; }
					addBullet(enemies[i]->position, direction);
					enemies[i]->attackCooldownCounter = 0;
				}
				enemies[i]->attackCooldownCounter++;
			}
		}
	}	

	// ###############################################################
	// Manage Mouse Events
	// ###############################################################

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


	// ###############################################################
	// Camera
	// ###############################################################

	this->camera()->position = player->position;
	this->camera()->position.z = 650;

	this->hud->position = Point(player->position.x - SWIDTH / 2, player->position.y - SHEIGHT / 2);
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
