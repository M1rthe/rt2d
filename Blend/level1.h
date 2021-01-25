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

/// @brief Level1 extends from Scene
class Level1 : public Scene {

public:
	/// @brief Constructor
	Level1();
	/// @brief Destructor
	virtual ~Level1();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:

	void instantiate();
	void reset();
	void die();
	void win();

	/// @brief Add bullet to scene
	/// @param position 
	/// @param direction
	/// @return void
	void addBullet(Vector2 pos, Vector2 dir);

	/// @brief Used to check if mouse is on button
	/// @param position 
	/// @param within position
	/// @param width & height
	/// @return bool
	bool mouseIsOn(Vector2 position, Vector2 withinPos, Vector2 s);

	Map* map;
	Hud* hud;
	Player* player;
	Enemy1* e1;
	Enemy2* e2;
	Enemy1* e3;
	///< @brief win/die message
	Text* winOrDie;

	///< @brief Timer
	Timer t;

	///< @brief Current camouflage
	int currentCamouflage = 3;

	///< @brief Move by key or move by click
	bool moveByKey = true;

	///< @brief Mouse position
	Vector2 mousePosition;

	///< @brief List of enemies
	vector<Enemy*> enemies;
	///< @brief List of bullets
	vector<Bullet*> bullets;
	///< @brief List of items
	vector<Item*> items;
	///< @brief List of layers, meant for: [0]Map - [1]items - [2]player - [3]enemy - [4]bullets - [5]HUD
	vector<BasicEntity*> layers;
	///< @brief top layer for forloop
	unsigned int topLayer = 5; 

	///< @brief Offset for win/die text
	int offSetWinDie = 0;
	///< @brief Used for no instant quit when won
	double timeQuit = 0;
	///< @brief Used for no instant quit when won
	bool won = false;
	///< @brief Used for no instant reset when died
	double timeOfDead = 0;
	///< @brief Used for no instant reset when died
	bool dead = false;

	bool hasDonut = false;
};

#endif /* LEVEL1_H */
