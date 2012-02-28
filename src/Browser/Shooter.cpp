#include "stdafx.h"
#include "../Draw/gl.h"
#include "Object3D.h"
#include "dxfile.h"

#include "../windows_header.h"

extern "C"
{
_CRTIMP int    __cdecl rand(void);

/* Maximum value that can be returned by the rand function. */

#define RAND_MAX 0x7fff

}	// extern "C"

namespace System
{
using namespace IO;
using namespace UI;

#define REMAINDER(t, d) ((t) - (d)*floor((t)/(d)))

namespace LDraw
{
void X3DEXT gluSphere(LDraw::Graphics3D* pG, double radius, int slices, int stacks);
void X3DEXT gluCylinder(LDraw::Graphics3D* pG, double baseRadius, double topRadius, double height, int slices, int stacks);
}

class ShooterControl : public Control//, public MSWindows::WindowImpl//<ShooterControl>
{
public:
	ShooterControl();

protected:

	LDraw::GLState* m_serverState;
	LDraw::ClientState* m_clientState;

	void OnRender(UI::Graphics* pGraphics);
	void handleEvent(System::Event* evt);

	LDraw::vector3f m_pos;
	LDraw::vector3f m_angle;
	LDraw::vector3f m_lookangle;
	LDraw::vector3f m_vel;
	float m_accel;

	float m_speed;

	double m_distance;

	uint m_texName;
	uint m_texName2;
	uint m_texName3;
	uint m_texName4;
	uint m_texName5;
	uint m_texName6;
	LDraw::Bitmap* m_depthBitmap;
	LDraw::Bitmap* m_dummyBitmap;

	uint m_texName7;
	LDraw::Bitmap* m_noiseBitmap;

	LDraw::vector3f m_lightpos;
	LDraw::vector3f m_lightangle;
	double m_lightfov;
	double m_lightzFar;

	virtual bool ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult/*, DWORD dwMsgMapID*/ )
	{
		if (uMsg == WM_TIMER)
		{
		//	bool bHandled = true;
			OnTimer();
			return true;
		}
		else
			return false;
	}

	void OnTimer();

	class Particle
	{
	public:
		LDraw::vector3f m_pos;
		LDraw::vector3f m_angle;
		LDraw::vector3f m_direction;
	};

	void DrawObject(LDraw::Graphics3DImmediate* pG);

	Array<Particle*> m_particles;

	UI::Media3D::Document3D* document3d;
};

/* macros */

#define IX(i,j) ((i)+(N+2)*(j))

/* external definitions (from solver.c) */

extern "C" void dens_step ( int N, float * x, float * x0, float * u, float * v, float diff, float dt );
extern "C" void vel_step ( int N, float * u, float * v, float * u0, float * v0, float visc, float dt );

/* global variables */

static int N;
static float dt, diff, visc;
static float force, source;
static int dvel;

static float * u, * v, * u_prev, * v_prev;
static float * dens, * dens_prev;

static int win_id;
static int win_x, win_y;
static int mouse_down[3];
static int omx, omy, mx, my;

static void clear_data ( void )
{
	int i, size=(N+2)*(N+2);

	for ( i=0 ; i<size ; i++ ) {
		u[i] = v[i] = u_prev[i] = v_prev[i] = dens[i] = dens_prev[i] = 0.0f;
	}
}

static int allocate_data ( void )
{
	int size = (N+2)*(N+2);

	u			= (float *) malloc ( size*sizeof(float) );
	v			= (float *) malloc ( size*sizeof(float) );
	u_prev		= (float *) malloc ( size*sizeof(float) );
	v_prev		= (float *) malloc ( size*sizeof(float) );
	dens		= (float *) malloc ( size*sizeof(float) );	
	dens_prev	= (float *) malloc ( size*sizeof(float) );

	if ( !u || !v || !u_prev || !v_prev || !dens || !dens_prev ) {
		fprintf ( stderr, "cannot allocate data\n" );
		return ( 0 );
	}

	return ( 1 );
}

static void draw_density ( LDraw::Graphics3DImmediate* pG )
{
	int i, j;
	float x, y, h, d00, d01, d10, d11;

	h = 20.0/N;

	pG->glNormalf(0, 0, 1);

	pG->glBegin ( GL_QUADS );

		for ( i=0 ; i<=N ; i++ ) {
			x = (i-0.5f)*h;
			for ( j=0 ; j<=N ; j++ ) {
				y = (j-0.5f)*h;

				d00 = dens[IX(i,j)];
				d01 = dens[IX(i,j+1)];
				d10 = dens[IX(i+1,j)];
				d11 = dens[IX(i+1,j+1)];

				/*
				pG->glColorf ( d00, d00, d00 ); pG->glVertexf ( x, y );
				pG->glColorf ( d10, d10, d10 ); pG->glVertexf ( x+h, y );
				pG->glColorf ( d11, d11, d11 ); pG->glVertexf ( x+h, y+h );
				pG->glColorf ( d01, d01, d01 ); pG->glVertexf ( x, y+h );
				*/

				pG->glColorf (1,1,1, d00); pG->glVertexf ( x, y );
				pG->glColorf (1,1,1, d10); pG->glVertexf ( x+h, y );
				pG->glColorf (1,1,1, d11); pG->glVertexf ( x+h, y+h );
				pG->glColorf (1,1,1, d01); pG->glVertexf ( x, y+h );
			}
		}

	pG->glEnd ();
}

