#ifndef __M_TANK__
#define __M_TANK__

#include <d3dx9.h>
#include "cub.h"
#include "platform.h"
#include "bullet.h"

class CTank
{
public:
	CTank(LPDIRECT3DDEVICE9 pD3DDevice, CPlatform* platform);
	virtual ~CTank();

	bool CanMove(float step_Width, float step_Height, float step_Depth);
	void Move(float step_Width, float step_Height, float step_Depth);
	void Rotate(float angle);
	void Render();
	CBullet* Shoot();

	void GetCameraVec(D3DXVECTOR3* relCamera);
	void GetLookatVec(D3DXVECTOR3* relLookat);
	void UpdateWorldMat();

private:
	CCub* tank;
	CCub* barrel;
	CPlatform* m_platform;

	D3DXVECTOR3 camera;
	D3DXVECTOR3 lookat;
	D3DXVECTOR3 bulletPos;
	D3DXVECTOR3 cubOrient;
	D3DXMATRIX	tWorldMat;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif
