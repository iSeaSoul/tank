#include "gameloader.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

GameLoader* g_pGame = NULL;

void CleanUp()
{
	SafeDelete(g_pGame);
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINT ptLastMousePosit;
	static POINT ptCurrentMousePosit;
	static bool bMousing;

    switch(msg)
	{
        case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
			}
		}
        break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
		
        case WM_DESTROY:
		{
            PostQuitMessage(0);
		}
        break;

		default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
    WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, WinProc, 0L, 0L, 
                     GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                     "Tank Game", NULL};
	
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);	
	
	RegisterClassEx(&wc);

    HWND hWnd = CreateWindow("Tank Game", "Tank Game", 
                              WS_OVERLAPPEDWINDOW, 0, 0, 640, 480,
                              NULL, NULL, wc.hInstance, NULL);

	g_pGame = new GameLoader();

	if(g_pGame->Initialise(hWnd))
    { 
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);

        g_pGame->GameLoop();        
    }
    
    CleanUp();
    UnregisterClass("Tank Game", wc.hInstance);
    
    return 0;
}
