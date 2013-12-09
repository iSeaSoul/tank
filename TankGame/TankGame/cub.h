#ifndef __M_CUB__
#define __M_CUB__

#include <d3dx9.h>
#include "config.h"

#define CUB_D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class CCub
{
public:
	void Move(float x, float y, float z);
	void Yaw(float angle);
	bool CanMove(D3DXMATRIX mMat, float lx, float rx, float lz, float rz);
	
	void SetWorldMat(D3DXMATRIX wMat);
	void GetWorldMat(D3DXMATRIX* wMat);

	void SetPosition(float x, float y, float z);
	void SetSize(float rWidth, float rHeight, float rDepth);
	void SetColor(DWORD col);
	void SetTexture(const char *textureFilePath);

	void Render();
	void UpdateVertices();
	
	CCub(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~CCub();

	float m_pX, m_pY, m_pZ;
	float m_pWidth, m_pHeight, m_pDepth;

private:
	struct VERTEX
	{
		float x, y, z;		
		DWORD color;
		float tu, tv;	
	};

	VERTEX m_pVertice[24];
	D3DXMATRIX m_pWorldMat;
	
	void UpdateVertices(D3DXMATRIX wMat);
	
	HRESULT CreateVertexBuffer();
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
};

#endif
