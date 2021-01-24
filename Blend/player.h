#ifndef PLAYER_H
#define PLAYER_H

#include <rt2d/entity.h>
#include <cmath>
#include <rt2d/pointx.h>
#include "basicentity.h"
#include <rt2d/timer.h>
#include <string>
#include "map.h"

using namespace std;

#define LEFT 0 
#define RIGHT 1

/// @brief Player extends from Entity
class Player : public Entity {

public:
	/// @brief Constructor
	Player();
	/// @brief Destructor
	virtual ~Player();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	/// @brief Check for input (wasd, esc, enz.)
	/// @param deltaTime
	/// @param map
	/// @param moveWithKeys
	/// @return void
	void check4input(float dt, Map* map, bool moveWithKeys);

	/// @brief Click camouflage
	/// @param camouflage
	/// @return void
	void clickCamouflage(int c);

	/// @brief newDestination (for click2go movement)
	/// @param destination
	/// @return void
	void newDestination(Vector2 d);

	/// @brief Get rectangle 
	/// @param wholeBody or only legs
	/// @return Rectangle
	Rectangle getRect(int wholeBody);

	int camouflageFrame = 65; //doesnt exists, so its just green, default cameleon

	Vector2 finalDestination; ///< @brief finalDestination (for click2go movement)

	int facing = RIGHT;

	bool tongueIsStickedOut = false;

	///< @brief List of colliders (tiles)
	vector<Rectangle> colliders;
	//vector<Rectangle> movingColliders;

	bool isMoving = false;

private:
	/// @brief Animation
	/// @return void
	void animation();

	/// @brief Consume
	/// @return void
	void consume();

	/// @brief Move
	/// @param direction
	/// @param speed
	/// @param deltaTime
	/// @return void
	void move(Vector2 direction, float speed, float deltaTime);

	Vector2 oldPosition;
	bool collided;

	Timer time;

	double nextActionTime = 0.0;
	double timeFirstStickedOutTongue = 0.0;

	Vector2 direction;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 mousePosition;
	float speed;
	float topspeed;
	float distance;
};

#endif /* PLAYER_H */