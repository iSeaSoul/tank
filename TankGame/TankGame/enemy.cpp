//--------------------------------------------------------
//    Name: enemy.cpp
//    Description: Create Enemy Object
//--------------------------------------------------------

#include "enemy.h"

CEnemy::CEnemy(LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 birthPosition, D3DXVECTOR3 enemySize)
{
	e_Cub = new CCub(pD3DDevice);
	e_Cub->SetSize(enemySize.x, enemySize.y, enemySize.z);
	e_Cub->SetPosition(birthPosition.x, birthPosition.y, birthPosition.z);
	//e_Cub->SetColor(D3DCOLOR_XRGB(52, 3, 73));
	e_Cub->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	e_Cub->SetTexture(ENEMY_TEXTURE);
}

CEnemy::~CEnemy()
{
	SafeDelete(e_Cub);
}

CCub* CEnemy::GetEnemyCub()
{
	return e_Cub;
}

void CEnemy::Render()
{
	e_Cub->Render();
}