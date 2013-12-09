//--------------------------------------------------------
//    Name: gameloader.cpp
//    Description: The main game Loader
//--------------------------------------------------------

#include "gameloader.h"

GameLoader::GameLoader()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;

	floor = NULL;
	platform = NULL;
	tank = NULL;
	m_pFont = NULL;
	bulletList.clear();
	enemyList.clear();
}

GameLoader::~GameLoader()
{
	SafeRelease(m_pD3DDevice);
	SafeRelease(m_pD3D);

	SafeDelete(floor);
	SafeDelete(platform);
	SafeDelete(tank);
	bulletList.clear();
	enemyList.clear();
}

bool GameLoader::Initialise(HWND hWnd)
{
	if(!SUCCEEDED(InitialiseD3D(hWnd)))
	{
		return false;
	}

	InitialiseGame();
	return true;
}

void GameLoader::InitialiseGame()
{
	floor = new CCub(m_pD3DDevice);
	floor->SetSize(FLOOR_WIDTH, FLOOR_HEIGHT, FLOOR_DEPTH);
	floor->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	floor->SetTexture(FLOOR_TEXTURE);

	platform = new CPlatform(m_pD3DDevice);
	tank = new CTank(m_pD3DDevice, platform);
}

HRESULT GameLoader::InitialiseD3D(HWND hWnd)
{
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(m_pD3D == NULL)
    {
        return E_FAIL;
    }
	
    D3DDISPLAYMODE d3ddm;
    if( FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

    if(m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D32) == D3D_OK)
	{
        d3dpp.AutoDepthStencilFormat = D3DFMT_D32;
        d3dpp.EnableAutoDepthStencil = TRUE;
    }
    else if(m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8) == D3D_OK)
    {
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
        d3dpp.EnableAutoDepthStencil = TRUE;
	}
    else if(m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16) == D3D_OK)
    {
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
        d3dpp.EnableAutoDepthStencil = TRUE;
	}
    else
	{
        d3dpp.EnableAutoDepthStencil = FALSE;
	}

    if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
    {
        return E_FAIL;
    }
    
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	
	SetupPerspective();
	SetupFont();

    return S_OK;
}

//-----------------------------------------------------------
// Name: GameLoop()
// Desc: The main game loop Handler
//-----------------------------------------------------------
void GameLoader::GameLoop()
{
    MSG msg;
    PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			InputHandler(msg);
            Render();
        }
    }
}

//-----------------------------------------------------------
// Name: InputHandler()
// Desc: The input message handler
//-----------------------------------------------------------
void GameLoader::InputHandler(MSG msg)
{
	static POINT ptLastMousePosit;
	static POINT ptCurrentMousePosit;
	static bool bMousing;
	
	if (msg.message == WM_LBUTTONDOWN)
	{
		ptLastMousePosit.x = ptCurrentMousePosit.x = LOWORD (msg.lParam);
		ptLastMousePosit.y = ptCurrentMousePosit.y = HIWORD (msg.lParam);
		bMousing = true;
	}

	if (msg.message == WM_LBUTTONUP)
	{
		bMousing = false;
	}

	if (msg.message == WM_MOUSEMOVE)
	{
		ptCurrentMousePosit.x = LOWORD (msg.lParam);
		ptCurrentMousePosit.y = HIWORD (msg.lParam);

		if( bMousing )
		{
			tank->Rotate(D3DXToRadian((ptCurrentMousePosit.x - ptLastMousePosit.x)));
		}

		ptLastMousePosit.x = ptCurrentMousePosit.x;
		ptLastMousePosit.y = ptCurrentMousePosit.y;
	}

	// Tank Move
	if ((::GetAsyncKeyState('W') & 0x8000f) || (::GetAsyncKeyState(VK_UP) & 0x8000f))
	{
		tank->Move(0, 0, TANK_STEP_UNIT);
	}
	if ((::GetAsyncKeyState('S') & 0x8000f) || (::GetAsyncKeyState(VK_DOWN) & 0x8000f))
	{
		tank->Move(0, 0, -TANK_STEP_UNIT);
	}
	if ((::GetAsyncKeyState('A') & 0x8000f) || (::GetAsyncKeyState(VK_LEFT) & 0x8000f))
	{
		tank->Move(-TANK_STEP_UNIT, 0, 0);
	}
	if ((::GetAsyncKeyState('D') & 0x8000f) || (::GetAsyncKeyState(VK_RIGHT) & 0x8000f))
	{
		tank->Move(TANK_STEP_UNIT, 0, 0);
	}
	// Tank Shoot
	if (::GetAsyncKeyState('F'))
	{
		if (CheckPresskeyGapTime())
		{
			bulletList.push_back(tank->Shoot());
		}
	}
	// Create random enemy
	if (::GetAsyncKeyState(VK_SPACE))
	{
		if (CheckPresskeyGapTime())
		{
			enemyList.push_back(RandomEnemy());
		}
	}
	// Platform rotate
	if (PLATFORM_ROTATE_MODE)
	{
		platform->Rotate();
		tank->UpdateWorldMat();
	}
}

