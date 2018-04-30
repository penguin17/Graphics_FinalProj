# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>

# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>
# include <sig/sn_manipulator.h>
# include "characterModel.h"

// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvNormals, EvAnimate, EvExit };
	UiCheckButton* _nbut;
	float rot;
	
	bool _animating;
	GsVec direction;
	GsVec position;
	GsVec eyePos, centerPos;
	GsVec lightSource;
	bool cameraMode;
	bool first;
	int legRotFront = 0.0;
	characterModel *janemba;
	characterModel *janemba_shadow;
   public :
	MyViewer ( int x, int y, int w, int h, const char* l );
	void build_dohnut();
	void build_floor();
	void build_ui ();
	void movement(int);
	void handle_motion(int);
	void add_model ( SnShape* s, GsVec p );
	void build_scene ();
	void show_normals ( bool b );
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;
	virtual int timer(int e) override;
};

