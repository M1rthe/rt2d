#ifndef HUD_H
#define HUD_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>
#include <rt2d/text.h>
#include "camouflage.h"
#include "camouflagegauge.h"

/// @brief Hud extends from Entity
class Hud : public Entity {

public:
	/// @brief Constructor
	Hud();
	/// @brief Destructor
	virtual ~Hud();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	///< @brief Mission
	Text* mission;
	///< @brief Camouflage button 1
	Camouflage* camouflage1;
	///< @brief Camouflage button 2
	Camouflage* camouflage2;
	///< @brief Camouflage button 3
	Camouflage* camouflage3;
	///< @brief Camouflage isHidden
	Camouflagegauge* camouflagegauge;

private:
	///< @brief Margin around HUD
	float margin;
	///< @brief Size of buttons
	int size;
};

#endif /* HUD_H */