ShooterControl::ShooterControl()
{
	{
		N = 64;
		dt = 0.1f;
		diff = 0.0f;
		visc = 0.0f;
	//	force = 5.0f;
		force = 15.0f;
		source = 50.0f;

	allocate_data();
	clear_data ();
}

	m_serverState = new LDraw::GLState;
	m_clientState = new LDraw::ClientState;

	m_pos[1] = 1.75;

	m_lightpos[0] = -7;
	m_lightpos[1] = 35;
	m_lightpos[2] = -15;

	m_pos[0] = 2;

	m_lightpos[0] = 6;
	m_lightpos[1] = 20;
	m_lightpos[2] = 0;
	m_lightangle[0] = 90;
	m_lightangle[1] = 0;
	m_lightangle[2] = 0;
	m_lightfov = 50;
	m_lightzFar = 20;

	for (int i = 0; i < 100; i++)
	{
		Particle* pParticle = new Particle;

			pParticle->m_pos[0] = m_pos[0] + 2 + (rand() - RAND_MAX/2.0) * 8.0 / RAND_MAX ;
			pParticle->m_pos[1] = m_pos[1] + 0.5 + rand() * 5.0 / RAND_MAX ;
			pParticle->m_pos[2] = m_pos[2] + (rand() - RAND_MAX/2.0) * 80.0 / RAND_MAX ;
/*
		pParticle->m_pos[0] = rand() * 10.0 / RAND_MAX ;
		pParticle->m_pos[1] = 10.0 + rand() * 10.0 / RAND_MAX ;
		pParticle->m_pos[2] = rand() * -10.0 / RAND_MAX ;
*/
		pParticle->m_angle[0] = rand() * 360.0 / RAND_MAX;
		pParticle->m_angle[1] = rand() * 360.0 / RAND_MAX;
		pParticle->m_angle[2] = rand() * 360.0 / RAND_MAX;

		m_particles.Add(pParticle);
	}

	{
	LDraw::Graphics3DImmediate* pG = new LDraw::Graphics3DImmediate(m_serverState, m_clientState, NULL);
//	pG->AddRef();

	/*
	{
		Imaging::BitmapLoader loader;
		loader.Load("C:/floor1.png");

	//	uint texName;
		pG->glGenTextures(1, &m_texName);

		pG->glBindTexture(GL_TEXTURE_2D, m_texName);

		pG->glTexImage2D(GL_TEXTURE_2D, &loader.GetBitmap());

	}

	{
		Imaging::BitmapLoader loader;
		loader.Load("C:/wall1.png");

	//	uint texName;
		pG->glGenTextures(1, &m_texName2);

		pG->glBindTexture(GL_TEXTURE_2D, m_texName2);

		pG->glTexImage2D(GL_TEXTURE_2D, &loader.GetBitmap());

	}

	*/
	{
		Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
		loader->Load(new StringA("C:/particle1.png"));

	//	uint texName;
		pG->glGenTextures(1, &m_texName3);

		pG->glBindTexture(GL_TEXTURE_2D, m_texName3);

		pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		pG->glTexImage2D(GL_TEXTURE_2D, loader->GetBitmap());

	}

	{
		Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
		loader->Load(new StringA("C:/light1.png"));

	//	uint texName;
		pG->glGenTextures(1, &m_texName4);

		pG->glBindTexture(GL_TEXTURE_2D, m_texName4);
		pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		pG->glTexImage2D(GL_TEXTURE_2D, loader->GetBitmap());

	}
	{
		pG->glGenTextures(1, &m_texName5);

		pG->glBindTexture(GL_TEXTURE_2D, m_texName5);

		m_depthBitmap = new LDraw::Bitmap(512, 512, LDraw::PixelFormat_t::DEPTH_32);
		m_dummyBitmap = new LDraw::Bitmap(512, 512, LDraw::PixelFormat_t::RGB_32);

		pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		pG->glTexImage2D(GL_TEXTURE_2D, m_depthBitmap);
	}

	{
		Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
		loader->Load(new StringA("C:/tree1.png"));

	//	uint texName;
		pG->glGenTextures(1, &m_texName6);

		pG->glBindTexture(GL_TEXTURE_2D, m_texName6);
	//	pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		pG->glTexImage2D(GL_TEXTURE_2D, loader->GetBitmap());

	}

	/*
	{
		for (int y = 0; y < 1024; y++)
		{
			for (int x = 0; x < 1024; x++)
			{
				PerlinNoise_2D(
	}
	*/

	//	pG->Release();
}

	SetRetainedMode(false);

	m_accel = 0;
	m_speed = 0;
	m_distance = 0;

	{
		document3d = new UI::Media3D::Document3D;
		{
			DX::xfileparser standard_templates;
			{
				FileByteStream stream(new StringA("C:/standard_templates.x"));
				standard_templates.ParseX(&stream);
			}

			if (true)
			{
			//	UI::Media3D::C3DSLoader* loader = new UI::Media3D::C3DSLoader;
				FileByteStream stream(new StringA("C:/DXSDK/Samples/Media/tiny.x"));
			//	FileByteStream stream("C:/DXSDK/Samples/Media/spaceship 2.x");
			//	FileByteStream stream("C:/DXSDK/Samples/Media/airplane 2.x");
			//	FileByteStream stream("C:/DXSDK/Samples/Media/tiger.x");

				DX::xfileparser parser;
				parser.m_templates = standard_templates.m_templates;
				parser.ParseX(&stream);

			//	Convert(parse.m_objects);

				UI::Media3D::Group* group = new UI::Media3D::Group;
				UI::Media3D::Object3DCollection* children = new UI::Media3D::Object3DCollection;

				UI::Media3D::convert(document3d, parser.m_objects, children);

				for (int i = 0; i < document3d->m_references.GetSize(); i++)
				{
					document3d->m_references[i]->m_object = document3d->m_namedObjects[document3d->m_references[i]->m_name];
					document3d->m_references[i]->m_object->m_references.Add(document3d->m_references[i]);
				}

				group->m_Children = children;
				document3d->m_object = group;

				document3d->SetCurrentTime(0);

				UI::Media3D::Object3D* head = document3d->m_namedObjects[new StringA("Bip01_Head")];
			}
		}
	}

#if 0
	Create(NULL, LDraw::RectI(), NULL, WS_POPUP);
	SetTimer(1, 1000/20);
#endif
}

#define SPEED			4
#define TURN_SPEED	6

static void get_from_UI ( float * d, float * u, float * v )
{
	int i, j, size = (N+2)*(N+2);

	for ( i=0 ; i<size ; i++ ) {
		u[i] = v[i] = d[i] = 0.0f;
	}

	i = N/2;//(int)((       mx /(float)win_x)*N+1);
	j = 5;//(int)(((win_y-my)/(float)win_y)*N+1);

	mx = 15;
	omx = 15;

	my = 20;
	omy = 25;

	if (true)// mouse_down[0] )
	{
		u[IX(i,j)] = force * (mx-omx);
		v[IX(i,j)] = force * (my-omy);
	}

	if ((rand()%3) == 0)// mouse_down[2] )
	{
		int i = rand()%N;

		d[IX(i,j)] = source;
	}
}

