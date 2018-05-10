# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>

# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>
# include <sig/sn_manipulator.h>
# include <sig/sn_model.h>
# include "characterModel.h"
# include "tracking.h"

// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvNormals, EvAnimate, EvExit };
	UiCheckButton* _nbut;
	float rot;
	GsVec leftLowerArmRot, leftHandRot, leftUpperArmRot, rightLowerArmRot, rightHandRot, rightUpperArmRot;
	int count;
	bool _animating;
	GsVec direction;
	GsVec position;
	GsVec eyePos, centerPos;
	GsVec lightSource;
	bool cameraMode;
	bool first;
	int legRotFront = 0.0;
	characterModel *janemba;
	//characterModel *janemba_shadow;
	GsVec incrmnt;
	GsVec start_position;
	GsVec destination;
	
   public :
	   SnManipulator * carManip;
	MyViewer ( int x, int y, int w, int h, const char* l );
	//void build_dohnut();
	void build_floor();
	void build_wall();
	void build_wall2();
	void build_wall3();
	void build_wall4();
	void build_ui ();
	bool collision(GsBox & box1, SnManipulator* check);
	void movement(int);
	void handle_motion(int);
	void animate();
	void add_model ( SnShape* s, GsVec p );
	void build_scene ();
	void show_normals ( bool b );
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;
	virtual int timer(int e) override;
	void timer_environment(int e);
	
};



