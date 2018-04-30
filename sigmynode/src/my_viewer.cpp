
# include "my_viewer.h"
# include "sn_mynode.h"
# include "glr_mynode.h"
# include <sig/gs_array.h>
#include <sig/sn_model.h>
# include <sigogl/gl_tools.h>
# include <sigogl/ui_button.h>

SnMyNode* add(GsVec o, float w, float h);

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	add_ui ();

	R = 1.0;
	r = 0.02;
	numFaces = 24;
	angleLong = 0.0f;
	angleShort = 0.0f;
	
	shadowPoint.x = 3.0;
	shadowPoint.y = 3.0;
	shadowPoint.z = 3.0;

	//add_timer(1.0,0);
	timer0 = true;
	//add_timer(1.0/60.0,1);
	timer1 = true;
	SnModel *point = new SnModel;
	GsModel&p = *point->model();
	GsVec norm;
	norm.x = 0.0;
	norm.y = 1.0;
	norm.z = 0.0;
	p.V.push() = GsVec(10.0, 0.0, 10.0);
	p.N.push() = p.V.top() - GsVec(p.V.top().x,-1.0f,p.V.top().z);
	p.V.push() = GsVec(-10.0, 0.0, -10.0);
	p.N.push() = p.V.top() - GsVec(p.V.top().x, -1.0f, p.V.top().z);
	p.V.push() = GsVec(10.0, 0.0, -10.0);
	p.N.push() = p.V.top() - GsVec(p.V.top().x, -1.0f, p.V.top().z);
	p.F.push() = GsModel::Face(2,1,0);
	//point->color(GsColor::black);
	p.set_mode(GsModel::Smooth, GsModel::NoMtl);
	rootg()->add(point);
	render();

	//drawClock();
	message("Keys = LEFT(-x), RIGHT(+x), UP(+y), DOWN(-y), w(+)width, e(-)width, PGUP(+)height, PGDOWN(-)height");
}

void MyViewer::add_ui ()
{
	UiPanel *p;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "Add", EvAdd ) );
	p->add ( new UiButton ( "Info", EvInfo ) );
	p->add ( new UiButton ( "Exit", EvExit ) );
}
void MyViewer::letterPoints(int choice,float h, float w, GsVec* o)
{
	// This method deals with sending the correct points to start drawing the letters based on which letter is decided with choice 
	// variable
	if (choice == 0)
	{
		// D

		o[0].set(xPos, yPos, -0.12f);
		o[1].set(xPos + (1.0f / 4.0f)*width, yPos + (3.0f*height) / 4.0f, -0.12f);
		o[2].set(xPos + (0.5f)*width, yPos + (5.0f / 8.0f)*height, -0.12f);
		o[3].set(xPos + 0.55f*width, yPos + 0.375f*height, -0.12f);
		o[4].set(xPos + 0.5f*width, yPos + 0.125f*height, -0.12f);
		o[5].set(xPos + 0.25f*width, yPos, -0.12f);
	}
	else if (choice == 1)
	{
		// A

		o[0].set(1.2f*width + xPos, yPos, -0.12f);
		o[1].set(1.2f*width + xPos + 0.5f*w, yPos + h, -0.12f);
		o[2].set(1.2f*width + xPos + w, yPos + 2.0f*h, -0.12f);
		o[3].set(1.2f*width + xPos + 2.0f*w, yPos + 2.5f*h, -0.12f);
		o[4].set(1.2f*width + xPos + 3.0f*w, yPos + 2.0f*h, -0.12f);
		o[5].set(1.2f*width + xPos + 3.5f*w, yPos + h, -0.12f);
		o[6].set(1.2f*width + xPos + 4.0f*w, yPos, -0.12f);
		o[7].set(1.2f*width + xPos + 1.5f*w, yPos + h, -0.12f);
	}
	else if (choice == 2)
	{
		// V

		o[0].set(2.4f*width + xPos, yPos + 2.0f*h, -0.12f);
		o[1].set(2.4f*width + xPos + 0.5f*w, yPos + h, -0.12f);
		o[2].set(2.4f*width + xPos + w, yPos, -0.12f);
		o[3].set(2.4f*width + xPos + 2.0f*w, yPos, -0.12f);
		o[4].set(2.4f*width + xPos + 3.0f*w, yPos, -0.12f);
		o[5].set(2.4f*width + xPos + 3.5f*w, yPos + h, -0.12f);
		o[6].set(2.4f*width + xPos + 4.0f*w, yPos + 2.0f*h, -0.12f);
	}
	else if (choice == 3)
	{
		// I

		o[0].set(3.6f*width + xPos, yPos, -0.12f);
		o[1].set(3.6f*width + xPos + width / 3, yPos, -0.12f);
		o[2].set(3.6f*width + xPos, yPos + (2 * height) / 3, -0.12f);
	}
	else if (choice == 4)
	{
		// Last D
		o[0].set(4.8f*width + xPos, yPos, -0.12f);
		o[1].set(4.8f*width + xPos + (1.0f / 4.0f)*width, yPos + (3.0f*height) / 4.0f, -0.12f);
		o[2].set(4.8f*width + xPos + (0.5f)*width, yPos + (5.0f / 8.0f)*height, -0.12f);
		o[3].set(4.8f*width + xPos + 0.55f*width, yPos + 0.375f*height, -0.12f);
		o[4].set(4.8f*width + xPos + 0.5f*width, yPos + 0.125f*height, -0.12f);
		o[5].set(4.8f*width + xPos + 0.25f*width, yPos, -0.12f);
	}
	else
		gsout << "Unknown Choice being selected!!!\n";
}