void ShooterControl::OnTimer()
{
	get_from_UI ( dens_prev, u_prev, v_prev );


	vel_step ( N, u, v, u_prev, v_prev, visc, dt );
	dens_step ( N, dens, dens_prev, u, v, diff, dt );

	if (MSWindows::GetAsyncKeyState(VK_SPACE) & (1<<15))
	{
	//	gas = 1;
	}
	else if (MSWindows::GetAsyncKeyState(VK_UP) & (1<<15))
	{
	//	gas = -1;
	//	m_vel[0] += sin(gmRadians(m_angle[0])) * SPEED;
	//	m_vel[2] -= cos(gmRadians(m_angle[0])) * SPEED;
		m_accel = 0.2;
	}
	else if (MSWindows::GetAsyncKeyState(VK_DOWN) & (1<<15))
	{
	//	gas = -1;
	//	m_vel[0] -= sin(gmRadians(m_angle[0])) * SPEED;
	//	m_vel[2] += cos(gmRadians(m_angle[0])) * SPEED;
		m_accel = -0.2;
	}
	else
	{
		m_accel = 0;
	}
	
	if (MSWindows::GetAsyncKeyState(VK_LEFT) & (1<<15))
	{
		m_lookangle[1] -= TURN_SPEED;
		m_angle[1] = m_lookangle[1];
	//	steering += gmRadians(5);
	}
	else if (MSWindows::GetAsyncKeyState(VK_RIGHT) & (1<<15))
	{
		m_lookangle[1] += TURN_SPEED;
		m_angle[1] = m_lookangle[1];
	//	steering -= gmRadians(5);
	}

	if (MSWindows::GetAsyncKeyState(VK_PRIOR) & (1<<15))
	{
		m_lookangle[0] += TURN_SPEED;
		if (m_lookangle[0] > 90)
		{
			m_lookangle[0] = 90;
		}
	}
	else if (MSWindows::GetAsyncKeyState(VK_NEXT) & (1<<15))
	{
		m_lookangle[0] -= TURN_SPEED;
		if (m_lookangle[0] < -90)
		{
			m_lookangle[0] = -90;
		}
	}

//	m_vel.length();
//	m_vel

	m_vel[0] = sin(gmRadians(m_angle[1])) * m_speed;
	m_vel[2] = -cos(gmRadians(m_angle[1])) * m_speed;

	m_distance += m_speed;

	document3d->SetCurrentTime(REMAINDER(m_distance * 1, 10));

	m_pos += m_vel;

	for (int i = 0; i < m_particles.GetSize(); i++)
	{
		Particle* pParticle = m_particles[i];

	//	pParticle->m_pos += m_vel;

		/*
		pParticle->m_pos[0] += (rand() - RAND_MAX / 2.0) * 0.01 / RAND_MAX;
		pParticle->m_pos[1] += (rand() - RAND_MAX / 2.0) * 0.01 / RAND_MAX;
		pParticle->m_pos[2] += (rand() - RAND_MAX / 2.0) * 0.01 / RAND_MAX;
		*/

		pParticle->m_angle[0] += rand() * 5 / RAND_MAX;
		pParticle->m_angle[1] += rand() * 5 / RAND_MAX;
		pParticle->m_angle[2] += rand() * 5 / RAND_MAX;

		if (pParticle->m_pos[1] < 0)
			pParticle->m_pos[1] = 0;

		/*
		if (LDraw::gmDistance(pParticle->m_pos, m_pos) > 30)
		{
			pParticle->m_pos[0] = m_pos[0] + (rand() - RAND_MAX/2.0) * 10.0 / RAND_MAX ;
			pParticle->m_pos[1] = m_pos[1] + rand() * 10.0 / RAND_MAX ;
			pParticle->m_pos[2] = m_pos[2] + (rand() - RAND_MAX/2.0) * -10.0 / RAND_MAX ;

		//	pParticle->m_pos = m_pos;
		}
		*/
	}

	//m_speed += m_accel;
	/*
	m_vel[0] += m_accel;
	m_vel[1] += m_accel;
	m_vel[2] += m_accel;
	m_accel -= 2;
	if (m_accel < 0) m_accel = 0;
	*/

	if (m_accel > 0)
	{
		m_speed += 0.1;
		if (m_speed > 2)
			m_speed = 2;
	}
	else if (m_accel < 0)
	{
		m_speed -= 0.1;
		if (m_speed < -1)
			m_speed = -1;
	}
	else
	{
		if (m_speed > 0)
		{
			m_speed -= 0.5;
			if (m_speed < 0) m_speed = 0;
		}
		else if (m_speed < 0)
		{
			m_speed += 0.5;
			if (m_speed > 0) m_speed = 0;
		}
	}

//	m_lightangle[1] += 2;

	m_lightpos[2] -= 1.2;
	if (m_lightpos[2] < -100)
		m_lightpos[2] = 100;

/*
	m_vel /= 2;
	if (m_vel[0] < 0.05) m_vel[0] = 0;
	if (m_vel[1] < 0.05) m_vel[1] = 0;
	if (m_vel[2] < 0.05) m_vel[2] = 0;
*/

	InvalidateRender();
}

void Cube(LDraw::Graphics3D* pG, float width, float height, float depth, float dx = 0, float dy = 0, float dz = 0);

//-----------------------------------------------------------------------------
// Name: buildAxisAlignedBBMatrix()
// Desc: 
//-----------------------------------------------------------------------------
void buildAxisAlignedBBMatrix( float m[16], float x, float y, float z )
{
    float pi    = 3.141592654f;
    float theta = -180 * atan2f(m[8], m[10]) / pi;
    float d     = x*x + y*y + z*z;
    float ct    = cosf(gmRadians(theta));
    float st    = sinf(gmRadians(theta));

    // Normalize
    if( d > 0 )
    {
	    d = 1/d;
	    x *= d;
	    y *= d;
	    z *= d;
    }

    // Clear out the view matrix passed in
    m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
    m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
    m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

    //---------------------------------------------
    // R = uu' + cos(theta)*(I-uu') + sin(theta)*S
    //
    // S =  0  -z   y    u' = (x, y, z)
    //	    z   0  -x
    //	   -y   x   0
    //---------------------------------------------

     m[0] = x*x + ct*(1-x*x) + st*0;
     m[4] = x*y + ct*(0-x*y) + st*-z;
     m[8] = x*z + ct*(0-x*z) + st*y;

     m[1] = y*x + ct*(0-y*x) + st*z;
     m[5] = y*y + ct*(1-y*y) + st*0;
     m[9] = y*z + ct*(0-y*z) + st*-x;

     m[2] = z*x + ct*(0-z*x) + st*-y;
     m[6] = z*y + ct*(0-z*y) + st*x;
     m[10]= z*z + ct*(1-z*z) + st*0;
}

