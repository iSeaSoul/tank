//-----------------------------------------------------------------------
//    Name: Tank.cpp
//    Description: Create and handle Tank Object can move and shoot
//-----------------------------------------------------------------------

#include "tank.h"

CTank::CTank(LPDIRECT3DDEVICE9 pD3DDevice, CPlatform* platform)
{
	m_pD3DDevice = pD3DDevice;
	m_platform = platform;
	tank = new CCub(pD3DDevice);
	barrel = new CCub(pD3DDevice);
	
	// Set up tank position, size and world matrix
	tank->SetSize(TANK_WIDTH, TANK_HEIGHT, TANK_DEPTH);
	tank->SetColor(D3DCOLOR_COLORVALUE(1, 1, 1, 0));
	tank->SetPosition(0, TANK_HEIGHT, 0);
	tank->SetTexture(TANK_TEXTURE);

	barrel->SetSize(BARREL_WIDTH, BARREL_HEIGHT, BARREL_DEPTH);
	barrel->SetColor(D3DCOLOR_COLORVALUE(1, 1, 1, 0));
	barrel->SetPosition(BARREL_WIDTH, TANK_HEIGHT * 2, BARREL_DEPTH + BARREL_DEPTH);
	barrel->SetTexture(TANK_TEXTURE);

	D3DXMATRIX tank_RelWorldMatrix;
	m_platform->GetPWorldMat(&tank_RelWorldMatrix);
	tank->SetWorldMat(tank_RelWorldMatrix);
	barrel->SetWorldMat(tank_RelWorldMatrix);
	
	// Set up origianl camera and lookat
	camera = D3DXVECTOR3(CAMERA_WIDTH, CAMERA_HEIGHT, CAMERA_DEPTH);
	lookat = D3DXVECTOR3(0, TANK_HEIGHT, 0);
	bulletPos = D3DXVECTOR3(0, TANK_HEIGHT * 2, TANK_DEPTH + BARREL_DEPTH * 2);
	cubOrient = D3DXVECTOR3(0, 0, 1.0f);
}

CTank::~CTank()
{
	SafeDelete(tank);
}

void CTank::GetCameraVec(D3DXVECTOR3* relCamera)
{
	D3DXMATRIX tank_RelWorldMatrix;
	m_platform->GetPWorldMat(&tank_RelWorldMatrix);
	D3DXVec3TransformCoord(relCamera, &camera, &tank_RelWorldMatrix);
}

void CTank::GetLookatVec(D3DXVECTOR3* relLookat)
{
	D3DXMATRIX tank_RelWorldMatrix;
	m_platform->GetPWorldMat(&tank_RelWorldMatrix);
	D3DXVec3TransformCoord(relLookat, &lookat, &tank_RelWorldMatrix);
}

void CTank::UpdateWorldMat()
{
	D3DXMATRIX tank_RelWorldMatrix;
	m_platform->GetPWorldMat(&tank_RelWorldMatrix);
	tank->SetWorldMat(tank_RelWorldMatrix);
	barrel->SetWorldMat(tank_RelWorldMatrix);
	tank->UpdateVertices();
}

bool CTank::CanMove(float step_Width, float step_Height, float step_Depth)
{
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, step_Width, step_Height, step_Depth);
	return tank->CanMove(mat, -PLATFORM_WIDTH, PLATFORM_WIDTH, -PLATFORM_DEPTH, PLATFORM_DEPTH);
}

void CTank::Move(float step_Width, float step_Height, float step_Depth)
{
	float tmp_step_Width = step_Width;
	step_Width = step_Width * cubOrient.z + step_Depth * cubOrient.x;
	step_Depth = step_Depth * cubOrient.z - tmp_step_Width * cubOrient.x;

	if (CanMove(step_Width, step_Height, step_Depth))
	{
		tank->Move(step_Width, step_Height, step_Depth);
		barrel->Move(step_Width, step_Height, step_Depth);
		camera += D3DXVECTOR3(step_Width, step_Height, step_Depth);
		lookat += D3DXVECTOR3(step_Width, step_Height, step_Depth);
		bulletPos += D3DXVECTOR3(step_Width, step_Height, step_Depth);
	}
}

void CTank::Rotate(float angle)
{
	tank->Yaw(angle);
	barrel->Yaw(angle);
	
	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, angle);
	D3DXVec3TransformCoord(&camera, &camera, &mat);
	D3DXVec3TransformCoord(&lookat, &lookat, &mat);
	D3DXVec3TransformCoord(&bulletPos, &bulletPos, &mat);
	D3DXVec3TransformNormal(&cubOrient, &cubOrient, &mat);
}

void CTank::Render()
{
	tank->Render();
	barrel->Render();
}

CBullet* CTank::Shoot()
{
	D3DXVECTOR3 relBirthPlace;
	D3DXVECTOR3 relSpeedVector;
	D3DXMATRIX tank_RelWorldMatrix;
	m_platform->GetPWorldMat(&tank_RelWorldMatrix);
	D3DXVec3TransformCoord(&relBirthPlace, &bulletPos, &tank_RelWorldMatrix);
	D3DXVec3TransformNormal(&relSpeedVector, &cubOrient, &tank_RelWorldMatrix);

	CBullet* nBullet = NULL;
	nBullet = new CBullet(m_pD3DDevice, relBirthPlace, relSpeedVector);
	return nBullet;
}