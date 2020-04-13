#pragma once
#include "Vector2D.h"
struct HitboxData 
{
public:
	int damage_ = -1,
		time_ = -1,
		hitstun_ = -1;
	Vector2D knockBack_; //Assuming looking to the right
	bool guardBreaker = false;
	bool destroy = false;//if its true it means that it has to be destroyed
	
};