void ShooterControl::DrawObject(LDraw::Graphics3DImmediate* pG)
{
		pG->glColorf(1,1,1);
	{
		pG->glNormalf(0, 1, 0);

		for (int x = 100; x >= -100; x -= 50)
		{
			pG->glBegin(GL_QUAD_STRIP);

			for (int z = 100; z >= -100; z -= 50)
			{
			//	pG->glTexCoordf(x/800.0+1, z/800.0+1);
				pG->glVertexf(x, 0, z);

			//	pG->glTexCoordf(1, 0);
				pG->glVertexf(x+50, 0, z);
			}

			pG->glEnd();
		}
	}

	/*
	{
		pG->glPushMatrix();
		pG->glColorf(0,0.9,1);
		pG->glTranslatef(1, 1.5, -1);
	//	pG->glRotatef(45, 1, 0, 0);
	//	pG->glRotatef(0, 0, 1, 0);
	//	pG->glRotatef(0, 0, 0, 1);
		Cube(pG, 3.5, 3, 3.5);
		pG->glPopMatrix();
	}

	{
		pG->glPushMatrix();
		pG->glColorf(0,0.9,1);
		pG->glTranslatef(6, 5, -1);
	//	pG->glRotatef(45, 1, 0, 0);
	//	pG->glRotatef(0, 0, 1, 0);
	//	pG->glRotatef(0, 0, 0, 1);
		Cube(pG, 1, 1, 1);
		pG->glPopMatrix();
	}

	{
		pG->glPushMatrix();
		pG->glColorf(0,0.9,1);
		pG->glTranslatef(1, 14, -1);
	//	pG->glRotatef(45, 1, 0, 0);
	//	pG->glRotatef(0, 0, 1, 0);
	//	pG->glRotatef(0, 0, 0, 1);
		Cube(pG, 2, 2, 2);
		pG->glPopMatrix();
	}
	*/

	/*
	{
		pG->glPushMatrix();
		pG->glColorf(1,0.9,0.3);
		pG->glTranslatef(0, 8, 0);
		pG->glRotatef(45, 0, 1, 0);
		pG->glRotatef(20, 1, 0, 0);
//		LDraw::gluCylinder(pG, 5, 5, 30, 4, 1);
		Cube(pG, 1.5, 1.5, 1.5);
		pG->glPopMatrix();
	}
	*/

#if 1
	{
		pG->glPushMatrix();
		pG->glColorf(0.6,0.9,0.6);
		pG->glTranslatef(0, 10, -220);
		/*
		pG->glRotatef(45, 0, 1, 0);
		pG->glRotatef(90, 1, 0, 0);
		LDraw::gluCylinder(pG, 5, 5, 30, 4, 1);
		*/
		Cube(pG, 5, 20, 5);
		pG->glPopMatrix();
	}

	{
		pG->glPushMatrix();
		pG->glColorf(0.6,0.9,0.6);
		pG->glTranslatef(0, 10, -120);
//		pG->glRotatef(45, 0, 1, 0);
//		pG->glRotatef(90, 1, 0, 0);
//		LDraw::gluCylinder(pG, 5, 5, 30, 4, 1);
		Cube(pG, 5, 20, 5);
		pG->glPopMatrix();
	}

	{
		pG->glPushMatrix();
		pG->glColorf(0.6,0.9,0.6);
		pG->glTranslatef(0, 10, -20);
//		pG->glRotatef(45, 0, 1, 0);
//		pG->glRotatef(90, 1, 0, 0);
//		LDraw::gluCylinder(pG, 5, 5, 30, 4, 1);
		Cube(pG, 5, 20, 5);
		pG->glPopMatrix();
	}
#endif

#if 1
	{
		pG->glPushMatrix();
		pG->glColorf(0.6,0.9,0.6);
		pG->glTranslatef(0, 0, 0);
	//	pG->glRotatef(90, 1, 0, 0);
	//	LDraw::gluCylinder(pG, 5, 5, 10, 16, 1);
		{
			{
				pG->glBegin(GL_QUAD_STRIP);
				pG->glNormalf(-1, 0, 0);

				for (int z = 200; z >= -200; z -= 20)
				{
					pG->glTexCoordf(z/20.0, 0);
					pG->glVertexf(1, 5, z);

					pG->glTexCoordf(z/20.0, 1);
					pG->glVertexf(1, 0, z);
				}

				pG->glEnd();
			}

			{
				pG->glBegin(GL_QUAD_STRIP);
				pG->glNormalf(1, 0, 0);

				for (int z = 200; z >= -200; z -= 20)
				{
					pG->glTexCoordf(z/20.0, 0);
					pG->glVertexf(-1, 5, z);
					pG->glTexCoordf(z/20.0, 1);
					pG->glVertexf(-1, 0, z);
				}
				pG->glEnd();
			}

			{
				pG->glBegin(GL_QUAD_STRIP);
				pG->glNormalf(0, 1, 0);

				for (int z = 200; z >= -200; z -= 20)
				{
					pG->glTexCoordf(z/20.0, 0);
					pG->glVertexf(1, 5, z);
					pG->glTexCoordf(z/20.0, 1);
					pG->glVertexf(-1, 5, z);
				}
				pG->glEnd();
			}
		}
		pG->glPopMatrix();
	}
#endif

	if (false)
	{
		pG->glPushAttrib(GL_ENABLE_BIT);

		pG->glColorf(0.0,1.0,0.0);

		pG->ActiveTexture(GL_TEXTURE0);
		pG->glBindTexture(GL_TEXTURE_2D, m_texName6);
	//	pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		pG->glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
		pG->glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
		pG->glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PREVIOUS);

		pG->glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
		pG->glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_TEXTURE);
		
		pG->glEnable(GL_TEXTURE_2D);

		pG->glAlphaFunc(GL_GREATER, 0);
		pG->glEnable(GL_ALPHA_TEST);

		pG->glDisable(GL_CULL_FACE);

	//	pG->glDisable(GL_DEPTH_TEST);

		pG->glPushMatrix();

		pG->glTranslatef(4, 4 - 0.6, -10);
		pG->glScalef(4, 4, 4);

		{
        float mat[16];
        pG->glGetFloatv( GL_MODELVIEW_MATRIX, mat );
        buildAxisAlignedBBMatrix( mat, 0.0f, 1.0f, 0.0f ); 
			pG->glMultMatrixf( mat );
		}

		pG->glPushMatrix();

	//	pG->glRotatef(-45, 0, 1, 0);
	//	pG->glRotatef(-20, 1, 0, 0);
	//	pG->glRotatef(2, 1, 0, 0);

		pG->glNormalf(0, 0, -1);

		pG->glBegin(GL_QUADS);

		pG->glTexCoordf(0, 0);
		pG->glVertexf(-1, -1, 0);

		pG->glTexCoordf(1, 0);
		pG->glVertexf(1, -1, 0);

		pG->glTexCoordf(1, 1);
		pG->glVertexf(1, 1, 0);

		pG->glTexCoordf(0, 1);
		pG->glVertexf(-1, 1, 0);

		pG->glEnd();

		pG->glPopMatrix();

		/*
		pG->glPushMatrix();
		
		{
        float mat[16];
        pG->glGetFloatv( GL_MODELVIEW_MATRIX, mat );
        buildAxisAlignedBBMatrix( mat, 0.0f, 1.0f, 0.0f ); 
			pG->glMultMatrixf( mat );
		}
		pG->glRotatef(90, 0, 1, 0);

		pG->glBegin(GL_QUADS);

		pG->glTexCoordf(0, 0);
		pG->glVertexf(-1, -1, 0);

		pG->glTexCoordf(1, 0);
		pG->glVertexf(1, -1, 0);

		pG->glTexCoordf(1, 1);
		pG->glVertexf(1, 1, 0);

		pG->glTexCoordf(0, 1);
		pG->glVertexf(-1, 1, 0);

		pG->glEnd();

		pG->glPopMatrix();
*/

		pG->glPopAttrib();
	}

	if (true)
	{
		float size = 0.1;

		pG->glPushAttrib(GL_ENABLE_BIT);

	//	pG->ActiveTexture(GL_TEXTURE0);
	//	pG->glBindTexture(GL_TEXTURE_2D, m_texName3);
	//	pG->glEnable(GL_TEXTURE_2D);

	//	pG->glEnable(GL_BLEND);
	//	pG->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < m_particles.GetSize(); i++)
		{
			Particle* pParticle = m_particles[i];

			pG->glPushMatrix();

			pG->glTranslatef(pParticle->m_pos[0], pParticle->m_pos[1], pParticle->m_pos[2]);
			pG->glRotatef(pParticle->m_angle[0], 1, 0, 0);
			pG->glRotatef(pParticle->m_angle[1], 0, 1, 0);
			pG->glRotatef(pParticle->m_angle[2], 0, 0, 1);

			pG->glBegin(GL_TRIANGLES);

			LDraw::vector3f normal = LDraw::cross(LDraw::vector3f(1, 0, 0), LDraw::vector3f(0, 1, 0));
			pG->glNormal(normal);

			pG->glTexCoordf(0, 0);
			pG->glVertexf(-size, -size, -size);

			pG->glTexCoordf(1, 0);
			pG->glVertexf(+size, -size, -size);

			pG->glTexCoordf(1, 1);
			pG->glVertexf(+size, +size, +size);


			pG->glEnd();

			pG->glPopMatrix();
		}

		pG->glPopAttrib();
	}
}

