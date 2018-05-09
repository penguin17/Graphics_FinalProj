
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>
# include <sig/gs_vec.h>
# include <sig/gs_mat.h>

#include <list>
MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	count = 0;
	leftLowerArmRot.x = 0; leftLowerArmRot.y = 0; leftLowerArmRot.z = 0;
	leftHandRot.x = 0; leftHandRot.y = 0; leftHandRot.z = 0;
	leftUpperArmRot.x = 0; leftUpperArmRot.y = 0; leftUpperArmRot.z = 0;
	first = true;
	_nbut=0;
	_animating=false;
	eyePos.x = 3.11;
	eyePos.y = 94.79;
	eyePos.z = -82.46;

	centerPos.x = -1.91;
	centerPos.y = 49.13;
	centerPos.z = 5.64;

	lightSource.x = 0.0;
	lightSource.y = 100.0;
	lightSource.z = 40.0;
	cameraMode = true;
	build_ui ();
	janemba = new characterModel;
	//janemba_shadow = new characterModel;
	janemba->mode = 1;
	//janemba_shadow->mode = 0;
	janemba->loadModel();
	//janemba_shadow->loadModel();
	build_scene ();
	/*SnModel *derp = new SnModel;
	derp->model()->load("../building19.obj");
	rootg()->add(derp);*/
	render();
}

/*void MyViewer::build_dohnut()
{
	SnModel* sn = new SnModel; // create your SnModel
	GsModel& m = *sn->model(); // access the GsModel

	double inc = (2.0*3.14159265358979323846) / 16;
	double angleO = 0.0, angleP = 0.0;
	int i = 0;
	double r = 10.0;
	double R = 40.0;

	//rootg()->init();
	// 1. Generate the geometry:

	//Add your code here to generate the m.V, m.F, and m.N arrays for the torus
	while (angleO < 2.0*3.14159265358979323846)
	{
		while (angleP < 2.0*3.14159265358979323846)
		{

			GsVec n1(R*cos(angleP), R*sin(angleP), 0.0);
			GsVec n2(R*cos(angleP + inc), R*sin(angleP + inc), 0.0);


			m.V.push() = GsPnt((R + r * cos(angleO))*cos(angleP + inc), (R + r * cos(angleO))*sin(angleP + inc), r*sin(angleO));
			m.N.push() = (m.V.top() - n2);

			m.V.push() = GsPnt((R + r * cos(angleO + inc))*cos(angleP), (R + r * cos(angleO + inc))*sin(angleP), r*sin(angleO + inc));
			m.N.push() = (m.V.top() - n1);

			m.V.push() = GsPnt((R + r * cos(angleO + inc))*cos(angleP + inc), (R + r * cos(angleO + inc))*sin(angleP + inc), r*sin(angleO + inc));
			m.N.push() = (m.V.top() - n2);

			m.F.push() = GsModel::Face(m.V.size() - 1, m.V.size() - 2, m.V.size() - 3);

			m.V.push() = GsPnt((R + r * cos(angleO))*cos(angleP), (R + r * cos(angleO))*sin(angleP), r*sin(angleO));
			m.N.push() = (m.V.top() - n1);

			m.V.push() = GsPnt((R + r * cos(angleO))*cos(angleP + inc), (R + r * cos(angleO))*sin(angleP + inc), r*sin(angleO));
			m.N.push() = (m.V.top() - n2);

			m.V.push() = GsPnt((R + r * cos(angleO + inc))*cos(angleP), (R + r * cos(angleO + inc))*sin(angleP), r*sin(angleO + inc));
			m.N.push() = (m.V.top() - n1);


			m.F.push() = GsModel::Face(m.V.size() - 3, m.V.size() - 2, m.V.size() - 1);

			angleP += inc;


		}
		i++;
		angleO += inc;
		angleP = 0;
	}
	// 2. Create a material group:
	GsModel::Group& g = *m.G.push();
	g.fi = 0; // The group starts at first face,
	g.fn = m.F.size(); // convers all faces,
	g.dmap = new GsModel::Texture; // and will be textured,
	g.dmap->fname.set("../the-sun.png"); // with this image.
										 // 3. Make sure the number of materials matches the number of groups:
	m.M.push().init(); // Only the diffuse component will come from the texture,
					   //m.M.top() = ...; // so add here any other material properties you’d like.
					   // 4. Now you can add texture coordinates per vertex:
	int nv = m.V.size();
	m.T.size(nv); // set same size as m.V array

	inc = 1.0 / i;


	double x1 = 0.0, y1 = 1.0;
	int iSize = i;
	i = 0;

	for (int j = 0; j < iSize*iSize; j++)
	{
		m.T[i].set(x1, y1 - inc);
		m.T[i + 1].set(x1 + inc, y1);
		m.T[i + 2].set(x1 + inc, y1 - inc);

		m.T[i + 5].set(x1 + inc, y1);
		m.T[i + 4].set(x1, y1 - inc);
		m.T[i + 3].set(x1, y1);
		i += 6;
		y1 -= inc;

		if ((j + 1) % iSize == 0)
		{
			y1 = 1.0;
			x1 += inc;
		}
		else if (x1 >= 1.0)
			gsout << "Going overboard\n";
	}

	m.set_mode(GsModel::Smooth, GsModel::PerGroupMtl);
	m.textured = true;
	sn->model()->translate(lightSource);
	rootg()->add(sn); // add to the scene
	render();
}*/
void MyViewer::build_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _nbut=new UiCheckButton ( "Normals", EvNormals ) ); 
	}
	p->add ( new UiButton ( "Animate", EvAnimate ) );
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::add_model ( SnShape* s, GsVec p )
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	m.translation ( p );
	manip->initial_mat ( m );

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);

	rootg()->add(manip);
}

