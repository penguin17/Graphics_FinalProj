# include "characterModel.h"

void characterModel::loadModel()
{
	SnGroup *mainGroup = new SnGroup; 
	SnGroup *leftArmGroup1 = new SnGroup; 
	SnGroup *leftArmGroup2 = new SnGroup; 
	SnGroup *rightArmGroup1 = new SnGroup; 
	SnGroup *rightArmGroup2 = new SnGroup; 
	SnGroup *leftLegGroup1 = new SnGroup; 
	SnGroup *leftLegGroup2 = new SnGroup; 
	SnGroup *rightLegGroup1 = new SnGroup;
	SnGroup *rightLegGroup2 = new SnGroup; 
	

	SnModel *body = new SnModel;
	SnModel *head = new SnModel;
	SnModel *leftLowerLeg = new SnModel;
	SnModel *leftFoot = new SnModel;
	SnModel *leftHand = new SnModel;
	SnModel *leftLowerArm = new SnModel;
	SnModel *leftUpperArm = new SnModel;
	SnModel *leftUpperLeg = new SnModel;
	SnModel *rightFoot = new SnModel;
	SnModel *rightHand = new SnModel;
	SnModel *rightLowerArm = new SnModel;
	SnModel *rightUpperArm = new SnModel;
	SnModel *rightLowerLeg = new SnModel;
	SnModel *rightUpperLeg = new SnModel;

	mainGroup->separator(true);
	leftArmGroup1->separator(true);
	leftArmGroup2->separator(true);
	rightArmGroup1->separator(true);
	rightArmGroup2->separator(true);
	leftLegGroup1->separator(true);
	leftLegGroup2->separator(true);
	rightLegGroup1->separator(true);
	rightLegGroup2->separator(true);

	mainManip = new SnManipulator; mainManip->draw_box(false);
	bodyManip = new SnManipulator; bodyManip->draw_box(false);
	headManip = new SnManipulator; headManip->draw_box(false);
	leftLowerLegManip = new SnManipulator; leftLowerLegManip->draw_box(false);
	leftFootManip = new SnManipulator; leftFootManip->draw_box(false);
	leftHandManip = new SnManipulator; leftHandManip->draw_box(false);
	leftLowerArmManip = new SnManipulator; leftLowerArmManip->draw_box(false);
	leftUpperArmManip = new SnManipulator; leftUpperArmManip->draw_box(false);
	leftUpperLegManip = new SnManipulator; leftUpperLegManip->draw_box(false);
	rightFootManip = new SnManipulator; rightFootManip->draw_box(false);
	rightHandManip = new SnManipulator; rightHandManip->draw_box(false);
	rightLowerArmManip = new SnManipulator; rightLowerArmManip->draw_box(false);
	rightUpperArmManip = new SnManipulator; rightUpperArmManip->draw_box(false);
	rightLowerLegManip = new SnManipulator; rightLowerLegManip->draw_box(false);
	rightUpperLegManip = new SnManipulator; rightUpperLegManip->draw_box(false);

	body->model()->load("../Janemba_Body.obj");
	head->model()->load("../Janemba_Head.obj");
	leftLowerLeg->model()->load("../Janemba_LeftBottomLeg.obj");
	leftFoot->model()->load("../Janemba_LeftFoot.obj");
	leftHand->model()->load("../Janemba_LeftHand.obj");
	leftLowerArm->model()->load("../Janemba_LeftLowerArm.obj");
	leftUpperArm->model()->load("../Janemba_LeftUpperArm.obj");
	leftUpperLeg->model()->load("../Janemba_LeftUpperLeg.obj");
	rightFoot->model()->load("../Janemba_RightFoot.obj");
	rightHand->model()->load("../Janemba_RightHand.obj");
	rightLowerArm->model()->load("../Janemba_RightLowerArm.obj");
	rightLowerLeg->model()->load("../Janemba_RightLowerLeg.obj");
	rightUpperArm->model()->load("../Janemba_RightUpperArm.obj");
	rightUpperLeg->model()->load("../Janemba_RightUpperLeg.obj");

	if (mode == 0)
	{
		body->color(GsColor::black);
		head->color(GsColor::black);
		leftLowerLeg->color(GsColor::black);
		leftFoot->color(GsColor::black);
		leftHand->color(GsColor::black);
		leftLowerArm->color(GsColor::black);
		leftUpperArm->color(GsColor::black);
		leftUpperLeg->color(GsColor::black);
		rightFoot->color(GsColor::black);
		rightHand->color(GsColor::black);
		rightLowerArm->color(GsColor::black);
		rightLowerLeg->color(GsColor::black);
		rightUpperArm->color(GsColor::black);
		rightUpperLeg->color(GsColor::black);
	}
	else
	{
		body->color(GsColor::darkblue);
		head->color(GsColor::red);
		leftLowerLeg->color(GsColor::darkblue);
		leftFoot->color(GsColor::red);
		leftHand->color(GsColor::red);
		leftLowerArm->color(GsColor::darkblue);
		leftUpperArm->color(GsColor::red);
		leftUpperLeg->color(GsColor::red);
		rightFoot->color(GsColor::red);
		rightHand->color(GsColor::red);
		rightLowerArm->color(GsColor::darkblue);
		rightLowerLeg->color(GsColor::darkblue);
		rightUpperArm->color(GsColor::red);
		rightUpperLeg->color(GsColor::red);
	}

	bodyManip->child(body);
	headManip->child(head);
	mainGroup->add(bodyManip);
	mainGroup->add(headManip);

	// left leg
	leftFootManip->child(leftFoot);
	leftLegGroup2->add(leftFootManip);
	leftLegGroup2->add(leftLowerLeg);
	leftLowerLegManip->child(leftLegGroup2);
	leftLegGroup1->add(leftLowerLegManip);
	leftLegGroup1->add(leftUpperLeg);
	leftUpperLegManip->child(leftLegGroup1);
	mainGroup->add(leftUpperLegManip);

	// right leg
	rightFootManip->child(rightFoot);
	rightLegGroup2->add(rightFootManip);
	rightLegGroup2->add(rightLowerLeg);
	rightLowerLegManip->child(rightLegGroup2);
	rightLegGroup1->add(rightLowerLegManip);
	rightLegGroup1->add(rightUpperLeg);
	rightUpperLegManip->child(rightLegGroup1);
	mainGroup->add(rightUpperLegManip);

	// left arm
	leftHandManip->child(leftHand);
	leftArmGroup2->add(leftHandManip);
	leftArmGroup2->add(leftLowerArm);
	leftLowerArmManip->child(leftArmGroup2);
	leftArmGroup1->add(leftLowerArmManip);
	leftArmGroup1->add(leftUpperArm);
	leftUpperArmManip->child(leftArmGroup1);
	mainGroup->add(leftUpperArmManip);

	// right arm
	rightHandManip->child(rightHand);
	rightArmGroup2->add(rightHandManip);
	rightArmGroup2->add(rightLowerArm);
	rightLowerArmManip->child(rightArmGroup2);
	rightArmGroup1->add(rightLowerArmManip);
	rightArmGroup1->add(rightUpperArm);
	rightUpperArmManip->child(rightArmGroup1);
	mainGroup->add(rightUpperArmManip);

	mainManip->child(mainGroup);
}