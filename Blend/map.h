#ifndef MAP_H
#define MAP_H

#include <rt2d/entity.h>
#include <rt2d/pointx.h>
#include "basicentity.h"
#include <string>
#include "collider.h"

using namespace std;

/// @brief Map extends from Entity
class Map : public Entity {

public:
	/// @brief Constructor
	Map();
	/// @brief Destructor
	virtual ~Map();
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	/// @brief Get overlap value with current camouflage
	/// @param position
	/// @param size
	/// @param camouflage
	/// @param facing
	/// return int
	int findMostOverlappedTile(Vector2 position, Vector2 size, int camouflage, int facing);

	/// @brief Get Rectangle of certain tile
	/// @param tile
	/// return Rectangle
	Rectangle getRectTile(int tile);

	///< @brief Grid width (amount of horizontal tiles)
	int gridwidth;
	///< @brief Grid height (amount of vertical tiles)
	int gridheight;
	///< @brief Cell width (tile width)
	int cellwidth;
	///< @brief Cell height (tile height)
	int cellheight;

	///< @brief Tiles with Collider
	vector<Rectangle> tilesWithCollider;
	///< @brief Index of tiles with Collider
	vector<int> tilesWithCollision;

	void changeTiles(string find, string replaceString);
	void calculateTiles();

	bool reloadedMap = false;

private:
	/// @brief Calculate distance between to points
	float CalculateDistance(Vector2 p1, Vector2 p2);

	///< @brief Grid
	BasicEntity* grid;
	///< @brief Level, it consists of a list with strings
	string* level = new string[2048]{ //64 x 32
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fst","fst","fst","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tsb","tbt","tbtF","tsb","tsb","tsb","tbt","tbtF","tsb","tbt","tbtF","tsb","tsb","tsb","tbt","tbtF","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tsb","tbb","tbbF","tsb","tsb","tsb","tbb","tbbF","tsb","tbb","tbbF","tsb","tsb","tsb","tbb","tbbF","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","flu","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tsb","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","fst","tsb","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","fpl","fpl","tbr","tbr","tbr","tbr","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","fpl","fpl","tbr","tbr","tbr","tbr","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","fpl","fpl","fpl","fpl","tbr","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","fpl","fpl","fpl","fpl","tbr","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","tcw","tcw","tcw","tbr","tbr","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fpl","fpl","fpl","fpl","fpl","fpl","fpl","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","tdt","tdtF","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","tbr","tdb","tdbF","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","tbr","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","fbu","fbu","f","f","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","fbu","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	"f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f","f",
	};
};

#endif /* MAP_H */