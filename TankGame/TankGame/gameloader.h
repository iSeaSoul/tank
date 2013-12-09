#ifndef __M_GAME__
#define __M_GAME__

#include <d3dx9.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <list>

#include "bullet.h"
#include "config.h"
#include "cub.h"
#include "enemy.h"
#include "platform.h"
#include "tank.h"

class GameLoader
{
public:
	GameLoader();
	virtual ~GameLoader();

	bool Initialise(HWND hWnd);
	void GameLoop();

private:
	HRESULT InitialiseD3D(HWND hWnd);

	void InitialiseGame();
	void InputHandler(MSG msg);
	void Render();

	void SetupFont();
	void SetupCamera();
	void SetupPerspective();

	void CheckBulletCollide(static int& collideCnt);
	bool CheckPresskeyGapTime();

	CEnemy* RandomEnemy();

	CCub* floor;
	CPlatform* platform;
	CTank* tank;
	std::list<CBullet*> bulletList;
	std::list<CEnemy*> enemyList;
	
	LPDIRECT3D9 m_pD3D;
	ID3DXFont* m_pFont;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif