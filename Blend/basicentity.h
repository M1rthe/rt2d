#ifndef BASICENTITY_H
#define BASICENTITY_H

#include <rt2d/entity.h>

/// @brief Entity implementation
class BasicEntity : public Entity {

public:
	/// @brief Constructor
	BasicEntity();
	/// @brief Destructor
	virtual ~BasicEntity();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
};

#endif /* BASICENTITY_H */