void GameLoader::Render()
{
	static int currentHit = 0;
    if(m_pD3DDevice == NULL)
    {
        return;
    }

    m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    m_pD3DDevice->BeginScene();

	SetupCamera();
	CheckBulletCollide(currentHit);

	floor->Render();
	platform->Render();
	tank->Render();

	char textString[32];
	sprintf (textString, "Score = %d", currentHit);

	RECT rect = {0, 0, 640, 480};
	m_pFont->DrawTextA(
			NULL,
			textString, 
			-1, 
			&rect,            
			DT_TOP | DT_LEFT, 
			0xffffffff);      

	for (std::list<CBullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		(*it)->Render();
	}
	for (std::list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		(*it)->Render();
	}

    m_pD3DDevice->EndScene();
    m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

bool GameLoader::CheckPresskeyGapTime()
{
	static DWORD prePressKeyTime = -1;
	DWORD curPreesKeyTime = timeGetTime();
	DWORD duration = (curPreesKeyTime - prePressKeyTime);
	if (duration >= GAP_TIME)
	{
		prePressKeyTime = curPreesKeyTime;
		return true;
	}
	return false;
}

void GameLoader::SetupFont()
{
	D3DXFONT_DESC df;
	ZeroMemory(&df, sizeof(D3DXFONT_DESC));

	df.Height			= 24;    // in logical units
	df.Width			= 10;    // in logical units
	df.Weight			= 300;   // boldness, range 0(light) - 1000(bold)
	df.MipLevels		= D3DX_DEFAULT;
	df.Italic			= false;     
	df.CharSet			= DEFAULT_CHARSET;
	df.OutputPrecision  = 0;          
	df.Quality			= 0;           
	df.PitchAndFamily	= 0;           
	strcpy(df.FaceName, "Times New Roman"); // font style

	D3DXCreateFontIndirect(m_pD3DDevice, &df, &m_pFont);
}

void GameLoader::SetupPerspective()
{
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 1.0f, 500.0f);
    m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void GameLoader::SetupCamera()
{
    D3DXMATRIX matView;
	D3DXVECTOR3 cameraPos;
	D3DXVECTOR3 lookatPos;
	tank->GetCameraVec(&cameraPos);
	tank->GetLookatVec(&lookatPos);
	if (FIXED_VIEW)
	{
		cameraPos = D3DXVECTOR3(120, 150, -100);
		lookatPos = D3DXVECTOR3(0, 0, -10);
	}
    D3DXMatrixLookAtLH(&matView, &cameraPos, &lookatPos, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void GameLoader::CheckBulletCollide(static int& collideCnt)
{
	std::list<CBullet*> tmpBulletList(0);
	for (std::list<CBullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		(*it)->GetCurrentPlace();
		if ((*it)->CheckOutOfFloor())
		{
			tmpBulletList.push_back(*it);
		}
	}
	bulletList.clear();
	for (std::list<CBullet*>::iterator it = tmpBulletList.begin(); it != tmpBulletList.end(); ++it)
	{
		bool collided = false;
		for (std::list<CEnemy*>::iterator jt = enemyList.begin(); jt != enemyList.end(); ++jt)
		{
			if ((*it)->CheckCollide(*jt))
			{
				collided = true;
				enemyList.erase(jt);
				++collideCnt;
				break;
			}
		}
		if (!collided)
		{
			bulletList.push_back(*it);
		}
	}
}

CEnemy* GameLoader::RandomEnemy()
{
	srand(time(NULL));
	D3DXVECTOR3 enemySize = D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE)
		* (rand() % 10 + 10) / 10.0;
	int posx = rand() % ENEMY_RANGE, posz = rand() % ENEMY_RANGE;
	while (posx < PLATFORM_WIDTH * 1.5 && posz < PLATFORM_DEPTH * 1.5)
	{	
		posx = rand() % ENEMY_RANGE, posz = rand() % ENEMY_RANGE;
	}
	posx *= (rand() % 2 == 0? 1 : -1);
	posz *= (rand() % 2 == 0? 1 : -1);

	D3DXVECTOR3 birthPosition = D3DXVECTOR3(posx, rand() % 20 + 
		(PLATFORM_HEIGHT + ENEMY_SIZE)* 2, posz);
	CEnemy* newEnemy = new CEnemy(m_pD3DDevice, birthPosition, enemySize);
	return newEnemy;
}