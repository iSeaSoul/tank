#ifndef __M_BULLET__
#define __M_BULLET__

#include <d3dx9.h>
#include <Mmsystem.h>
#include "cub.h"
#include "config.h"
#include "enemy.h"

class CBullet
{
public:
	CBullet(LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 birthPosition, D3DXVECTOR3 speedVector);
	virtual ~CBullet();

	void GetCurrentPlace();
	void Render();
	bool CheckOutOfFloor();
	bool CheckCollide(CEnemy* enemy);

private:
	CCub* b_Cub;
	D3DXVECTOR3 b_speedVec;
	DWORD b_STime;
	float b_pX, b_pY, b_pZ;
};

#endif