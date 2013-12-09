//--------------------------------------------------------
//    Name: Platform.cpp
//    Description: The rotate platform
//--------------------------------------------------------

#include "platform.h"

CPlatform::CPlatform(LPDIRECT3DDEVICE9 pD3DDevice)
{
	mainCub = new CCub(pD3DDevice);
	mainCub->SetSize(PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_DEPTH);
	mainCub->SetPosition(0, PLATFORM_HEIGHT, 0);

	D3DXMatrixTranslation(&pWorldMat, 0, PLATFORM_HEIGHT * 2, 0);
}

CPlatform::~CPlatform()
{
	SafeDelete(mainCub);
}

void CPlatform::Render()
{
	mainCub->Render();
}

void CPlatform::Rotate()
{
	D3DXMATRIX matCur;
	D3DXMatrixRotationY(&matCur, D3DX_PI/PLATFORM_ROTATE_ANGLE_UNIT);
	D3DXMatrixMultiply(&pWorldMat, &pWorldMat, &matCur);

	mainCub->Yaw(D3DX_PI/PLATFORM_ROTATE_ANGLE_UNIT);
}

void CPlatform::GetPWorldMat(D3DXMATRIX* wMat)
{
	*wMat = pWorldMat;
}
