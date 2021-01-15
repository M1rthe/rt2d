/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "level1.h"

Level1::Level1() : Scene()
{
	// start the timer.
	t.start();

	map = new Map();

	player = new Player();
	player->position = Vector2(680, 1500);
	player->finalDestination = player->position;

	human = new Enemy();
	human->position = Vector2(1800, 1300);

	hud = new Hud();

	hud->mission->message("mission");

	moveByKey = true;

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(map);
	this->addChild(player);
	this->addChild(human);
	this->addChild(hud);
}


Level1::~Level1()
{
	// deconstruct and delete the Tree
	this->removeChild(map);
	this->removeChild(player);
	this->removeChild(hud);
	this->removeChild(human);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete map;
	delete player;
	delete hud;
	delete human;
}

void Level1::update(float deltaTime) {

	int overlapping = map->findMostOverlappedTile(Vector2(player->position.x, player->position.y), Vector2(player->scale.x * player->sprite()->size.x, player->scale.y * player->sprite()->size.y), player->camouflageFrame, player->facing);
	std::cout << "overlapping: "<< overlapping<<", supposed to be > 45\n";
	if (overlapping > 45) { 
		hud->camouflagegauge->overlappingSpace->message("HIDDEN");
		human->playerIsHidden = false;
		//hud->camouflagegauge->overlappingSpace->message("HIDDEN("+ to_string(overlapping) +")");
	} if (overlapping <= 45) {
		hud->camouflagegauge->overlappingSpace->message("NOT HIDDEN");
		human->playerIsHidden = true;
		//hud->camouflagegauge->overlappingSpace->message("NOT HIDDEN(" + to_string(overlapping) + ")");
	}

	//dhud->camouflagegauge->overlappingSpace->message(to_string(overlapping));

	this->hud->position = Point(player->position.x - SWIDTH / 2, player->position.y - SHEIGHT / 2);

	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Manage clickevents
	// ###############################################################
	player->check4input(deltaTime, map, true);

	mousePosition = Vector2(Vector2(input()->getMouseX() + camera()->position.x - SWIDTH / 2, input()->getMouseY() + camera()->position.y - SHEIGHT / 2));

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

	// ###############################################################
	// Collision
	// ###############################################################
	/*
	player->limitLeft = false;
	player->limitUp = false;
	player->limitDown = false;
	player->limitRight = false;

	for (int i = 0; i < map->tilesWithCollider.size(); i++) {
		//player->collideWithTile(map->getRectTile(i));
		if (Collider::rectangle2rectangle(map->getRectTile(i), player->getRect())) {
			std::cout << "Tile[" << i << "]: ";
			if (player->getRect().y + player->getRect().height - 11 < map->getRectTile(i).y) {
				std::cout << "Above. ";
				player->limitDown = true;
			}
			if (player->getRect().y + 11 > map->getRectTile(i).y + map->getRectTile(i).height) {
				std::cout << "Below. ";
				player->limitUp = true;
			}
			if (player->getRect().x + player->getRect().width - 11 < map->getRectTile(i).x) {
				std::cout << "Left. ";
				player->limitRight = true;
			}
			if (player->getRect().x + 11 > map->getRectTile(i).x + map->getRectTile(i).width) {
				std::cout << "Right. ";
				player->limitLeft = true;
			}
		}
		
	}*/
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
