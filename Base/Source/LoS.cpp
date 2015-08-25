#include "LoS.h"

bool checkLineOfSight(Vector3 point, Vector3 target, const TileMap* tileMap)
{
	if (point == target) return true;
	Vector3 view = (target - point).Normalized();
	if (view.x < 0)
	{
		point += target;
		target = point - target;
		point -= target;
		(view = target - point).Normalize();
	}

	Vector3 temp(point);
	/*float diff_x = ceil(temp.x) - temp.x;
	temp.x = ceil(temp.x);
	temp.y += view.y * diff_x * (1 / view.x);*/
	while (temp.x < floor(target.x))
	{
		//if (temp.y - (int) temp.y)
		if (tileMap->getTile(temp.x, floor(temp.y)) > 0)
			return false;
		++temp.x;
		temp.y += view.y * (1 / view.x);
	}

	view = (target - point).Normalized();
	if (view.y < 0)
	{
		point += target;
		target = point - target;
		point -= target;
		(view = target - point).Normalize();
	}

	temp = point;
	/*float diff_y = ceil(temp.y) - temp.y;
	temp.y = ceil(temp.y);
	temp.x += view.x * diff_y * (1 / view.y);*/
	while (temp.y < floor(target.y))
	{
		//if (temp.x - (int)temp.x)
		if (tileMap->getTile(floor(temp.x), temp.y) > 0)
			return false;
		++temp.y;
		temp.x += view.x * (1 / view.y);
	}

	return true;
}