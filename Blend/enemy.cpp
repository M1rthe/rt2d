#include "enemy.h"

Enemy::Enemy() : Entity() {

	time.start();

	actionDistance = 250;
	this->addSprite("assets/Enemies/Human1.tga");
	this->sprite()->filter(0);
	this->scale = Point2(2.5, 2.5);
	mirror = scale.x;

	questionMark = new Text();
	questionMark->scale = Point2(0.5, 0.5);
	addChild(questionMark);
	questionMark->position.y = -40;
}

Enemy::~Enemy() {
	removeChild(questionMark);
	delete questionMark;
}

void Enemy::update(float deltaTime) {

}

Vector2 Enemy::ai(float deltaTime, Rectangle playerRect, bool playerIsCamouflaged, bool playerIsMoving) {

	Vector2 playerPosition = Vector2(playerRect.x, playerRect.y);

	//Randomly turn around
	if (!canSeePlayer) {
		if (time.seconds() - timeWhenTurnedAround > timeToTurnAround) {
			scale.x *= -1;
			questionMark->scale.x *= -1;

			double f = (double)rand() / RAND_MAX;
			timeToTurnAround = time.seconds() + 5 + f * 15;
		}
	}

	isAttackedThisFrame = false;

	Vector2 enemyPos;

	if (collidingWithWall) {
		//std::cout << "FEET\n";
		enemyPos = Vector2(position.x + (getRect().width / 2), position.y + (sprite()->height() * scale.y));
	}
	else {
		//std::cout << "BODY\n";
		enemyPos = Vector2(position.x + (getRect().width / 2), position.y + (sprite()->height() * scale.y / 2));
	}
	//Movement
	Vector2 enemyPosDirection = playerPosition - enemyPos;
	float enemyPosDistance = sqrt(enemyPosDirection.x * enemyPosDirection.x + enemyPosDirection.y * enemyPosDirection.y);
	enemyPosDirection = Vector2(enemyPosDirection.x / enemyPosDistance, enemyPosDirection.y / enemyPosDistance);
	//Attack
	Vector2 direction = (playerPosition - position); // enemyPos
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction = Vector2(direction.x / distance, direction.y / distance);

	if (canSeePlayer) {

		dirWhenLostPlayer = direction;

		float distance2Body = sqrt((playerPosition - Vector2(position.x + (getRect().width / 2), position.y + (sprite()->height() * scale.y / 3))).x * (playerPosition - Vector2(position.x + (getRect().width / 2), position.y + (sprite()->height() * scale.y / 3))).x + (playerPosition - Vector2(position.x + (getRect().width / 2), position.y + (sprite()->height() * scale.y / 3))).y * (playerPosition - Vector2(position.x + (getRect().width / 2), position.y + (sprite()->height() * scale.y / 3))).y);

		//MOVE
		if (distance2Body > actionDistance) {
			move(deltaTime, enemyPosDirection);
			//std::cout << "MOVE\n";
		}
		//QUESTION MARK
		questionMark->message("!");
		//ATTACK
		if (distance2Body < actionDistance) {
			if (time.seconds() - timeFirstSeenPlayer > 1) { //Because its kinda scary if it turns around and instantly shoots. So I give the enemy half a second to aim
				attack();
				//std::cout << "ATTACK\n";
			}
		}
		//FACING
		if (distance > 5) {
			float scaleBefore = scale.x;
			if (playerPosition.x > position.x) { scale.x = mirror * -1; questionMark->scale.x = -0.5; }
			if (playerPosition.x < position.x) { scale.x = mirror; questionMark->scale.x = 0.5; }
		}
	}

	float distanceBetweenLastSeenPlayerPos = sqrt((lastSeenPlayerPos - position).x * (lastSeenPlayerPos - position).x + (lastSeenPlayerPos - position).y * (lastSeenPlayerPos - position).y);

	if (timeLostPlayer + 3 >= time.seconds() && distanceBetweenLastSeenPlayerPos > 100) {

		move(deltaTime, dirWhenLostPlayer);
	}
	
	//CAN SEE PLAYER
	bool before = canSeePlayer;
	canSeePlayer = seesPlayer(Vector2(playerRect.x, playerRect.y + playerRect.height), playerIsCamouflaged, playerIsMoving, direction, distance);

	//GOT AWAY
	if (canSeePlayer == false && before == true) {
		//std::cout << "got away\n";
		questionMark->message("?");
		timeLostPlayer = time.seconds();
		lastSeenPlayerPos = playerPosition;
		//playerWasMoving = playerIsMoving;
	}
	//Just see
	if (canSeePlayer == true && before == false) {
		//std::cout << "sees player\n";
		timeFirstSeenPlayer = time.seconds();
	}

	if (timeLostPlayer + 3 < time.seconds() && !canSeePlayer) {
		questionMark->clearMessage();
	}

	return direction;
}

void Enemy::attack() { }

Rectangle Enemy::getRect() {
	float scaleX = scale.x;
	if (scaleX < 0) { scaleX *= -1; }

	return Rectangle(
		position.x - (sprite()->width() * scaleX / 2),
		position.y + (sprite()->height() * scale.y / 2) - 30,
		sprite()->width() * scaleX,
		30 //20
	);
}

