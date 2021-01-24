#ifndef COLLIDER_H
#define COLLIDER_H

#include <algorithm> 
#include <rt2d/pointx.h> 

/// @brief Rectangle
struct Rectangle {

	float x;
	float y;
	float width;
	float height;

	/// @brief Constructor
	/// @param x x position
	/// @param y y position
	/// @param w width
	/// @param h height
	Rectangle(float x_, float y_, float w, float h) {
		this->x = x_;
		this->y = y_;
		this->width = w;
		this->height = h;
	}
};

/// @brief Collider
class Collider {

public:

	/// @brief Rectangle collision with Rectangle
	/// @param rect1 Rectangle1
	/// @param rect2 Rectangle2
	/// @return bool
	static bool rectangle2rectangle(const Rectangle& rect1, const Rectangle& rect2) {
		return (
			rect1.x < rect2.x + rect2.width &&
			rect1.x + rect1.width > rect2.x &&
			rect1.y < rect2.y + rect2.height &&
			rect1.y + rect1.height > rect2.y
		);
	}

private:
	/// @param Disallow creating an instance of this object
	Collider() {}
};

#endif /* COLLIDER_H */

