#pragma once
# include <sig/sn_manipulator.h>
# include <sig/sn_model.h>
#include <list>

class tracking {
public:
	SnManipulator *model;
	GsVec incrmnt;
	GsVec start_position;
	GsVec destination;
	tracking();


	

};