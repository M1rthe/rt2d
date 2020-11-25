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

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(map);
	this->addChild(player);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(map);
	this->removeChild(player);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete map;
	delete player;
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
}
