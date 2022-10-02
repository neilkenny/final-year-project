#include <windowsx.h>
#include <stdio.h>
#include <d3dx9.h>
#include "io.h"
#include "assert.h"
#include "Direct3DBase.h"


Direct3DBase * Direct3DBase::_instance = NULL;

const DWORD TexelVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;
const DWORD Vertex::FVF = D3DFVF_XYZ;
const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
const DWORD CustomVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

long round(float x) 
{
      assert(x >= LONG_MIN-0.5);
      assert(x <= LONG_MAX+0.5);
      if (x >= 0)
         return (long) (x+0.5);
      return (long) (x-0.5);
}

Direct3DBase::Direct3DBase()
{
	// Set initial parameters
	_device = NULL;
	_instance = this;

	_width = 800;
	_height = 600;
	_windowed = true;
	_console = true;
	_filtering = false;
	_aa = false;

	_camPos = D3DXVECTOR3(-50.0f, 5.0f, -50.0f);
	_camLook = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
}

int Direct3DBase::main(HINSTANCE hInstance)
{
	MSG msg;
	
	::ZeroMemory(&msg, sizeof(MSG));

	_hInstance = hInstance;

	// Initialise the window and direct3D
	if (!initD3D())
	{
		MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return -1;
	}
		
	// Setup the camera, lighting etc.
	if(!setup(_device))
	{
		MessageBox(0, "Setup() - FAILED", 0, 0);
		return -1;
	}
	static float lastTime = (float)timeGetTime(); 

	// Enter the message loop
	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
        {	
		float currTime  = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;

			// Update the geometry
			update(timeDelta);

			// Redraw the scene
			_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			_device->BeginScene();

			draw(_device);

			_device->EndScene();
			_device->Present(0, 0, 0, 0);

			lastTime = currTime;
        }
	}

	// Cleanup any resources
	cleanup(_device);	
	return 0;
}

LRESULT CALLBACK Direct3DBase::handleEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return Direct3DBase::instance()->handleEvent(hwnd, msg, wParam, lParam);
}

bool Direct3DBase::initD3D()
{
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = _hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Direct3D9App";

	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	HWND hwnd = 0;
	hwnd = ::CreateWindow("Direct3D9App", "Direct3D9App", 
		WS_EX_TOPMOST,
		0, 0, _width, _height,
		0 /*parent hwnd*/, 0 /* menu */, _hInstance, 0 /*extra*/); 

	if( !hwnd )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	HRESULT hr = 0;

	// Step 1: Create the IDirect3D9 object.
	IDirect3D9 * d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if( !d3d9 )
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: Check for hardware vp.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = _width;
	d3dpp.BackBufferHeight           = _height;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = hwnd;
	d3dpp.Windowed                   = _windowed;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 4: Create the _device.
	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		D3DDEVTYPE_HAL,         // _device type
		hwnd,               // window associated with _device
		vp,                 // vertex processing
	    &d3dpp,             // present parameters
	    & _device);            // return created _device

	if( FAILED(hr) )
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hwnd,
			vp,
			& d3dpp,
			& _device);

		if( FAILED(hr) )
		{
			d3d9->Release(); // done with d3d9 object
			::MessageBox(0, "Create_device() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release(); // done with d3d9 object
	
	return true;
}

bool Direct3DBase::setup(IDirect3DDevice9 * device)
{
	// Set up a console for debugging		
	if (_console) 
	{
		AllocConsole();
		int fd = _open_osfhandle( (long)GetStdHandle( STD_OUTPUT_HANDLE ), 0); 
		FILE * fp = _fdopen( fd, "w" ); 
		*stdout = *fp; 
		setvbuf( stdout, NULL, _IONBF, 0 );
	}

	// Position and aim the camera.
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
    D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &_camPos, &_camLook, &up);
	_device->SetTransform(D3DTS_VIEW, &V);
		
	// Set the projection matrix.
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.5f, // 90 - degree
			(float)_width / (float)_height,
			1.0f,
			1000.0f);
	_device->SetTransform(D3DTS_PROJECTION, &proj);
	
	// Configure rendering
	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	_device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	_device->SetRenderState(D3DRS_NORMALIZENORMALS, false);
	_device->SetRenderState(D3DRS_LIGHTING, false);

	if (_filtering)
	{
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		_device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 4);
	}
	
	// Set up a light source
	D3DLIGHT9 dir;
	::ZeroMemory(&dir, sizeof(dir));
	dir.Type      = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse   = D3DUtils::WHITE;
	dir.Specular  = D3DUtils::WHITE * 0.3f;
	dir.Ambient   = D3DUtils::WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	
	_device->SetLight(0, &dir);
	_device->LightEnable(0, true);

	// Turn off the cursor
	SetCursorPos(_width / 2, _height / 2);	
	_device->ShowCursor(false);
	return true;
}


Direct3DBase * Direct3DBase::instance()
{
	return Direct3DBase::_instance;
}

void Direct3DBase::update(float timeDelta)
{
}

void Direct3DBase::draw(IDirect3DDevice9 * device)
{
	
}

void Direct3DBase::cleanup(IDirect3DDevice9 * device)
{
	device->Release();
}



D3DMATERIAL9 D3DUtils::initMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}

void Direct3DBase::setBounds(float width, float height)
{
	_width = width;
	_height = height;
}

void Direct3DBase::setWindowed(bool windowed)
{
	_windowed = windowed;
}

void Direct3DBase::setConsole(bool console)
{
	_console = console;
}

void Direct3DBase::setFiltering(bool filtering)
{
	_filtering = filtering;
}

void Direct3DBase::setAA(bool aa)
{
	_aa = aa;
}


void Direct3DBase::setCameraPos(D3DXVECTOR3 * pos)
{
	_camPos = * pos;
}

void Direct3DBase::setCameraLook(D3DXVECTOR3 * look)
{
	_camLook = * look;
}