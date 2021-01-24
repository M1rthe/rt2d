#ifndef BULLET_H
#define BULLET_H

#include <rt2d/entity.h>
#include "collider.h"

/// @brief Bullet extends from Entity
class Bullet : public Entity {

public:
	/// @brief constructor
	/// @param direction The direction the bullets moves
	Bullet(Vector2 _direction);
	/// @brief destructor
	virtual ~Bullet();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	/// @brief get the Rectangle of Bullet
	/// @return Rectangle
	Rectangle getRect();

private:
	///< @brief direction The direction the bullets moves. It is also used to calculate the rotation
	Vector2 direction;
};

#endif /* BULLET_H */
