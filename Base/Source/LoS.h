#ifndef LOS_H
#define LOS_H

#include "Vector3.h"
#include "TileMap.h"

bool checkLineOfSight(Vector3 point, Vector3 target, const TileMap* tileMap);

#endif