/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef LEVEL1_H
#define LEVEL1_H

#include <rt2d/scene.h>
#include <rt2d/camera.h>
#include "player.h"
#include "enemy.h"
#include "enemy1.h"
#include "enemy2.h"
#include "item.h"
#include "map.h"
#include "hud.h"
#include "collider.h"

using namespace std;

/// @brief The MyScene class is the Scene implementation.
class Level1 : public Scene {

public:

	Hud* hud;

	/// @brief Constructor
	Level1();
	/// @brief Destructor
	virtual ~Level1();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void addBullet(Vector2 pos, Vector2 dir);

private:
	Map* map;
	Player* player;
	Enemy* human;

	Timer t;

	int bulletCooldown = 0;

	int currentCamouflage = 3;
	bool moveByKey = true;

	Vector2 mousePosition;
	bool mouseIsOn(Vector2 position, Vector2 withinPos, Vector2 s);

	vector<Enemy*> enemies;
	vector<Bullet*> bullets;
	vector<Item*> items;

	vector<BasicEntity*> layers;
	unsigned int topLayer = 5; //Map - items - player - enemy - bullets - HUD

	void instantiate();
	void reset();
};

#endif /* LEVEL1_H */