void MyViewer::build_scene ()
{
	

	GsMat mat;
	mat.e11 = lightSource.y;
	mat.e12 = -lightSource.x;
	mat.e32 = -lightSource.z;
	mat.e33 = lightSource.y;
	mat.e42 = -1.0;
	mat.e44 = lightSource.y;
	mat.e13 = mat.e14 = mat.e31 = mat.e34 = mat.e21 = mat.e22 = mat.e23 = mat.e24 = mat.e41 = mat.e43 = 0;

	

	//janemba_shadow->mainManip->mat() = mat;

	rootg()->add(janemba->mainManip);
	//rootg()->add(janemba_shadow->mainManip);
	camera().eye = eyePos;
	camera().center = centerPos;
	render();


	SnModel *building1 = new SnModel;
	building1->model()->load("../building1.obj");
	building1->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building1, GsVec(200.0,0.0, -680.0));
	
	SnModel *building2 = new SnModel;
	building2->model()->load("../building2.obj");
	building2->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f,0.0f));
	add_model(building2, GsVec(500.0, 0.0, 100.0));

	SnModel *building3 = new SnModel;
	building3->model()->load("../building3.obj");
	building3->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building3, GsVec(-500.0, 0.0, -100.0));

	SnModel *building4 = new SnModel;
	building4->model()->load("../building4.obj");
	building4->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building4, GsVec(-200.0, 0.0, 500.0));
	
	SnModel *building5 = new SnModel;
	building5->model()->load("../building5.obj");
	building5->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building5, GsVec(-100.0, 0.0, 100.0));

	SnModel *building6 = new SnModel;
	building6->model()->load("../building6.obj");
	building6->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building6, GsVec(300.0, 0.0, -50.0));

	SnModel *building7 = new SnModel;
	building7->model()->load("../building7.obj");
	building7->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building7, GsVec(-650.0, 0.0, 550.0));

	SnModel *building8 = new SnModel;
	building8->model()->load("../building8.obj");
	building8->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building8, GsVec(450.0, 0.0, -550.0));

	SnModel *building9 = new SnModel;
	building9->model()->load("../building9.obj");
	building9->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building9, GsVec(-150.0, 0.0, 700.0));

	SnModel *building10 = new SnModel;
	building10->model()->load("../building10.obj");
	building10->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building10, GsVec(150.0, 0.0, 560.0));

	SnModel *building11 = new SnModel;
	building11->model()->load("../building11.obj");
	building11->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building11, GsVec(-680.0, 0.0, 100.0));

	SnModel *building12 = new SnModel;
	building12->model()->load("../building12.obj");
	building12->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building12, GsVec(-150.0, 0.0, -680.0));

	SnModel *building13 = new SnModel;
	building13->model()->load("../building13.obj");
	building13->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building13, GsVec(70.0, 0.0, 50.0));

	SnModel *building14 = new SnModel;
	building14->model()->load("../building14.obj");
	building14->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building14, GsVec(400.0, 0.0, 400.0));

	SnModel *building15 = new SnModel;
	building15->model()->load("../building15.obj");
	building15->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building15, GsVec(-400.0, 0.0, 400.0));

	SnModel *building16 = new SnModel;
	building16->model()->load("../building16.obj");
	building16->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building16, GsVec(200.0, 0.0, -400.0));

	SnModel *building17 = new SnModel;
	building17->model()->load("../building17.obj");
	building17->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building17, GsVec(0.0, 0.0, -500.0));

	SnModel *building18 = new SnModel;
	building18->model()->load("../building18.obj");
	building18->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building18, GsVec(-20.0, 0.0, -175.0));

	SnModel *building19 = new SnModel;
	building19->model()->load("../building19.obj");
	building19->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building19, GsVec(-600.0, 0.0, -650.0));

	SnModel *building20 = new SnModel;
	building20->model()->load("../building19.obj");
	building20->model()->rotate(GsQuat(-0.8f, 0.0f, 0.0f, 0.0f));
	add_model(building20, GsVec(-400.0, 0.0, -500.0));

	SnModel *tree1 = new SnModel;
	//tree1->model()->load("../../Tree/Tree.obj");
	tree1->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Tree/Tree.obj");
	tree1->model()->rotate(GsQuat(6.0f, 0.0f, 0.0f, 0.0f));
	add_model(tree1, GsVec(170.0f, 0.0f, 10.0f));

	SnModel *tree2 = new SnModel;
	//tree2->model()->load("../Tree.obj");
	tree2->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Tree/Tree.obj");
	tree2->model()->rotate(GsQuat(6.0f, 0.0f, 0.0f, 0.0f));
	add_model(tree2, GsVec(570.0f, 0.0f, -90.0f));

	SnModel *tree3 = new SnModel;
	//tree3->model()->load("../Tree.obj");
	tree3->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Tree/Tree.obj");
	tree3->model()->rotate(GsQuat(6.0f, 0.0f, 0.0f, 0.0f));
	add_model(tree3, GsVec(-730.0f, 0.0f, -50.0f));

	SnModel *tree4 = new SnModel;
	//tree4->model()->load("../Tree.obj");
	tree4->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Tree/Tree.obj");
	tree4->model()->rotate(GsQuat(6.0f, 0.0f, 0.0f, 0.0f));
	add_model(tree4, GsVec(-730.0f, 0.0f, -730.0f));

	SnModel *tree5 = new SnModel;
	//tree5->model()->load("../Tree.obj");
	tree5->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Tree/Tree.obj");
	tree5->model()->rotate(GsQuat(6.0f, 0.0f, 0.0f, 0.0f));
	add_model(tree5, GsVec(-530.0f, 0.0f, 730.0f));

	SnModel *tree6 = new SnModel;
	//tree6->model()->load("../Tree.obj");
	tree6->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Tree/Tree.obj");
	tree6->model()->rotate(GsQuat(6.0f, 0.0f, 0.0f, 0.0f));
	add_model(tree6, GsVec(550.0f, 0.0f, 700.0f));

	SnModel *bush1 = new SnModel;
	bush1->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Bush/Bush1.obj");
	bush1->model()->rotate(GsQuat(4.5f, 0.0f, 0.0f, 0.0f));
	add_model(bush1, GsVec(-80.0f, 0.0f, 25.0f));

	SnModel *bush2 = new SnModel;
	bush2->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Bush/Bush1.obj");
	bush2->model()->rotate(GsQuat(4.5f, 0.0f, 0.0f, 0.0f));
	add_model(bush2, GsVec(-380.0f, 0.0f, 125.0f));

	SnModel *bush3 = new SnModel;
	bush3->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Bush/Bush1.obj");
	bush3->model()->rotate(GsQuat(4.5f, 0.0f, 0.0f, 0.0f));
	add_model(bush3, GsVec(80.0f, 0.0f, -25.0f));

	SnModel *bush4 = new SnModel;
	bush4->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Bush/Bush1.obj");
	bush4->model()->rotate(GsQuat(4.5f, 0.0f, 0.0f, 0.0f));
	add_model(bush4, GsVec(480.0f, 0.0f, 25.0f));

	SnModel *bush5 = new SnModel;
	bush5->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/Bush/Bush1.obj");
	bush5->model()->rotate(GsQuat(4.5f, 0.0f, 0.0f, 0.0f));
	add_model(bush5, GsVec(0.0f, 0.0f, -400.0f));

	SnModel* car = new SnModel;
	car->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/car/coupe.obj");
	//car->get_bounding_box();
	car->model()->rotate(GsQuat(3.5f, 0.0f, 0.0f, 0.0f));
	add_model(car, GsVec(260.0f, 0.0f, 370.0f));


	
	//Points for car path: (260, 0 ,370) to (260, 0, 700) to (10, 0, 700) to (10, 0, 370)

	SnModel* goku = new SnModel;
	goku->model()->load("C:/Users/Muqqaddas/Desktop/Graphics_FinalProj-master (2)/Graphics_FinalProj-master/84s2p5aq76yo-NarutoGokuOutfit/nrt.obj");
	//goku->model()->load("../nrt.obj");
	goku->model()->rotate(GsQuat(-0.4, 0.35, 0.0, 0.0));
	add_model(goku, GsVec(-90, 30, 300));

	//Points for Goku path: (-90,30,300) to (-590,30,300) to (-590,30,250) to (-90,30,250)

	//build_dohnut();
	build_floor();
}