#if 0
void 
gluLookAt(LDraw::Graphics3DImmediate* pG, GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx,
	  GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy,
	  GLdouble upz)
{
    float forward[3], side[3], up[3];
    GLfloat m[4][4];

    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;

    up[0] = upx;
    up[1] = upy;
    up[2] = upz;

    normalize(forward);

    /* Side = forward x up */
    cross(forward, up, side);
    normalize(side);

    /* Recompute up as: up = side x forward */
    cross(side, forward, up);

    *(gmMatrix4f*)m = gmMatrix4f::getIdentity();//__gluMakeIdentityf(&m[0][0]);
    m[0][0] = side[0];
    m[1][0] = side[1];
    m[2][0] = side[2];

    m[0][1] = up[0];
    m[1][1] = up[1];
    m[2][1] = up[2];

    m[0][2] = -forward[0];
    m[1][2] = -forward[1];
    m[2][2] = -forward[2];

    glMultMatrixf(&m[0][0]);
    glTranslated(-eyex, -eyey, -eyez);
}
#endif

void ShooterControl::OnRender(UI::Graphics* pGraphics)
{
	LDraw::SizeD actualSize = get_ActualSize();

	if (true)
	// shadow map
	{
		LDraw::GraphicsO* p = new LDraw::GraphicsO(m_dummyBitmap);

		LDraw::BitmapData depthBitmapData;
		m_depthBitmap->LockBits(NULL, LDraw::ImageLockModeWrite, &depthBitmapData);

		p->SetDepthBuffer(depthBitmapData.Scan0);

		LDraw::Graphics3DImmediate* pG = new LDraw::Graphics3DImmediate(m_serverState, m_clientState, p);
	//	pG->AddRef();

		pG->glClear(GL_DEPTH_BUFFER_BIT);

		pG->glEnable(GL_DEPTH_TEST);
		pG->glDepthFunc(GL_LESS);

		pG->glViewport(0, 0, 512, 512);

		pG->glMatrixMode(GL_PROJECTION);
		pG->glLoadIdentity();
		pG->gluPerspective(m_lightfov, 1, 2, m_lightzFar);

		pG->glMatrixMode(GL_MODELVIEW);
		pG->glLoadIdentity();

	//	m_lightangle[0] = 0;	// downwards
//		m_lightangle[1] = 0;

		{
		//	pG->glScalef(0.1, 0.1, 0.1);
			pG->glRotatef(m_lightangle[0], 1, 0, 0);
			pG->glRotatef(m_lightangle[1], 0, 1, 0);
			pG->glRotatef(m_lightangle[2], 0, 0, 1);
			pG->glTranslatef(-m_lightpos[0], -m_lightpos[1], -m_lightpos[2]);
		}
/*
	pG->glRotatef(m_lookangle[0], 1, 0, 0);
	pG->glRotatef(m_lookangle[1], 0, 1, 0);
	pG->glTranslatef(-m_pos[0], -8, -m_pos[2]);
*/
		pG->glColorMask(false, false, false, false);
	//	pG->glEnable(GL_CULL_FACE);
	//	pG->glCullFace(GL_FRONT);

		DrawObject(pG);

		pG->glColorMask(true, true, true, true);
	//	pG->glCullFace(GL_BACK);
	//	pG->glDisable(GL_CULL_FACE);

		/*
		int width = dynamic_cast<LDraw::GraphicsO*>(pGraphics->m_p)->GetBitmap().GetWidth();
		int height = dynamic_cast<LDraw::GraphicsO*>(pGraphics->m_p)->GetBitmap().GetHeight();
		uint32* depthBuffer = (uint32*)dynamic_cast<LDraw::GraphicsO*>(pGraphics->m_p)->GetDepthBuffer();
		*/

		if (false)
		{
			for (int y = 0; y < 1024; y++)
			{
				uint8* dst = (uint8*)(depthBitmapData.Scan0 + y* depthBitmapData.Stride);

				for (int x = 0; x < 1024; x++)
				{
					uint32 depth = *(uint32*)dst;
					depth >>= 24;

					dst[0] = depth;
					dst[1] = depth;
					dst[2] = depth;

					dst += 4;
				}
			}
		}

		m_depthBitmap->UnlockBits(&depthBitmapData);

		//pG->Release();

		if (false)
		{
			m_depthBitmap->SetPixelFormat(LDraw::PixelFormat_t::RGB_32);

			pGraphics->DrawImage(m_depthBitmap, 0, 0);

			return;
		}

	//	m_depthBitmap.SetPixelFormat(RGB_32);
	}

	pGraphics->TranslateTransform(-0.25, -0.25);

#if 1
	LDraw::Graphics3DImmediate* pG = new LDraw::Graphics3DImmediate(m_serverState, m_clientState, dynamic_cast<LDraw::GraphicsO*>(pGraphics->m_p));
//	pG->AddRef();
#else

	LDraw::DisplayList* list = new LDraw::DisplayList;
	LDraw::Graphics3DList* pG = new LDraw::Graphics3DList(m_document->m_glState, m_document->m_clientState, list);
//	pG->AddRef();
#endif

	pG->glPushAttrib(GL_ENABLE_BIT);

	pG->glEnable(GL_CULL_FACE);
	pG->glCullFace(GL_BACK);

	pG->glDepthFunc(GL_LESS);
	pG->glEnable(GL_DEPTH_TEST);
	pG->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pG->glViewport(0, 0, actualSize.Width, actualSize.Height);
	//double viewport[4] = {0, 0, actualSize.Width, actualSize.Height};

	double fov = 45;

	pG->glMatrixMode(GL_PROJECTION);
	pG->glLoadIdentity();
	pG->gluPerspective(fov, (float)actualSize.Width / (float)actualSize.Height, 1.0, 100.0);

	pG->glMatrixMode(GL_MODELVIEW);
	pG->glLoadIdentity();

	pG->glPushMatrix();

	pG->glRotatef(m_lookangle[0], 1, 0, 0);
	pG->glRotatef(m_lookangle[1], 0, 1, 0);
	pG->glTranslatef(-m_pos[0], -m_pos[1], -m_pos[2]);

	pG->glEnable(GL_LIGHTING);

	{
		float light_diffuse[4] = {1,0.9,0.8,1};
		float light_position[4];// = {0, 1, 1, 0};

		light_position[0] = m_lightpos[0];
		light_position[1] = m_lightpos[1];
		light_position[2] = m_lightpos[2];
		light_position[3] = 1;

		pG->glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		pG->glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		pG->glEnable(GL_LIGHT0);
	}

	pG->glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// light bulb
	{
		pG->glPushMatrix();
		pG->glColorf(0.9,0.9,0.6);
		pG->glTranslatef(m_lightpos[0], m_lightpos[1], m_lightpos[2]);
		LDraw::gluSphere(pG, 0.5, 4, 4);
		pG->glPopMatrix();
	}

//	DrawObject(pG);

	if (true)
	{
	//	pG->glDepthFunc(GL_LEQUAL);
		pG->glDepthFunc(GL_LESS);
		//pG->glDisable(GL_LIGHTING);

		if (true)	// enable shadow for a light
		{
		// First convert from [-1...1] to [0..1]
		/*
		LDraw::gmMatrix4f	matrix = LDraw::gmMatrix4f::getIdentity();

		matrix = LDraw::gmMatrix4f::getTranslate(0.5, 0.5, 0) * matrix;
		matrix = LDraw::gmMatrix4f::getScale(0.5, 0.5, 1) * matrix;

		matrix = LDraw::gmMatrix4f::getPerspective(90, 1, 1, 15000) * matrix;
		matrix = LDraw::gmMatrix4f::getRotate(m_lightangle[0], LDraw::vector3f(1, 0, 0)) * matrix;
		matrix = LDraw::gmMatrix4f::getRotate(m_lightangle[1], LDraw::vector3f(0, 1, 0)) * matrix;
		matrix = LDraw::gmMatrix4f::getRotate(m_lightangle[2], LDraw::vector3f(0, 0, 1)) * matrix;
		matrix = LDraw::gmMatrix4f::getTranslate(-5, -20, -0) * matrix;
		//matrix = LDraw::gmMatrix4f::getScale(0.3, 0.3, 0.3) * matrix;
		*/

		if (true)
		{
			pG->glPushMatrix();
			pG->glLoadIdentity();

			pG->glTranslatef(0.5, 0.5, 0);
			pG->glScalef(0.5, 0.5, 1);

			pG->gluPerspective(m_lightfov, 1, 2, m_lightzFar);

			{
				
				pG->glRotatef(m_lightangle[0], 1, 0, 0);
				pG->glRotatef(m_lightangle[1], 0, 1, 0);
				pG->glRotatef(m_lightangle[2], 0, 0, 1);
				pG->glTranslatef(-m_lightpos[0], -m_lightpos[1], -m_lightpos[2]);
			//	pG->glScalef(0.08, 0.08, 1);

			//	pG->glRotatef(90, 1, 0, 0);
			//	pG->glTranslatef(-0, -5, 0);
				
			}
	/*	pG->glRotatef(m_lookangle[0], 1, 0, 0);
		pG->glRotatef(m_lookangle[1], 0, 1, 0);
		pG->glTranslatef(-m_pos[0], -8, -m_pos[2]);
	*/
			//LDraw::gmMatrix4f matrix;
			float matrix[16];
			pG->glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
			pG->glPopMatrix();

		//	*(LDraw::gmMatrix4f*)matrix = (*(LDraw::gmMatrix4f*)matrix).getTransposed();
	//		matrix = matrix.getInverse();

			pG->ActiveTexture(GL_TEXTURE4);
			pG->glBindTexture(GL_TEXTURE_2D, m_texName4);

			pG->glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			pG->glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			pG->glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			pG->glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

			pG->glTexGenfv(GL_S, GL_EYE_PLANE, &matrix[0]);
			pG->glTexGenfv(GL_T, GL_EYE_PLANE, &matrix[4]);
			pG->glTexGenfv(GL_R, GL_EYE_PLANE, &matrix[8]);
			pG->glTexGenfv(GL_Q, GL_EYE_PLANE, &matrix[12]);

			//	float s_plane[] = {0,0,0,0};
			//	float t_plane[] = {1,0,0,0};
/*				float r_plane[] = {0,0,1,0};
				float q_plane[] = {0,0,0,1};
*/
			//	pG->glTexGenfv(GL_S, GL_EYE_PLANE, s_plane);
			//	pG->glTexGenfv(GL_T, GL_EYE_PLANE, t_plane);
		//		pG->glTexGenfv(GL_R, GL_EYE_PLANE, r_plane);
		//		pG->glTexGenfv(GL_Q, GL_EYE_PLANE, q_plane);

			pG->glEnable(GL_TEXTURE_GEN_S);
			pG->glEnable(GL_TEXTURE_GEN_T);
			pG->glEnable(GL_TEXTURE_GEN_R);
			pG->glEnable(GL_TEXTURE_GEN_Q);

			pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		//	pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		//	pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		//	pG->glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

			pG->glEnable(GL_TEXTURE_2D);
		}

		if (true)
		{
			pG->glPushMatrix();
			pG->glLoadIdentity();

			pG->glTranslatef(0.5, 0.5, 0);
			pG->glScalef(0.5, 0.5, 1);

			pG->gluPerspective(m_lightfov, 1, 2, m_lightzFar);

			{
				
				pG->glRotatef(m_lightangle[0], 1, 0, 0);
				pG->glRotatef(m_lightangle[1], 0, 1, 0);
				pG->glRotatef(m_lightangle[2], 0, 0, 1);
				pG->glTranslatef(-m_lightpos[0], -m_lightpos[1], -m_lightpos[2]);
			//	pG->glScalef(0.08, 0.08, 1);

			//	pG->glRotatef(90, 1, 0, 0);
			//	pG->glTranslatef(-0, -5, 0);
				
			}
	/*	pG->glRotatef(m_lookangle[0], 1, 0, 0);
		pG->glRotatef(m_lookangle[1], 0, 1, 0);
		pG->glTranslatef(-m_pos[0], -8, -m_pos[2]);
	*/
			//LDraw::gmMatrix4f matrix;
			float matrix[16];
			pG->glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
			pG->glPopMatrix();

		//	*(LDraw::gmMatrix4f*)matrix = (*(LDraw::gmMatrix4f*)matrix).getTransposed();
	//		matrix = matrix.getInverse();

			pG->ActiveTexture(GL_TEXTURE5);
			pG->glBindTexture(GL_TEXTURE_2D, m_texName5);

			pG->glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			pG->glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			pG->glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			pG->glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

			pG->glTexGenfv(GL_S, GL_EYE_PLANE, &matrix[0]);
			pG->glTexGenfv(GL_T, GL_EYE_PLANE, &matrix[4]);
			pG->glTexGenfv(GL_R, GL_EYE_PLANE, &matrix[8]);
			pG->glTexGenfv(GL_Q, GL_EYE_PLANE, &matrix[12]);

			//	float s_plane[] = {0,0,0,0};
			//	float t_plane[] = {1,0,0,0};
/*				float r_plane[] = {0,0,1,0};
				float q_plane[] = {0,0,0,1};
*/
			//	pG->glTexGenfv(GL_S, GL_EYE_PLANE, s_plane);
			//	pG->glTexGenfv(GL_T, GL_EYE_PLANE, t_plane);
		//		pG->glTexGenfv(GL_R, GL_EYE_PLANE, r_plane);
		//		pG->glTexGenfv(GL_Q, GL_EYE_PLANE, q_plane);

			pG->glEnable(GL_TEXTURE_GEN_S);
			pG->glEnable(GL_TEXTURE_GEN_T);
			pG->glEnable(GL_TEXTURE_GEN_R);
			pG->glEnable(GL_TEXTURE_GEN_Q);

			pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
			pG->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
			pG->glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

			pG->glEnable(GL_TEXTURE_2D);
		}

		if (true)
		{
			pG->ActiveTexture(GL_TEXTURE6);
			pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

			pG->glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_ADD);
			pG->glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE3);	// Before 4
			pG->glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE5);

			pG->glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
			pG->glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_TEXTURE3);	// Before 4

			pG->glEnable(GL_TEXTURE_2D);
		}
		}

		DrawObject(pG);
	}


	/*
	UI::Media3D::Group* head = (UI::Media3D::Group*)document3d->m_namedObjects["Bip01_Head"];
	float m[16];
	head->m_combinedTransform.GetInverse().Get(m);
	pG->glRotatef(90, 0, 0, 1);
	{
		float scale = 0.05;
		pG->glScalef(scale, scale, scale);
		pG->glMultMatrixf(m);
		pG->glScalef(1/scale, 1/scale, 1/scale);
	}
	*/

