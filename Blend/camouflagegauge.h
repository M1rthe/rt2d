#ifndef CAMOUFLAGEGAUGE_H
#define CAMOUFLAGEGAUGE_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>
#include <rt2d/text.h>

 /// @brief IsHidden checker extends from Entity
class Camouflagegauge : public Entity {

public:
	/// @brief Constructor
	Camouflagegauge();
	/// @brief Destructor
	virtual ~Camouflagegauge();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	/// @brief Change frame whether player is hidden
	/// @param hidden hidden boolean
	/// @return void
	void isHidden(bool hidden);
};

#endif /* CAMOUFLAGEGAUGE_H */
