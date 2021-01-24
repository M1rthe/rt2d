#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>

/// @brief Camouflage extends from Entity
class Camouflage : public Entity {

public:
	/// @brief Constructor
	Camouflage();
	/// @brief Destructor
	virtual ~Camouflage();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	/// @brief Set sprite to tile frame
	/// @param tile Frame of tile
	/// @return void
	void setCamouflage(int tile);
};

#endif /* CAMOUFLAGE_H */