#if 0

	pG->glEnable(GL_DEPTH_TEST);
	pG->glEnable(GL_LIGHTING);

	{
		float light_diffuse[4] = {1,0.9,0.8,1};
		float light_position[4] = {0, 1, 1, 0};
		pG->glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		pG->glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		pG->glEnable(GL_LIGHT0);
	}

	{

	}

	/*
	{
		float light_diffuse[4] = {1,0.8,0.6,1};
		float light_position[4] = {1, 0, 0, 0};
		pG->glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		pG->glLightfv(GL_LIGHT1, GL_POSITION, light_position);
		pG->glEnable(GL_LIGHT1);
	}
	*/

//	pG->glEnable(GL_FOG);

	pG->Fogf(GL_FOG_DENSITY, 1/ 550.0);
	float fog_color[4] = { 0, 0, 0 };
	pG->Fogfv(GL_FOG_COLOR, fog_color);

	{

		{
			pG->glPushAttrib(GL_ENABLE_BIT);

		//	pG->ActiveTexture(GL_TEXTURE0);
		//	pG->glBindTexture(GL_TEXTURE_2D, m_texName);
		//	pG->glEnable(GL_TEXTURE_2D);

			pG->glColorf(0.4,0.9,0.4);

			pG->glNormalf(0, 1, 0);

			/*
			pG->glVertexf(-2, 2, -1);
			pG->glVertexf(2, 2, -1);
			pG->glVertexf(2, -2, -1);
			pG->glVertexf(-2, -2, -1);
			*/

			//pG->glTranslatef(m_pos[0], 0, m_pos[2]);

			pG->glPopAttrib();
		}

		{
		//	pG->ActiveTexture(GL_TEXTURE0);
		//	pG->glBindTexture(GL_TEXTURE_2D, m_texName2);
		//	pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//	pG->glEnable(GL_TEXTURE_2D);

			/*
			{
				pG->glPushMatrix();
				pG->glColorf(0.6,0.9,0.6);
				pG->glTranslatef(0, 30, 0);
				pG->glRotatef(45, 0, 1, 0);
				pG->glRotatef(90, 1, 0, 0);
				LDraw::gluCylinder(pG, 5, 5, 30, 4, 1);
				pG->glPopMatrix();
			}
			*/

			// Draw light
			if (false)
			{
				float s_plane[] = {1,0,0,0};
				float t_plane[] = {0,1,0,0};
				float r_plane[] = {0,0,1,0};
				float q_plane[] = {0,0,0,1};

				pG->glPushAttrib(GL_ENABLE_BIT);

				pG->ActiveTexture(GL_TEXTURE1);
				pG->glBindTexture(GL_TEXTURE_2D, m_texName4);
			//	pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
				pG->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
				pG->glEnable(GL_TEXTURE_2D);

				pG->glDepthFunc(GL_LEQUAL);

				pG->glTexGenfv(GL_S, GL_EYE_PLANE, s_plane);
				pG->glTexGenfv(GL_T, GL_EYE_PLANE, t_plane);
				pG->glTexGenfv(GL_R, GL_EYE_PLANE, r_plane);
				pG->glTexGenfv(GL_Q, GL_EYE_PLANE, q_plane);

				pG->glEnable(GL_TEXTURE_GEN_S);
				pG->glEnable(GL_TEXTURE_GEN_T);
				pG->glEnable(GL_TEXTURE_GEN_R);
				pG->glEnable(GL_TEXTURE_GEN_Q);

				pG->glMatrixMode(GL_TEXTURE);
				pG->glPushMatrix();

				pG->glTranslatef(0.5, 0.5, 0);	// Because of texture coordinates are 0..1

				pG->glRotatef(m_lightangle[0], 1, 0, 0);
				pG->glRotatef(m_lightangle[1], 0, 1, 0);
				pG->glRotatef(m_lightangle[2], 0, 0, 1);
				pG->glScalef(0.1, 0.1, 0.1);
				pG->glTranslatef(40, -6, -8);
			//	pG->gluPerspective(45, 1, 1, 1000);
				pG->glMatrixMode(GL_MODELVIEW);

				DrawObject(pG);

				/*
				{
					pG->glBegin(GL_QUADS);

					pG->glVertexf(-5, 0, 0);
					pG->glVertexf(-5, 15, 0);
					pG->glVertexf(5, 15, 0);
					pG->glVertexf(5, 0, 0);

					pG->glEnd();
				}
				*/

				pG->ActiveTexture(GL_TEXTURE1);
				pG->glMatrixMode(GL_TEXTURE);
				pG->glPopMatrix();
				pG->glMatrixMode(GL_MODELVIEW);

				pG->glPopAttrib();
				pG->glDepthFunc(GL_LESS);
			}
			else
			{
				DrawObject(pG);
			}

		}
	}
