#ifndef __Direct3DBase__
#define __Direct3DBase__

#include <windowsx.h>
#include <stdio.h>
#include <d3dx9.h>
#include "drawableentity.h"

class Direct3DBase: public DrawableEntity
{
	private:		
		
		static Direct3DBase * _instance;
		HINSTANCE _hInstance;

	protected:
		IDirect3DDevice9 * _device; 
		D3DXVECTOR3 _camPos;
		D3DXVECTOR3 _camLook;

		int _width;
		int _height;
		bool _windowed;
		bool _console;
		bool _filtering;
		bool _aa;
	public:
		Direct3DBase();
		int main(HINSTANCE hinstance);		
		virtual LRESULT CALLBACK handleEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		virtual bool setup(IDirect3DDevice9 * device);
		virtual void update(float timeDelta);
		virtual void draw(IDirect3DDevice9 * device);
		virtual void cleanup(IDirect3DDevice9 * device);
		
		bool initD3D();
		void setBounds(float width, float height);
		void setWindowed(bool windowed);
		void setConsole(bool console);
		void setFiltering(bool filtering);
		void setAA(bool aa);
		void setCameraPos(D3DXVECTOR3 * pos);
		void setCameraLook(D3DXVECTOR3 * look);

		static Direct3DBase * instance();		
};


namespace D3DUtils
{
	D3DMATERIAL9 initMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

	const D3DMATERIAL9 WHITE_MTRL  = initMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL    = initMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL  = initMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL   = initMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = initMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);
};

struct TexelVertex
{
	TexelVertex(){}

	TexelVertex(float x, float y, float z, float u, float v)
	{
		_x = x;	 _y = y;  _z = z;
		_u = u;
		_v = v;
	}

	float _x, _y, _z;
	float _u, _v;

	static const DWORD FVF;
};

struct CustomVertex
{

	CustomVertex(){}

	CustomVertex(float x, float y, float z, float nx, float ny, float nz, D3DCOLOR c)
	{
		_x = x;	 _y = y;  _z = z;
		_normal.x = nx;	_normal.y = ny;	_normal.z = nz;
		_color1 = c;
	}
    float       _x, _y, _z;        // position
    D3DXVECTOR3      _normal;     // normal
    D3DCOLOR       _color1;         // diffuse color

	static const DWORD FVF;
};
//#define D3DFVF_CustomVertex (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE)


struct ColorVertex
{
	ColorVertex(){}

	ColorVertex(float x, float y, float z, D3DCOLOR c)
	{
		_x = x;	 _y = y;  _z = z;  _color = c;
	}

	float _x, _y, _z;
	D3DCOLOR _color;

	static const DWORD FVF;
};


struct Vertex
{
	Vertex(){}

	Vertex(float x, float y, float z)
	{
		_x = x;	 _y = y;  _z = z;		
	}

	float _x, _y, _z;
	static const DWORD FVF;
};

long round(float val);

#endif