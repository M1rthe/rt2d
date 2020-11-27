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
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Rotate color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = player->sprite()->color;
		player->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}

	// ###############################################################
	// Manage clickevents
	// ###############################################################
	mousePosition = Vector2((float)input()->getMouseX(), (float)input()->getMouseY());

	if (input()->getMouseDown(0)) {

		if (mouseIsOn(mousePosition, hud->camouflage1->worldposition(), Vector2(hud->camouflage1->sprite()->width(), hud->camouflage1->sprite()->height()))) { hud->clickedCamouflage1(); }
		else if (mouseIsOn(mousePosition, hud->camouflage2->worldposition(), Vector2(hud->camouflage2->sprite()->width(), hud->camouflage2->sprite()->height()))) { hud->clickedCamouflage2(); }
		else if (mouseIsOn(mousePosition, hud->camouflage3->worldposition(), Vector2(hud->camouflage3->sprite()->width(), hud->camouflage3->sprite()->height()))) { hud->clickedCamouflage3(); }
		else if (!mouseIsOn(mousePosition, hud->camouflagegauge->worldposition(), Vector2(hud->camouflagegauge->sprite()->width(), hud->camouflagegauge->sprite()->height()))) {
			player->newDestination(mousePosition);
		}

	}
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