#endif

	if (false)
	{
		/*
		{
        float mat[16];
        pG->glGetFloatv( GL_MODELVIEW_MATRIX, mat );
        buildAxisAlignedBBMatrix( mat, 0.0f, 1.0f, 0.0f ); 
			pG->glMultMatrixf( mat );
		}
		*/

	//	pG->glTranslatef(-1, -1, -1);
		pG->glDisable(GL_LIGHTING);
		pG->glDisable(GL_CULL_FACE);
		pG->glEnable(GL_BLEND);
		pG->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		draw_density(pG);
	}

	pG->glPopAttrib();
	pG->glPopMatrix();

//	pG->Release();
}

void ShooterControl::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown" || *evt->get_type() == L"mousemove")
		{
			UI::MouseEvent* mouseEvt = static_cast<UI::MouseEvent*>(evt);
			LDraw::PointD mousepos = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			LDraw::SizeD actualSize = get_ActualSize();
			/*

			LDraw::vector3f xyz = LDraw::vector3f(mousepos.X, actualSize.Height - mousepos.Y, -2);

		//	pG->glMatrixMode(GL_PROJECTION);
		//	pG->glLoadIdentity();
			LDraw::gmMatrix4f proj = LDraw::gmMatrix4f::getPerspective(45, (GLfloat)actualSize.Width / (GLfloat)actualSize.Height, 1.0, 100.0);

			LDraw::gmMatrix4f model;
			model = LDraw::gmMatrix4f::getRotate(m_lookangle[0], LDraw::vector3f(1, 0, 0));
			model = LDraw::gmMatrix4f::getRotate(m_lookangle[1], LDraw::vector3f(0, 1, 0)) * model;
			model = LDraw::gmMatrix4f::getTranslate(-m_pos[0], -8, -m_pos[2]) * model;

			double viewport[4] =
			{
				0, 0, actualSize.Width, actualSize.Height
			};

			m_lightpos = xyz.UnProject(model, proj, viewport);
			*/

		//	m_lightpos[2] = (-actualSize.Width/2 + mousepos.X) / 10;
		//	m_lightpos[1] = (actualSize.Height - mousepos.Y) / 10;
		}
		else if (*evt->get_type() == L"keydown" || *evt->get_type() == L"keyup")
		{
			evt->stopPropagation();

			//MessageBeep(-1);


			InvalidateRender();
		}
	}
}

}