void Enemy::move(float deltaTime, Vector2 direction) {

	collidingWithWall = false;

	//x
	oldPosition = position;
	position.x += direction.x * 80 * deltaTime;
	collided = false;
	for (int i = 0; i < colliders.size(); i++) { //Not moving (tiles)
		bool collidedBoolX = Collider::rectangle2rectangle(getRect(), colliders[i]);
		if (collidedBoolX) { collided = collidedBoolX; }
	}
	//bool collidedBoolX = Collider::rectangle2rectangle(getRect(), playerCollider);
	//if (collidedBoolX) { if (!collided) { collided = collidedBoolX; } }

	if (collided) { position = oldPosition; collidingWithWall = true; }

	//y
	oldPosition = position;
	position.y += direction.y * 80 * deltaTime;
	collided = false;
	for (int i = 0; i < colliders.size(); i++) { //Not moving (tiles)
		bool collidedBoolY = Collider::rectangle2rectangle(getRect(), colliders[i]);
		if (collidedBoolY) { collided = collidedBoolY; }
	}
	//bool collidedBoolY = Collider::rectangle2rectangle(getRect(), playerCollider);
	//if (collidedBoolY) { if (!collided) { collided = collidedBoolY; } }

	if (collided) { position = oldPosition; collidingWithWall = true; }
}

bool Enemy::seesPlayer(Vector2 playerPosition_, bool playerIsCamouflaged_, bool playerIsMoving_, Vector2 direction_, float distance_) {

	bool boolSeesPlayer = playerIsCamouflaged_;

	if (distance_ > 800) { boolSeesPlayer = false; } //Within enemy renderdistance?

	//In their view?
	if (scale.x < 0 && playerPosition_.x < position.x) { boolSeesPlayer = false; }
	if (scale.x > 0 && playerPosition_.x > position.x) { boolSeesPlayer = false; }

	if (distance_ < 150 && playerIsMoving_) { boolSeesPlayer = true; } //So nearby they can hear you?

	//Walls between you?

	bool checkCasts = false;

	for (int castI = 0; castI <= 5; castI++) {

		bool checkCast = true;

		float h = sprite()->height() * scale.y;
		float w = 0;
		if (position.x + (getRect().width / 2) < playerPosition_.x) {
			w = getRect().width;
		}
		Vector2 _enemyPos = Vector2(position.x + w, position.y - (h - (h / 6 * (castI + 0.5))));
		_enemyPos.y += h / 2;

		Vector2 _direction = (playerPosition_ - _enemyPos);
		float _distance = sqrt(_direction.x * _direction.x + _direction.y * _direction.y);
		_direction = Vector2(_direction.x / _distance, _direction.y / _distance);
		
		for (int i = 0; i < colliders.size(); i++) {

			float x1L = colliders[i].x;
			float y1L = colliders[i].y;
			float x2L = colliders[i].x;
			float y2L = colliders[i].y + colliders[i].height;

			float x1R = colliders[i].x + colliders[i].width;
			float y1R = colliders[i].y;
			float x2R = colliders[i].x + colliders[i].width;
			float y2R = colliders[i].y + colliders[i].height;

			float x1T = colliders[i].x;
			float y1T = colliders[i].y;
			float x2T = colliders[i].x + colliders[i].width;
			float y2T = colliders[i].y;

			float x1B = colliders[i].x;
			float y1B = colliders[i].y + colliders[i].height;
			float x2B = colliders[i].x + colliders[i].width;
			float y2B = colliders[i].y + colliders[i].height;

			float x3 = _enemyPos.x;
			float y3 = _enemyPos.y;
			float x4 = _enemyPos.x + _direction.x;
			float y4 = _enemyPos.y + _direction.y;

			if (cast(playerPosition_, x1L, y1L, x2L, y2L, x3, y3, x4, y4) ||
				cast(playerPosition_, x1R, y1R, x2R, y2R, x3, y3, x4, y4) ||
				cast(playerPosition_, x1T, y1T, x2T, y2T, x3, y3, x4, y4) ||
				cast(playerPosition_, x1B, y1B, x2B, y2B, x3, y3, x4, y4)) {
				checkCast = false;
			} 
		}
		if (checkCast) {
			checkCasts = checkCast;
		}
		//std::cout << castI <<". check:"<< checkCast <<"\n";
	}
	if (!checkCasts) {
		boolSeesPlayer = checkCasts;
	}
	//std::cout << "boolSeesPlayer: "<< boolSeesPlayer<<"\n\n";

	return boolSeesPlayer;
}

bool Enemy::cast(Vector2 playerPos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) { //Is blocking view?

	bool blockingView = false;

	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0) { // denominator can't be zero
		blockingView = false;
	}
	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

	if (t > 0 && t < 1 && u > 0) {
		Vector2 pt;
		pt.x = x1 + t * (x2 - x1);
		pt.y = y1 + t * (y2 - y1);
		if (playerPos.x < pt.x && position.x > pt.x) {
			blockingView = true;
		}
		if (playerPos.x > pt.x && position.x < pt.x) {
			blockingView = true;
		}
		if (playerPos.y < pt.y && position.y > pt.y) {
			blockingView = true;
		}
		if (playerPos.y > pt.y && position.y < pt.y) {
			blockingView = true;
		}
	}

	return blockingView;
}

