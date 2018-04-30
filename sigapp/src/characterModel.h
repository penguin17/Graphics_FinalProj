#pragma once
# include <sig/sn_manipulator.h>
# include <sig/sn_model.h>

class characterModel {
	

public:
	int mode;
	GsVec direction, position;
	SnManipulator *mainManip;
	SnManipulator *shadowManip;
	SnManipulator *bodyManip;
	SnManipulator *headManip;
	SnManipulator *leftLowerLegManip;
	SnManipulator *leftFootManip;
	SnManipulator *leftHandManip;
	SnManipulator *leftLowerArmManip;
	SnManipulator *leftUpperArmManip;
	SnManipulator *leftUpperLegManip;
	SnManipulator *rightFootManip;
	SnManipulator *rightHandManip;
	SnManipulator *rightLowerArmManip;
	SnManipulator *rightUpperArmManip;
	SnManipulator *rightLowerLegManip;
	SnManipulator *rightUpperLegManip;

	characterModel()
	{
		direction.x = 0.0;
		direction.y = 0.0;
		direction.z = 20.0;

		position.x = 0.0;
		position.y = 0.0;
		position.z = 0.0;
	}
	void loadModel();
};