#ifndef ENEMY1_H
#define ENEMY1_H

#include "enemy.h"

class Enemy1 : public Enemy {

public:

	//Standard entity function
	Enemy1();
	virtual ~Enemy1();
	virtual void update(float deltaTime);
	//Functions

	//Variables

private:

	//Functions
	void attack() override;
};

#endif /* ENEMY_H */