void MyViewer::add_mynode()
{
	float h = 0.0f, w = 0.0f;
	GsVec o[8];



	float r = 0.15f; // position range
	rootg()->init();
	
	for (int i = 0; i < 5; i++)
	{
		int size = 0;

		if (i == 0 || i == 4)
		{
			h = 0.25f*height;
			w = 0.25f*width;
			size = 6;
		}
		else if (i == 1)
		{
			h = 0.28571f*height;
			w = 0.2f*width;
			size = 8;
		}
		else if (i == 2)
		{
			h = 0.3333f*height;
			w = 0.2f*width;
			size = 7;
		}
		else if (i == 3)
		{
				h = (1.0f / 3.0f)*height;
				w = width;
				size = 3;
		}

		letterPoints(i, h, w, o);

		for (int j = 0; j < size; j++)
		{
			if ((i == 0 || i == 4) && j == 0)
				rootg()->add(add(o[j], w, height));
			else if (i == 1 && j == 7)
				rootg()->add(add(o[j], 3.0f*w, 0.5f*h));
			else if (i == 2 && j == 3)
				rootg()->add(add(o[j], w, 0.5f*h));
			else if (i == 3 && j == 1)
				rootg()->add(add(o[j], (1.0f/3.0f)*width, height));
			else
				rootg()->add(add(o[j], w, h));
		}
	}


}
void MyViewer::makeCircle()
{
	rootg()->init();


	double angleO = 0.0, angleP = 0.0;

	double inc = (2.0*3.14159265358979323846) / numFaces;

	while (angleO < 2.0*3.14159265358979323846)
	{
		while (angleP < 2.0*3.14159265358979323846)
		{
			clock.points.push() = GsVec((R + r * cos(angleO))*cos(angleP), (R + r * cos(angleO))*sin(angleP), r*sin(angleO));
			clock.points.push() = GsVec((R + r * cos(angleO))*cos(angleP + inc), (R + r * cos(angleO))*sin(angleP + inc), r*sin(angleO));
			clock.points.push() = GsVec((R + r * cos(angleO + inc))*cos(angleP), (R + r * cos(angleO + inc))*sin(angleP), r*sin(angleO + inc));

			clock.points.push() = GsVec((R + r * cos(angleO))*cos(angleP + inc), (R + r * cos(angleO))*sin(angleP + inc), r*sin(angleO));
			clock.points.push() = GsVec((R + r * cos(angleO + inc))*cos(angleP), (R + r * cos(angleO + inc))*sin(angleP), r*sin(angleO + inc));
			clock.points.push() = GsVec((R + r * cos(angleO + inc))*cos(angleP + inc), (R + r * cos(angleO + inc))*sin(angleP + inc), r*sin(angleO + inc));

			angleP += inc;
		}

		angleP = 0.0;
		angleO += inc;
	}
	
	/*rootg()->add(c);
	render();*/
}


SnMyNode* add(GsVec o,float w, float h)
{
	SnMyNode* c;
	c = new SnMyNode;
	c->init = o;
	c->width = w;
	c->height = h;
	c->color(GsColor::black);
	// Example how to print/debug your generated data:
	// gsout<<n<<": "<<c->color()<<gsnl;
	return c;
}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
		case GsEvent::KeyLeft: xPos -= 0.01f; add_mynode(); render(); return 1;
		case GsEvent::KeyRight: xPos += 0.01f; add_mynode(); render(); return 1;
		case GsEvent::KeyUp: yPos += 0.01f; add_mynode(); render(); return 1;
		case GsEvent::KeyDown: yPos -= 0.01f; add_mynode(); render(); return 1;
		case GsEvent::KeyPgUp: height += 0.01f; add_mynode(); render(); return 1;
		case GsEvent::KeyPgDn: height -= 0.01f; add_mynode(); render(); return 1;
		case GsEvent::KeySpace: timer0 = !timer0; timer1 = !timer1; return 1;
		case GsEvent::KeyEnter: angleShort = 0.0f; angleLong = 0.0f; return 1;
		/*case 'w': width += 0.01f; add_mynode(); render(); return 1;
		case 'e': width -= 0.01f; add_mynode(); render(); return 1;*/
		case 'q': shadowPoint.x++; drawClock(); return 1;
		case 'a': shadowPoint.x--; drawClock(); return 1;
		case 'w': shadowPoint.y++; drawClock(); return 1;
		case 's': shadowPoint.y--; drawClock(); return 1;
		case 'e': shadowPoint.z++; drawClock(); return 1;
		case 'd': shadowPoint.z--; drawClock(); return 1;
		//case GsEvent::KeySpace: if (message() == "") message("Keys = LEFT(-x), RIGHT(+x), UP(+y), DOWN(-y), w(+)width, e(-)width, PGUP(+)height, PGDOWN(-)height"); else message(0); render(); return 1;
		// etc
		default: gsout<<"Key pressed: "<<e.key<<gsnl;
	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvAdd: add_mynode(); return 1;

		case EvInfo:
		{	if ( output().len()>0 ) { output(""); return 1; }
			output_pos(0,30);
			activate_ogl_context(); // we need an active context
			GsOutput o; o.init(output()); gl_print_info(&o); // print info to viewer
			return 1;
		}

		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
