#ifndef ENEMY_H
#define ENEMY_H

#include <rt2d/entity.h>
#include "collider.h"
#include "basicentity.h"
#include "bullet.h"
#include <rt2d/timer.h>
#include <rt2d/text.h>

using namespace std;

/// @brief Enemy extends from Entity
class Enemy : public Entity {

public:
	/// @brief Constructor
	Enemy(); 
	/// @brief Destructor
	virtual ~Enemy();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	/// @brief get the Rectangle of Enemy
	/// @return Rectangle
	Rectangle getRect();
	/// @brief Attack
	/// @return void
	virtual void attack();
	/// @brief AI controls movement, attack, face directions, sees player, status (? or ! or nothing)
	/// @param deltaTime deltaTime
	/// @param playerPosition Use playerPosition to calculate Enemy direction & more
	/// @param playerIsCamouflaged seesPlayer function(gets called in this function) needs that data
	/// @param playerIsMoving Enemy can hear you moving if you are near
	/// @return Vector2
	Vector2 ai(float deltaTime, Rectangle playerRect, bool playerIsCamouflaged, bool playerIsMoving);

	///< @brief Type of enemy (Shoots or Hits)
	int type;

	///< @brief Use it to keep track of Enemy scale
	float mirror;

	///< @brief How near the player is supposed to be to attack
	int actionDistance;
	///< @brief Bullets are made in scene so this is how level knows when to shoot
	bool isAttackedThisFrame = false;
	///< @brief This way Enemy doesn't attack every frame
	double attackCooldown = 0.0;
	///< @brief This way Enemy doesn't attack every frame
	double timeFirstAttacked = 0.0;
	///< @brief This way Enemy can't attack instantly after turning around
	double timeWhenTurnedAround = 0.0;
	///< @brief This way Enemy can't attack instantly after turning around
	double timeToTurnAround = 0.0;
	///< @brief This way Enemy searches a little longer when lost sight of Player
	double timeLostPlayer = -3.0;
	Vector2 dirWhenLostPlayer;

	double timeFirstSeenPlayer = 0.0;

	///< @brief Timer
	Timer time;

	///< @brief Remeber old position so when you collide you get teleported back
	Vector2 oldPosition;
	///< @brief If collided teleport back
	bool collided;
	///< @brief List of colliders (tiles)
	vector<Rectangle> colliders;
	//Rectangle playerCollider = Rectangle(0, 0, 0, 0);

	///< @brief Status of Enemy (? or ! or nothing)
	Text* questionMark;

	///< @brief If Enemy sees Player most of it's AI kicks in
	bool canSeePlayer = false;

private:
	/// @brief Makes sure Enemy can't look through walls
	/// @param playerPos Helps to calculate direction
	/// @param x1, y1, x2, y2, x3, y3, x4, y4 is needed for the Line-Line Intersection calculation (https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection)
	/// @return bool
	bool cast(Vector2 playerPos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	/// @brief Enemy sees player depending on:
	/// - Camouflage 
	/// - Face direction
	/// - Distance
	/// - Colliders (walls)
	/// @param playerPosition to cast lines between enemy & player
	/// @param playerIsCamouflaged
	/// @param playerIsMoving Enemy can hear Player move when near
	/// @param direction
	/// @param distance
	/// @return bool
	bool seesPlayer(Vector2 playerPosition_, bool playerIsCamouflaged_, bool playerIsMoving_, Vector2 direction_, float distance_);
	/// @brief Move
	/// @param deltaTime
	/// @param playerPosition
	/// @param direction
	/// @param distance
	/// @return void
	void move(float deltaTime, Vector2 direction);
	
	///< @brief Check if Enemy collides with a wall
	bool collidingWithWall = false;
	Vector2 lastSeenPlayerPos;

	//bool playerWasMoving = false;
};

#endif /* ENEMY_H */
