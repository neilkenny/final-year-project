#include "Line3D.h"
#include "direct3dbase.h"

Line3D::Line3D() 
{
	_start.x = _start.y = _start.z = 0;
	_end.x = _end.y = _end.z = 0;
	_color = D3DCOLOR_XRGB(0,0,0);
}

void Line3D::setEndPoints(float x0, float y0, float z0, float x1, float y1, float z1, D3DCOLOR * color) 
{
	_start.x = x0;
	_start.y = y0;
	_start.z = z0;

	_end.x = x1;
	_end.y = y1;
	_end.z = z1;

	ColorVertex * vertices;
	_lineVertices->Lock(0, 0, (void**)&vertices, 0);		
	vertices[0] = ColorVertex(_start.x, _start.y, _start.z, * color);
	vertices[1] = ColorVertex(_end.x, _end.y, _end.z, * color);
	_lineVertices->Unlock();
	
}
bool Line3D::setup(IDirect3DDevice9 * device)
{
	_device = device;
	ColorVertex * vertices;
	int retvalue;
	
	retvalue = device->CreateVertexBuffer(
		2 * sizeof(ColorVertex),	// size in bytes
		D3DUSAGE_DYNAMIC,			// flags
		ColorVertex::FVF,			// vertex format
		D3DPOOL_DEFAULT,			// managed memory pool
		&_lineVertices,				// return create vertex buffer
	0);    
	
	if (retvalue != D3D_OK) 
	{
		::MessageBox(0, "CreateVertexBuffer() - FAILED", 0, 0);
		return false;
	}
	_lineVertices->Lock(0, 0, (void**)&vertices, 0);
	
	// The front wall
	vertices[0] = ColorVertex(_start.x, _start.y, _start.z, _color);
	vertices[1] = ColorVertex(_end.x, _end.y, _end.z, _color);
	
	_lineVertices->Unlock();

	return true;
}


void Line3D::draw(IDirect3DDevice9* device)
{
	
	device->SetStreamSource(0, _lineVertices, 0, sizeof(ColorVertex));		
	device->SetFVF(ColorVertex::FVF);

	D3DXMATRIX landscapeScale;
	D3DXMatrixScaling(&landscapeScale, 1,1,1);		
	device->SetTransform(D3DTS_WORLD, &landscapeScale);
	device->SetTexture(0,0);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);	
	// draw the line	
	device->DrawPrimitive(D3DPT_LINELIST, 0, 2);
}