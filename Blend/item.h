#ifndef ITEM_H
#define ITEM_H

#include <rt2d/entity.h>
#include <string>
#include "collider.h"

using namespace std;

/// @brief Item extends from Entity
class Item : public Entity {

public:
	/// @brief Constructor
	/// @param filename
	Item(string filename);
	/// @brief Destructor
	virtual ~Item();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	///< @brief Name of file
	string name;
};

#endif /* ITEM_H */
