#ifndef __3DLineH__
#define __3DLineH__

#include <d3dx9.h>
#include "drawableentity.h"

class Line3D:public DrawableEntity
{
private:
	IDirect3DVertexBuffer9 * _lineVertices;	
	IDirect3DDevice9 * _device;
	D3DCOLOR _color;
	D3DXVECTOR3 _start;
	D3DXVECTOR3 _end;
	
public:
	Line3D();
	void setEndPoints(float x0, float y0, float z0, float x1, float y1, float z1, D3DCOLOR * color);
	bool setup(IDirect3DDevice9* Device);
	void draw(IDirect3DDevice9* Device);
	void update(float timeDelta) {}; // No implementation
};
#endif
