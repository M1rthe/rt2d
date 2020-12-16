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
	player->position = Vector2(SWIDTH / 2, SHEIGHT / 2);
	player->finalDestination = player->position;

	hud = new Hud();

	moveByKey = true;

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(map);
	this->addChild(player);
	this->addChild(hud);
}


Level1::~Level1()
{
	// deconstruct and delete the Tree
	this->removeChild(map);
	this->removeChild(player);
	this->removeChild(hud);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete map;
	delete player;
	delete hud;
}

void Level1::update(float deltaTime) {

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
		std::cout << "mouseDown\n";
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
