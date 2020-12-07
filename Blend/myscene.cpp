/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	map = new Map();

	player = new Player();
	player->position = Vector2(SWIDTH / 2, SHEIGHT / 2);
	player->finalDestination = player->position;		

	hud = new Hud();

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(map);
	this->addChild(player);
	this->addChild(hud);
}


MyScene::~MyScene()
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

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Manage keyboard events
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	if (input()->getKeyUp(KeyCode::C)) {
		player->consume();
	}

	Vector2 dir = Vector2(0,0);
	player->isMoving = false;

	if (input()->getKey(KeyCode::W) || input()->getKey(KeyCode::Up)) {
		if (player->position.y -330 >= map->position.y) {
			dir.y = -1;
			player->isMoving = true;
		}
	}
	if (input()->getKey(KeyCode::A) || input()->getKey(KeyCode::Left)) {
		if (player->position.x -610 >= map->position.x) {
			dir.x = -1;
			player->facing = "left";
			player->isMoving = true;
		}
	}
	if (input()->getKey(KeyCode::S) || input()->getKey(KeyCode::Down)) {
		if (player->position.y + 390 <= map->position.y + (map->cellheight * map->gridheight)) {
			dir.y = 1;
			player->isMoving = true;
		}
	}
	if (input()->getKey(KeyCode::D) || input()->getKey(KeyCode::Right)) {
		if (player->position.x + 670 <= map->position.x + (map->cellwidth * map->gridwidth)) {
			dir.x = 1;
			player->facing = "right";
			player->isMoving = true;
		}
	}

	dir.normalize();

	player->moveByKey(deltaTime, dir);
	//player->moveByClick(deltaTime);

	// ###############################################################
	// Manage clickevents
	// ###############################################################
	mousePosition = Vector2(Vector2(input()->getMouseX() + camera()->position.x - SWIDTH / 2, input()->getMouseY() + camera()->position.y - SHEIGHT / 2));

	if (input()->getMouseDown(0)) {

		if (mouseIsOn(mousePosition, hud->camouflage1->worldposition(), Vector2(hud->camouflage1->sprite()->width(), hud->camouflage1->sprite()->height()))) { hud->clickedCamouflage1(); }
		else if (mouseIsOn(mousePosition, hud->camouflage2->worldposition(), Vector2(hud->camouflage2->sprite()->width(), hud->camouflage2->sprite()->height()))) { hud->clickedCamouflage2(); }
		else if (mouseIsOn(mousePosition, hud->camouflage3->worldposition(), Vector2(hud->camouflage3->sprite()->width(), hud->camouflage3->sprite()->height()))) { hud->clickedCamouflage3(); }
		
		else if (!mouseIsOn(mousePosition, hud->camouflagegauge->worldposition(), Vector2(hud->camouflagegauge->sprite()->width(), hud->camouflagegauge->sprite()->height()))) {
			player->newDestination(mousePosition);
		}
	}

	// ###############################################################
	// Camera
	// ###############################################################
	this->hud->position = Point(player->position.x - SWIDTH / 2, player->position.y - SHEIGHT / 2);
	this->camera()->position = player->position;
	this->camera()->position.z = 650;
}

bool MyScene::mouseIsOn(Vector2 mousePos, Vector2 entityPos, Vector2 s) {

	if (mousePos.x >= entityPos.x - s.x / 2 &&
		mousePos.x <= entityPos.x + s.x / 2 &&
		mousePos.y >= entityPos.y - s.y / 2 &&
		mousePos.y <= entityPos.y + s.y / 2) {
		return true;
	}

	return false;
}
