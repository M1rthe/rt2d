#ifndef ENEMY2_H
#define ENEMY2_H

#include "enemy.h"

/// @brief Enemy2 extends from Enemy
class Enemy2 : public Enemy {

public:
	/// @brief Constructor
	Enemy2();
	/// @brief Destructor
	virtual ~Enemy2();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/// @brief Attack function overrides Enemy attack function
	void attack() override;
};

#endif /* ENEMY2_H */
