//--------------------------------------------------------
//    Name: bullet.cpp
//    Description: Create Bullet with move speed
//--------------------------------------------------------

#include "bullet.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 birthPosition, D3DXVECTOR3 speedVector)
{
	b_Cub = new CCub(pD3DDevice);
	b_Cub->SetPosition(birthPosition.x, birthPosition.y, birthPosition.z);
	b_Cub->SetColor(D3DCOLOR_XRGB(223, 180, 49));
	b_pX = birthPosition.x; 
	b_pY = birthPosition.y; 
	b_pZ = birthPosition.z; 

	b_speedVec = speedVector * BULLET_SPEED;
	b_STime = timeGetTime();
}

CBullet::~CBullet()
{
	SafeDelete(b_Cub);
}

//-----------------------------------------------------------
// Name: CheckOutOfFloor()
// Desc: Check if bullet already out of floor
//-----------------------------------------------------------
bool CBullet::CheckOutOfFloor()
{
	DWORD cur_Time = timeGetTime();
	DWORD duration = (cur_Time - b_STime);

	if (b_pX + duration * b_speedVec.x < -FLOOR_WIDTH || b_pX + duration * b_speedVec.x > FLOOR_WIDTH)
	{
		return false;
	}
	if (b_pZ + duration * b_speedVec.z < -FLOOR_DEPTH || b_pZ + duration * b_speedVec.z > FLOOR_DEPTH)
	{
		return false;
	}
	return true;
}

//-----------------------------------------------------------
// Name: CheckCollide(CEnemy* enemy)
// Desc: Check if bullet collide with enemy
//-----------------------------------------------------------
bool CBullet::CheckCollide(CEnemy* enemy)
{
	DWORD cur_Time = timeGetTime();
	DWORD duration = (cur_Time - b_STime);
	
	CCub* enemyCub = enemy->GetEnemyCub();
	float lxDis = enemyCub->m_pX - enemyCub->m_pWidth;
	float rxDis = enemyCub->m_pX + enemyCub->m_pWidth;
	float lzDis = enemyCub->m_pZ - enemyCub->m_pDepth;
	float rzDis = enemyCub->m_pZ + enemyCub->m_pDepth;

	float lx_timeStamp = (lxDis - b_pX) / b_speedVec.x;
	float rx_timeStamp = (rxDis - b_pX) / b_speedVec.x;
	float lz_timeStamp = (lzDis - b_pZ) / b_speedVec.z;
	float rz_timeStamp = (rzDis - b_pZ) / b_speedVec.z;

	if (lx_timeStamp > rx_timeStamp)
	{
		float t = lx_timeStamp;
		lx_timeStamp = rx_timeStamp;
		rx_timeStamp = t;
	}
	if (lz_timeStamp > rz_timeStamp)
	{
		float t = lz_timeStamp;
		lz_timeStamp = rz_timeStamp;
		rz_timeStamp = t;
	}

	float l_timeRange = lx_timeStamp > lz_timeStamp? lx_timeStamp : lz_timeStamp;
	float r_timeRange = rx_timeStamp < rz_timeStamp? rx_timeStamp : rz_timeStamp;

	return duration >= l_timeRange && duration <= r_timeRange;
}

void CBullet::GetCurrentPlace()
{
	DWORD cur_Time = timeGetTime();
	DWORD duration = (cur_Time - b_STime);

	b_Cub->SetPosition(b_pX + duration * b_speedVec.x, 
		b_pY + duration * b_speedVec.y, b_pZ + duration * b_speedVec.z);
}

void CBullet::Render()
{
	b_Cub->Render();
}