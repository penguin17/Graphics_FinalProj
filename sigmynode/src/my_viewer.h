# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>

# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>
# include "sn_mynode.h"

// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvAdd, EvInfo, EvExit };
   public :
	float height = 0.1f, width = 0.1f ,xPos = -0.10f, yPos = -0.04f;
	float angleLong, angleShort;
	double R, r;
	bool timer0, timer1;
	SnMyNode clock;
	GsVec shadowPoint;
	int numFaces;
	MyViewer ( int x, int y, int w, int h, const char* l );
	void drawClock();
	void add_ui ();
	void add_mynode (  );
	void makeCircle();
	void letterPoints(int, float,float,GsVec*);
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;
	virtual int timer(int e) override;
};