int MyViewer::timer(int e)
{
	if (e == 0)
	{
		if (timer0)
		{
			angleLong += 6 * ((3.14159265358979323846f) / 180);
			drawClock();
		}
	}
	else if (e == 1)
	{
		if (timer1)
		{
			angleShort += 6 * ((3.14159265358979323846f) / 180);
			drawClock();
		}
	}
	else
		gsout << "Getting unexpected timer value\n";

	return 1;
}
void MyViewer::drawClock()
{
	SnMyNode *c = new SnMyNode;
	GsMat mat;
	mat.translation(0.0, 2.0, 0.0);
	rootg()->init();

	makeCircle();

	// draw time increments
	float angle = 0.0f;
	float inc = (2.0f*3.14159265358979323846f) / 12.0f;
	
	while (angle < (2.0f*3.14159265358979323846f))
	{
		GsVec curr = GsVec(0.0, R - 8 * r, 0.0);
		curr.rotz(angle);
		clock.points.push() = curr;
		
		curr = GsVec(0.0, R - r, 0.0);
		curr.rotz((inc / 8) + angle);
		clock.points.push() = curr;

		curr = GsVec(0.0, R - r, 0.0);
		curr.rotz((-inc / 8) + angle);
		clock.points.push() = curr;
		
		angle += inc;
	}
	
	// long arm
	GsVec curr = GsVec(-R / 8, 0.0, 0.0);
	curr.rotz(-angleLong);
	clock.points.push() = curr;

	curr = GsVec(R / 8, 0.0, 0.0);
	curr.rotz(-angleLong);
	clock.points.push() = curr;

	curr = GsVec(0.0, R / 2, 0.0);
	curr.rotz(-angleLong);
	clock.points.push() = curr;

	SnMyNode *c2 = new SnMyNode;
	// short arm
	curr = GsVec(-R / 16, 0.0, 0.0);
	curr.rotz(-angleShort);
	c2->points.push() = curr;

	curr = GsVec(R / 16, 0.0, 0.0);
	curr.rotz(-angleShort);
	c2->points.push() = curr;

	curr = GsVec(0.0, R / 4, 0.0);
	curr.rotz(-angleShort);
	c2->points.push() = curr;
	c2->color(GsColor::red);

	c2->points.get(0) = mat* c2->points.get(0);
	c2->points.get(1) = mat * c2->points.get(1);
	c2->points.get(2) = mat * c2->points.get(2);
	

	for (int i = 0; i < clock.points.size(); i++)
		clock.points.get(i) = mat * clock.points.get(i);
	
	

	c->color(GsColor::black);

	mat.e11 = shadowPoint.y;
	mat.e12 = -shadowPoint.x;
	mat.e32 = -shadowPoint.z;
	mat.e33 = shadowPoint.y;
	mat.e42 = -1.0;
	mat.e44 = shadowPoint.y;
	mat.e13 = mat.e14 = mat.e31 = mat.e34 = mat.e21 = mat.e22 = mat.e23 = mat.e24 = mat.e41 = mat.e43 = 0;

	for (int i = 0; i < clock.points.size(); i++)
		c->points.push() = clock.points.get(i);

	for (int i = 0; i < clock.points.size(); i++)
	{
		GsVec v = clock.points.get(i) - shadowPoint;
		GsVec n = GsVec(0.0, 1.0, 0.0);
		curr = GsVec(1.0, 0.0, 0.0) - clock.points.get(i);
		curr = ((dot(curr,n)) / (dot(v,n)))*v;
		
		c->points.push() = clock.points.get(i) + curr;
	}

	for (int i = 0; i < 3; i++)
	{
		GsVec v = c2->points.get(i) - shadowPoint;
		GsVec n = GsVec(0.0, 1.0, 0.0);
		curr = GsVec(1.0, 0.0, 0.0) - c2->points.get(i);
		curr = ((dot(curr, n)) / (dot(v, n)))*v;

		c2->points.push() = c2->points.get(i) + curr;
	}

	while (!clock.points.empty())
		clock.points.pop();

	rootg()->add(c);
	rootg()->add(c2);
	render();
}