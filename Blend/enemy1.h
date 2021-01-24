#ifndef ENEMY1_H
#define ENEMY1_H

#include "enemy.h"

/// @brief Enemy1 extends from Enemy
class Enemy1 : public Enemy {

public:
	/// @brief Constructor
	Enemy1();
	/// @brief Destructor
	virtual ~Enemy1();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/// @brief Attack function overrides Enemy attack function
	void attack() override;
};

#endif /* ENEMY_H */
