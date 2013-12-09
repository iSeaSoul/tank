#ifndef __M_PLATFORM__
#define __M_PLATFORM__

#include <d3dx9.h>
#include "cub.h"
#include "config.h"

class CPlatform
{
public:
	void Render();
	void Rotate();
	void GetPWorldMat(D3DXMATRIX* wMat);

	CPlatform(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~CPlatform();

private:
	CCub* mainCub;
	D3DXMATRIX pWorldMat;
};

#endif