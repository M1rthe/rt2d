#ifndef ENEMY2_H
#define ENEMY2_H

#include "enemy.h"

class Enemy2 : public Enemy {

public:

	//Standard entity function
	Enemy2(); 
	virtual ~Enemy2();
	virtual void update(float deltaTime);
	//Functions

	//Variables

private:

	//Functions
	void attack(Vector2 pos, Vector2 dir) override;
	//Variables
};

#endif /* ENEMY2_H */
