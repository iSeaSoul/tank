#ifndef __M_ENEMY__
#define __M_ENEMY__

#include <d3dx9.h>
#include "cub.h"
#include "config.h"

class CEnemy
{
public:
	CEnemy(LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 birthPosition, D3DXVECTOR3 enemySize);
	virtual ~CEnemy();
	void Render();
	CCub* GetEnemyCub();

private:
	CCub* e_Cub;
};

#endif