void MyViewer::handle_motion(int choice)
{
	GsMat m1, m2, m3;

	//m.translation(GsVec(-6.4,-20.0,0.0)); // leftLowerLeg
	//m.translation(GsVec(-6.5,-2.5,0.0));  // leftFoot
	//m.translation(GsVec(-16.0,-43.0,0.0));  // leftHand
	//m.translation(GsVec(-16.0,-51.0,0.0)); // leftLowerArm
	//m.translation(GsVec(-16.0,-59.0,0.0)); // leftUpperArm
	//m.translation(GsVec(-4.8,-35.0,0.0)); // leftUpperLeg
	//m.translation(GsVec(6.5,-2.8,0.0)); // rightFoot
	//m.translation(GsVec(16.0, -40.0, 0.0)); // rightHand
	//m.translation(GsVec(16.0,-51.0,0.0)); // rightLowerArm
	//m.translation(GsVec(15.0, -59.0, 0.0)); // rightUpperArm
	//m.translation(GsVec(5.8,-21.0,0.0)); // rightLowerLeg
	//m.translation(GsVec(4.8,-35.0,0.0)); // rightUpperLeg
	float x, y, z;

	if (choice == 0 || choice == 1) { x = 16.0f; y = 43.0f; z = 0.0f; } // leftHand
	else if (choice == 2 || choice == 3) { x = 16.0f; y = 51.0f; z = 0.0f; } // leftLowerArm
	else if (choice == 4 || choice == 5) { x = 16.0f; y = 59.0f; z = 0.0f; } // leftUpperArm
	else if (choice == 6 || choice == 7) { x = -16.0f; y = 40.0f; z = 0.0f; } // rightHand
	else if (choice == 8 || choice == 9) { x = -16.0f; y = 51.0f; z = 0.0f; } // rightLowerArm
	else if (choice == 10 || choice == 11) { x = -15.0f; y = 59.0f; z = 0.0f; } // rightUpperArm
	else { gsout << "Choice is unidentifiable\n"; return; }



	if ((choice % 2) == 0)
		m2.rotx(-0.2f);
	else
		m2.rotx(0.2f);

	if (choice == 2) m2.rotz(-0.2f);
	else if (choice == 3) m2.rotz(0.2f);
	m3.translation(-x, -y, -z);
	m1.translation(x, y, z);

	m1 = m1 * m2*m3;
	
	if (choice == 0 || choice == 1) { janemba->leftHandManip->mat() = m1*janemba->leftHandManip->mat();}
	else if (choice == 2 || choice == 3) { janemba->leftLowerArmManip->mat() = m1*janemba->leftLowerArmManip->mat(); }
	else if (choice == 4 || choice == 5) { janemba->leftUpperArmManip->mat() = m1*janemba->leftUpperArmManip->mat(); }
	else if (choice == 6 || choice == 7) { janemba->rightHandManip->mat() = m1*janemba->rightHandManip->mat(); }
	else if (choice == 8 || choice == 9) { janemba->rightLowerArmManip->mat() = m1*janemba->rightLowerArmManip->mat(); }
	else if (choice == 10 || choice == 11) { janemba->rightUpperArmManip->mat() = m1*janemba->rightUpperArmManip->mat(); }

	/*janemba_shadow->mainManip->mat() = janemba->mainManip->mat();

	if (choice == 0 || choice == 1) { janemba_shadow->leftHandManip->mat() = m1 * janemba_shadow->leftHandManip->mat(); }
	else if (choice == 2 || choice == 3) { janemba_shadow->leftLowerArmManip->mat() = m1 * janemba_shadow->leftLowerArmManip->mat(); }
	else if (choice == 4 || choice == 5) { janemba_shadow->leftUpperArmManip->mat() = m1 * janemba_shadow->leftUpperArmManip->mat(); }
	else if (choice == 6 || choice == 7) { janemba_shadow->rightHandManip->mat() = m1 * janemba_shadow->rightHandManip->mat(); }
	else if (choice == 8 || choice == 9) { janemba_shadow->rightLowerArmManip->mat() = m1 * janemba_shadow->rightLowerArmManip->mat(); }
	else if (choice == 10 || choice == 11) { janemba_shadow->rightUpperArmManip->mat() = m1 * janemba_shadow->rightUpperArmManip->mat(); }
	*/
	GsMat mat;
	mat.e11 = lightSource.y;
	mat.e12 = -lightSource.x;
	mat.e32 = -lightSource.z;
	mat.e33 = lightSource.y;
	mat.e42 = -1.0;
	mat.e44 = lightSource.y;
	mat.e13 = mat.e14 = mat.e31 = mat.e34 = mat.e21 = mat.e22 = mat.e23 = mat.e24 = mat.e41 = mat.e43 = 0;
	
	//janemba_shadow->mainManip->mat() = mat * janemba->mainManip->mat();
	render();
}
void MyViewer::build_floor()
{
	
	SnModel *floor = new SnModel;
	floor->model()->V.push() = GsVec(1000.0, 0.0, 1000.0);
	floor->model()->N.push() = GsVec(0.0, 40.0, 0.0);
	floor->model()->V.push() = GsVec(-1000.0, 0.0, 1000.0);
	floor->model()->N.push() = GsVec(0.0, 40.0, 0.0);
	floor->model()->V.push() = GsVec(1000.0, 0.0, -1000.0);
	floor->model()->N.push() = GsVec(0.0, 40.0, 0.0);
	floor->model()->F.push() = GsModel::Face(floor->model()->V.size() - 1, floor->model()->V.size() - 2, floor->model()->V.size() - 3);

	floor->model()->V.push() = GsVec(-1000.0, 0.0, -1000.0);
	floor->model()->N.push() = GsVec(0.0, 40.0, 0.0);
	floor->model()->V.push() = GsVec(-1000.0, 0.0, 1000.0);
	floor->model()->N.push() = GsVec(0.0, 40.0, 0.0);
	floor->model()->V.push() = GsVec(1000.0, 0.0, -1000.0);
	floor->model()->N.push() = GsVec(0.0, 40.0, 0.0);
	floor->model()->F.push() = GsModel::Face(floor->model()->V.size() - 3, floor->model()->V.size() - 2, floor->model()->V.size() - 1);

	GsModel::Group& g = *floor->model()->G.push();
	g.fi = 0; // The group starts at first face,
	g.fn = floor->model()->F.size(); // convers all faces,
	g.dmap = new GsModel::Texture; // and will be textured,
	g.dmap->fname.set("../gravel.png"); // with this image.
										 // 3. Make sure the number of materials matches the number of groups:
	floor->model()->M.push().init(); // Only the diffuse component will come from the texture,
									 //m.M.top() = ...; // so add here any other material properties you’d like.
									 // 4. Now you can add texture coordinates per vertex:
	floor->model()->T.size(6);

	floor->model()->T[0].set(0.0, 1.0);
	floor->model()->T[1].set(1.0, 1.0);
	floor->model()->T[2].set(0.0, 0.0);
	floor->model()->T[3].set(1.0, 0.0);
	floor->model()->T[4].set(1.0, 1.0);
	floor->model()->T[5].set(0.0, 0.0);

	floor->model()->set_mode(GsModel::Smooth, GsModel::PerGroupMtl);
	floor->model()->textured = true;
	floor->model()->translate(GsVec(0.0, -2.0, 0.0));
	rootg()->add(floor); // add to the scene
	render();
}
void MyViewer::show_normals ( bool b )
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for ( int k=0; k<r->size(); k++ )
	{	SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if ( !b ) { l->visible(false); continue; }
		l->visible ( true );
		if ( !l->empty() ) continue; // build only once
		l->init();
		if ( s->instance_name()==SnPrimitive::class_name )
		{	GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face ( fn );
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for ( int i=0; i<m.F.size(); i++ )
			{	const GsVec& a=m.V[m.F[i].a]; l->push ( a, a+(*n++)*f );
				const GsVec& b=m.V[m.F[i].b]; l->push ( b, b+(*n++)*f );
				const GsVec& c=m.V[m.F[i].c]; l->push ( c, c+(*n++)*f );
			}
		}  
	}
}
void MyViewer::movement(int choice)
{	
	GsMat mat;
	mat.e11 = lightSource.y;
	mat.e12 = -lightSource.x;
	mat.e32 = -lightSource.z;
	mat.e33 = lightSource.y;
	mat.e42 = -1.0;
	mat.e44 = lightSource.y;
	mat.e13 = mat.e14 = mat.e31 = mat.e34 = mat.e21 = mat.e22 = mat.e23 = mat.e24 = mat.e41 = mat.e43 = 0;

	if (choice == 0)
	{
		GsMat rot, trans1, trans2;
		rot.roty(0.5f);
		trans1.translation(-janemba->position);
		trans2.translation(janemba->position);

		janemba->mainManip->mat() = trans2 * rot*trans1*janemba->mainManip->mat();
		rot = trans2 * rot*trans1;
		janemba->direction = rot * janemba->direction;

		//janemba_shadow->mainManip->mat() = mat*janemba->mainManip->mat();
		//janemba_shadow->direction = rot * janemba_shadow->direction;
		eyePos = rot * eyePos;
		centerPos = rot * centerPos;
	}
	else if (choice == 1)
	{
		GsMat rot, trans1, trans2;
		rot.roty(-0.5f);
		trans1.translation(-janemba->position);
		trans2.translation(janemba->position);

		janemba->mainManip->mat() = trans2 * rot*trans1*janemba->mainManip->mat();
		rot = trans2 * rot*trans1;
		janemba->direction = rot * janemba->direction;

		//janemba_shadow->mainManip->mat() = mat*janemba->mainManip->mat();
		//janemba_shadow->direction = rot * janemba_shadow->direction;

		eyePos = rot * eyePos;
		centerPos = rot * centerPos;
	}
	else if (choice == 2)
	{
		GsVec placement = janemba->direction - janemba->position;
		GsMat trans;
		trans.translation(placement);
	
		
		janemba->mainManip->mat() = trans *janemba->mainManip->mat();
		janemba->direction = janemba->direction + placement;
		janemba->position += placement;
		
		if (legRotFront == 0)
		{
			GsMat m1, m2, m3;

			m1.translation(GsVec(4.8,-35.0,0.0));
			if (first)
				m2.rotx(-0.8);
			else
				m2.rotx(-1.6);
			m3.translation(GsVec(-4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->rightUpperLegManip->mat() = m1 * janemba->rightUpperLegManip->mat();
		//	janemba_shadow->rightUpperLegManip->mat() = m1 * janemba_shadow->rightUpperLegManip->mat();

			m1.translation(GsVec(-4.8, -35.0, 0.0));
			if (first)
				m2.rotx(0.8);
			else
				m2.rotx(1.6);
			m3.translation(GsVec(4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->leftUpperLegManip->mat() = m1 * janemba->leftUpperLegManip->mat();
			//janemba->leftLowerLegManip->mat() = janemba->leftLowerLegManip->mat();
			legRotFront = 1;
			//janemba_shadow->leftUpperLegManip->mat() = m1 * janemba_shadow->leftUpperLegManip->mat();
		
		}
		else
		{
			GsMat m1, m2, m3;

			m1.translation(GsVec(4.8, -35.0, 0.0));
			if (first)
				m2.rotx(0.8);
			else
				m2.rotx(1.6);
			m3.translation(GsVec(-4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->rightUpperLegManip->mat() = m1 * janemba->rightUpperLegManip->mat();
			//janemba_shadow->rightUpperLegManip->mat() = m1 * janemba_shadow->rightUpperLegManip->mat();

			m1.translation(GsVec(-4.8, -35.0, 0.0));
			if (first)
				m2.rotx(-0.8);
			else
				m2.rotx(-1.6);
			m3.translation(GsVec(4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->leftUpperLegManip->mat() = m1 * janemba->leftUpperLegManip->mat();
			legRotFront = 0;
			//janemba_shadow->leftUpperLegManip->mat() = m1 * janemba_shadow->leftUpperLegManip->mat();
		}

		//janemba_shadow->mainManip->mat() = mat * janemba->mainManip->mat();
		//janemba_shadow->direction = janemba_shadow->direction + placement;
		//janemba_shadow->position += placement;
		first = false;
		add_timer(0.5, 0);
		eyePos += placement;
		centerPos += placement;
	}
	else if (choice == 3)
	{
		GsVec placement = janemba->direction - janemba->position;
		GsMat trans;
		trans.translation(-placement);
		
		janemba->mainManip->mat() = trans * janemba->mainManip->mat();
		janemba->direction = janemba->direction - placement;
		janemba->position -= placement;
		if (legRotFront == 0)
		{
			GsMat m1, m2, m3;

			m1.translation(GsVec(4.8, -35.0, 0.0));
			if (first)
				m2.rotx(-0.8);
			else
				m2.rotx(-1.6);
			m3.translation(GsVec(-4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->rightUpperLegManip->mat() = m1 * janemba->rightUpperLegManip->mat();
			//janemba_shadow->rightUpperLegManip->mat() = m1 * janemba_shadow->rightUpperLegManip->mat();

			m1.translation(GsVec(-4.8, -35.0, 0.0));
			if (first)
				m2.rotx(0.8);
			else
				m2.rotx(1.6);
			m3.translation(GsVec(4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->leftUpperLegManip->mat() = m1 * janemba->leftUpperLegManip->mat();
			legRotFront = 1;
			//janemba_shadow->leftUpperLegManip->mat() = m1 * janemba_shadow->leftUpperLegManip->mat();
			first = false;
		}
		else
		{
			GsMat m1, m2, m3;

			m1.translation(GsVec(4.8, -35.0, 0.0));
			if (first)
				m2.rotx(0.8);
			else
				m2.rotx(1.6);
			m3.translation(GsVec(-4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->rightUpperLegManip->mat() = m1 * janemba->rightUpperLegManip->mat();
			//janemba_shadow->rightUpperLegManip->mat() = m1 * janemba_shadow->rightUpperLegManip->mat();

			m1.translation(GsVec(-4.8, -35.0, 0.0));
			if (first)
				m2.rotx(-0.8);
			else
				m2.rotx(-1.6);
			m3.translation(GsVec(4.8, 35.0, 0.0));
			m1 = m3 * m2*m1;
			janemba->leftUpperLegManip->mat() = m1 * janemba->leftUpperLegManip->mat();
			legRotFront = 0;
			//
			
			
			//janemba_shadow->leftUpperLegManip->mat() = m1 * janemba_shadow->leftUpperLegManip->mat();
		}
		/*janemba_shadow->mainManip->mat() = mat * janemba->mainManip->mat();
		janemba_shadow->direction = janemba_shadow->direction - placement;
		janemba_shadow->position -= placement;*/
		add_timer(0.5, 0);
		first = false;
		eyePos -= placement;
		centerPos -= placement;
	}
	else
	{
		gsout << "Choice is undentifiable\n";
	}


	if (cameraMode)
	{
		camera().eye = eyePos;
		camera().center = centerPos;
	}
	
	redraw();
}

int MyViewer::timer(int e)
{
	float x, y, z;
	GsMat m1, m2, m3, m4, m5,m6,m7;
	GsVec leftHandInc, leftLowerArmInc, leftUpperArmInc, rightHandInc, rightLowerArmInc, rightUpperArmInc;
	float pi = 3.141592f;
	float converter = (pi / 180.0f);

	leftHandInc.x = ((-31.933f)*converter) / 60.0f; 
	leftHandInc.y = ((-88.69f)*converter) / 60.0f; 
	leftHandInc.z = ((35.653f)*converter) / 60.0f;

	
	/*leftLowerArmInc.x = ((-62.021f)*converter) / 60.0f; 
	leftLowerArmInc.y = ((-43.932f)*converter) / 60.0f; 
	leftLowerArmInc.z = ((45.816f)*converter) / 60.0f;*/
	leftLowerArmInc.x = ((-62.021)*converter) / 60.0f;
	leftLowerArmInc.y = ((-43.932f)*converter) / 60.0f;
	leftLowerArmInc.z = ((-45.816f)*converter) / 60.0f;

	leftUpperArmInc.x = (-76.0f*converter) / 60.0f;
	leftUpperArmInc.y = (0.0f*converter) / 60.0f;
	leftUpperArmInc.z = (0.0f*converter) / 60.0f;

	rightHandInc.x = ((-50.256f)*converter) / 60.0f;
	rightHandInc.y = ((40.468f)*converter) / 60.0f;
	rightHandInc.z = ((-35.303f)*converter) / 60.0f;

	/*leftLowerArmInc.x = ((-62.021f)*converter) / 60.0f;
	leftLowerArmInc.y = ((-43.932f)*converter) / 60.0f;
	leftLowerArmInc.z = ((45.816f)*converter) / 60.0f;*/
	rightLowerArmInc.x = ((-35.971)*converter) / 60.0f;
	rightLowerArmInc.y = ((78.131f)*converter) / 60.0f;
	rightLowerArmInc.z = ((40.471f)*converter) / 60.0f;

	rightUpperArmInc.x = (-74.5f*converter) / 60.0f;
	rightUpperArmInc.y = (-21.196f*converter) / 60.0f;
	rightUpperArmInc.z = (0.0f*converter) / 60.0f;

	if (count == 60)
		remove_timer(1);
	if (e == 1)
	{
			x = 16.0f; y = 43.0f; z = 0.0f;  // leftHand
			m3.translation(x, y, z);
			m2.rotx(leftHandInc.x);
			m4.rotz(-leftHandRot.z);
			m6.rotz(leftHandRot.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m6*m2*m4*m1;
			janemba->leftHandManip->mat() = m1 * janemba->leftHandManip->mat();
			leftHandRot.x += leftHandInc.x;

			m2.rotz(leftHandInc.z);
			m1.translation(-x, -y, -z);
			m1 = m3 *m2*m1;
			janemba->leftHandManip->mat() = m1 * janemba->leftHandManip->mat();
			leftHandRot.z += leftHandInc.z;

			m2.roty(leftHandInc.y);
			m4.rotz(-leftHandRot.z);
			m5.rotz(leftHandRot.z);
			m6.rotx(-leftHandRot.x);
			m7.rotx(leftHandRot.x);
			m1.translation(-x, -y, -z);
			m1 = m3 * m5*m7*m2*m6*m4*m1;
			janemba->leftHandManip->mat() = m1 * janemba->leftHandManip->mat();
			leftHandRot.y += leftHandInc.y;
	

			x = 16.0f; y = 51.0f; z = 0.0f;  // leftLowerArm
			m3.translation(x, y, z);
			//m2.rotx(leftLowerArmInc.x);
			//m4.rotz(-leftLowerArmRot.z);
			//m6.rotz(leftLowerArmRot.z);
			//m1.translation(-x, -y, -z);
			//m1 = m3 * m6*m2*m4*m1;
			//janemba->leftLowerArmManip->mat() = m1 * janemba->leftLowerArmManip->mat();
			//leftLowerArmRot.x += leftLowerArmInc.x;

			m2.rotz(leftLowerArmInc.z);
			m1.translation(-x, -y, -z);
			m1 = m3 *m2*m1;
			janemba->leftLowerArmManip->mat() = m1 * janemba->leftLowerArmManip->mat();
			leftLowerArmRot.z += leftLowerArmInc.z;

			m2.roty(leftLowerArmInc.y);
			m1.translation(-x, -y, -z);
			m4.rotz(-leftLowerArmRot.z);
			m5.rotz(leftLowerArmRot.z);
			m6.rotx(-leftLowerArmRot.x);
			m7.rotx(leftLowerArmRot.x);
			m1 = m3 * m5*m7*m2*m6*m4*m1;
			janemba->leftLowerArmManip->mat() = m1 * janemba->leftLowerArmManip->mat();
			leftLowerArmRot.y += leftLowerArmInc.y;

			x = 16.0f; y = 59.0f; z = 0.0f;  // leftUpperArm
			m3.translation(x, y, z);
			m2.rotx(leftUpperArmInc.x);
			m4.rotz(-leftUpperArmRot.z);
			m6.rotz(leftUpperArmRot.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m6*m2*m4*m1;
			janemba->leftUpperArmManip->mat() = m1 * janemba->leftUpperArmManip->mat();
			leftUpperArmRot.x += leftUpperArmInc.x;

			m2.rotz(leftUpperArmInc.z);
			m1.translation(-x, -y, -z);
			m1 = m3 *m2*m1;
			janemba->leftUpperArmManip->mat() = m1 * janemba->leftUpperArmManip->mat();
			leftUpperArmRot.z += leftUpperArmInc.z;

			m2.roty(leftUpperArmInc.y);
			m1.translation(-x, -y, -z);
			m4.rotz(-leftUpperArmRot.z);
			m5.rotz(leftUpperArmRot.z);
			m6.rotx(-leftUpperArmRot.x);
			m7.rotx(leftUpperArmRot.x);
			m1 = m3 * m5*m7*m2*m6*m4*m1;
			janemba->leftUpperArmManip->mat() = m1 * janemba->leftUpperArmManip->mat();
			leftUpperArmRot.y += leftUpperArmInc.y;

			x = -16.0f; y = 40.0f; z = 0.0f;  // rightHand
			m3.translation(x, y, z);
			m2.rotx(rightHandInc.x);
			m4.rotz(-rightHandRot.z);
			m6.rotz(rightHandRot.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m6*m2*m4*m1;
			janemba->rightHandManip->mat() = m1 * janemba->rightHandManip->mat();
			rightHandRot.x += rightHandInc.x;

			m2.rotz(rightHandInc.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m2*m1;
			janemba->rightHandManip->mat() = m1 * janemba->rightHandManip->mat();
			rightHandRot.z += rightHandInc.z;

			m2.roty(rightHandInc.y);
			m4.rotz(-rightHandRot.z);
			m5.rotz(rightHandRot.z);
			m6.rotx(-rightHandRot.x);
			m7.rotx(rightHandRot.x);
			m1.translation(-x, -y, -z);
			m1 = m3 * m5*m7*m2*m6*m4*m1;
			janemba->rightHandManip->mat() = m1 * janemba->rightHandManip->mat();
			rightHandRot.y += rightHandInc.y;

			x = -16.0f; y = 51.0f; z = 0.0f;  // rightLowerArm
			m3.translation(x, y, z);
			/*m2.rotx(rightLowerArmInc.x);
			m4.rotz(-rightLowerArmRot.z);
			m6.rotz(rightLowerArmRot.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m6*m2*m4*m1;
			janemba->rightLowerArmManip->mat() = m1 * janemba->rightLowerArmManip->mat();
			rightLowerArmRot.x += rightLowerArmInc.x;*/

			m2.rotz(rightLowerArmInc.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m2 * m1;
			janemba->rightLowerArmManip->mat() = m1 * janemba->rightLowerArmManip->mat();
			rightLowerArmRot.z += rightLowerArmInc.z;

			m2.roty(rightLowerArmInc.y);
			m1.translation(-x, -y, -z);
			m4.rotz(-rightLowerArmRot.z);
			m5.rotz(rightLowerArmRot.z);
			m6.rotx(-rightLowerArmRot.x);
			m7.rotx(rightLowerArmRot.x);
			m1 = m3 * m5*m7*m2*m6*m4*m1;
			janemba->rightLowerArmManip->mat() = m1 * janemba->rightLowerArmManip->mat();
			rightLowerArmRot.y += rightLowerArmInc.y;

			x = -15.0f; y = 59.0f; z = 0.0f;  // rightUpperArm
			m3.translation(x, y, z);
			m2.rotx(rightUpperArmInc.x);
			m4.rotz(-rightUpperArmRot.z);
			m6.rotz(rightUpperArmRot.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m6*m2*m4*m1;
			janemba->rightUpperArmManip->mat() = m1 * janemba->rightUpperArmManip->mat();
			rightUpperArmRot.x += rightUpperArmInc.x;

			m2.rotz(rightUpperArmInc.z);
			m1.translation(-x, -y, -z);
			m1 = m3 * m2*m1;
			janemba->rightUpperArmManip->mat() = m1 * janemba->rightUpperArmManip->mat();
			rightUpperArmRot.z += rightUpperArmInc.z;

			m2.roty(rightUpperArmInc.y);
			m1.translation(-x, -y, -z);
			m4.rotz(-rightUpperArmRot.z);
			m5.rotz(rightUpperArmRot.z);
			m6.rotx(-rightUpperArmRot.x);
			m7.rotx(rightUpperArmRot.x);
			m1 = m3 * m5*m7*m2*m6*m4*m1;
			janemba->rightUpperArmManip->mat() = m1 * janemba->rightUpperArmManip->mat();
			rightUpperArmRot.y += rightUpperArmInc.y;

		count++;
		render();
	}
	return 1;
}
/*void MyViewer::timer_environment(int e)
{
	if (e = 0) 
	{
		std::list<tracking> temp;
		while (!temp.empty)
		{
			temp.pop_front;
			GsVec newPosition = incrmnt;
			if (newPosition != destination) 
			{
				temp.push_front;
			}


		}
	}

}*/
void MyViewer::animate()
{
	add_timer(0.01, 1);

}
int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
		case 'n' : { bool b=!_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
		case 'q': handle_motion(0); return 1;
		case 'a': handle_motion(1); return 1;
		case 'w': handle_motion(2); return 1;
		case 's': handle_motion(3); return 1;
		case 'e': handle_motion(4); return 1;
		case 'd': handle_motion(5); return 1;
		case 'r': handle_motion(6); return 1;
		case 'f': handle_motion(7); return 1;
		case 't': handle_motion(8); return 1;
		case 'g': handle_motion(9); return 1;
		case 'y': handle_motion(10); return 1;
		case 'h': handle_motion(11); return 1;
		case 'u': animate(); return 1;
		case GsEvent::KeyUp: movement(2); return 1;
		case GsEvent::KeyDown: movement(3);  return 1;
		case GsEvent::KeyLeft: movement(0); return 1;
		case GsEvent::KeyRight: movement(1); return 1;
		case GsEvent::KeySpace: cameraMode = !cameraMode; if (!cameraMode) { camera().eye.x = 0.0; camera().eye.y = 200.0; camera().eye.z = -100.0;
			camera().center.x = 0.0; camera().center.y = 50.0; camera().center.z = 0.0; render();
		}
								else { camera().eye = eyePos; camera().center = centerPos; } render(); return 1;
		default: return 1;
	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvNormals: show_normals(_nbut->value()); return 1;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
