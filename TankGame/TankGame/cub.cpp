//--------------------------------------------------------
//    Name: cub.cpp
//    Description: Create Basic Cub Object
//--------------------------------------------------------

#include "cub.h"

CCub::CCub(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;

	VERTEX c_vertice[] = 
	{
		// Quad 0
		{-1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ), 0.0f, 0.0f }, // 0
		{ 1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ), 1.0f, 0.0f }, // 1
		{-1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 1.0, 1.0 ), 0.0f, 1.0f }, // 2
		{ 1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ), 1.0f, 1.0f }, // 3

		// Quad 1
		{-1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ), 1.0f, 0.0f }, // 4
		{-1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ), 1.0f, 1.0f }, // 5
		{ 1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 1.0, 1.0 ), 0.0f, 0.0f }, // 6
		{ 1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ), 0.0f, 1.0f }, // 7

		// Quad 2
		{-1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ), 0.0f, 0.0f }, // 4
		{ 1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 1.0, 1.0 ), 1.0f, 0.0f }, // 6
		{-1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ), 0.0f, 1.0f }, // 0
		{ 1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ), 1.0f, 1.0f }, // 1

		// Quad 3
		{-1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ), 0.0f, 0.0f }, // 5
		{-1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 1.0, 1.0 ), 1.0f, 0.0f }, // 2
		{ 1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ), 0.0f, 1.0f }, // 7
		{ 1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ), 1.0f, 1.0f }, // 3

		// Quad 4
		{ 1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ), 0.0f, 0.0f }, // 1
		{ 1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 1.0, 1.0 ), 1.0f, 0.0f }, // 6
		{ 1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ), 0.0f, 1.0f }, // 3
		{ 1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ), 1.0f, 1.0f }, // 7

		// Quad 5
		{-1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ), 1.0f, 0.0f }, // 0
		{-1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 0.0, 1.0, 1.0 ), 1.0f, 1.0f }, // 2
		{-1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ), 0.0f, 0.0f }, // 4
		{-1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ), 0.0f, 1.0f }  // 5
	};

	memcpy (m_pVertice, c_vertice, sizeof(c_vertice));
	m_pX = m_pY = m_pZ = 0.0f;
	m_pWidth = m_pHeight = m_pDepth = 1.0f;

    if(SUCCEEDED(CreateVertexBuffer()))
	{
		D3DXMatrixIdentity(&m_pWorldMat);
		UpdateVertices();
	}
}

CCub::~CCub()
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pTexture);
}

HRESULT CCub::CreateVertexBuffer()
{
    if(FAILED(m_pD3DDevice->CreateVertexBuffer(24 * sizeof(VERTEX), D3DUSAGE_WRITEONLY, CUB_D3DFVF_CUSTOMVERTEX,
                                               D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
    {
        return E_FAIL;
    }

    return S_OK;
}

void CCub::Render()
{
    m_pD3DDevice->SetTexture(0, m_pTexture);
	m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX));
    m_pD3DDevice->SetFVF(CUB_D3DFVF_CUSTOMVERTEX);

	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  0, 2 );
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  4, 2 );
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  8, 2 );
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 12, 2 );
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 16, 2 );
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 20, 2 );

    m_pD3DDevice->SetTexture(0, NULL);
}

void CCub::UpdateVertices()
{
	VOID* pVertices;
	VERTEX c_pVertice[24];
	memcpy (c_pVertice, m_pVertice, sizeof(m_pVertice));
	for (int i = 0; i < 24; ++i) 
	{
		D3DXVECTOR3 rel;
		D3DXVECTOR3 tmp = D3DXVECTOR3(m_pVertice[i].x, m_pVertice[i].y, m_pVertice[i].z);
		D3DXVec3TransformCoord(&rel, &tmp, &m_pWorldMat);
		c_pVertice[i].x = rel.x;
		c_pVertice[i].y = rel.y;
		c_pVertice[i].z = rel.z;
	}

    m_pVertexBuffer->Lock(0, sizeof(c_pVertice), &pVertices, 0);
    memcpy(pVertices, c_pVertice, sizeof(c_pVertice));
    m_pVertexBuffer->Unlock();
}

void CCub::UpdateVertices(D3DXMATRIX wMat)
{
	for (int i = 0; i < 24; ++i) 
	{
		D3DXVECTOR3 rel;
		D3DXVECTOR3 tmp = D3DXVECTOR3(m_pVertice[i].x, m_pVertice[i].y, m_pVertice[i].z);
		D3DXVec3TransformCoord(&rel, &tmp, &wMat);
		m_pVertice[i].x = rel.x;
		m_pVertice[i].y = rel.y;
		m_pVertice[i].z = rel.z;
	}
	UpdateVertices();
}

void CCub::SetTexture(const char *textureFilePath)
{
	D3DXCreateTextureFromFile(m_pD3DDevice, textureFilePath, &m_pTexture);
}

void CCub::SetWorldMat(D3DXMATRIX wMat)
{
	m_pWorldMat = wMat;
	UpdateVertices();
}

void CCub::GetWorldMat(D3DXMATRIX* wMat)
{
	*wMat = m_pWorldMat;
}

void CCub::SetPosition(float x, float y, float z)
{
	Move(x - m_pX, y - m_pY, z - m_pZ);
}

void CCub::SetSize(float rWidth, float rHeight, float rDepth)
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mat(0, 0) = rWidth / m_pWidth;
	mat(1, 1) = rHeight / m_pHeight;
	mat(2, 2) = rDepth / m_pDepth;

	m_pWidth = rWidth;
	m_pHeight = rHeight;
	m_pDepth = rDepth;

	UpdateVertices(mat);
}

void CCub::SetColor(DWORD col)
{
	for (int i = 0; i < 24; ++i)
	{
		m_pVertice[i].color = col;
	}
	
	UpdateVertices();
}

void CCub::Move(float x, float y, float z)
{
	m_pX += x; m_pY += y; m_pZ += z;
	
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, x, y, z);

	UpdateVertices(mat);
}

bool CCub::CanMove(D3DXMATRIX mMat, float lx, float rx, float lz, float rz)
{
	for (int i = 0; i < 8; ++i) 
	{
		D3DXVECTOR3 rel;
		D3DXVECTOR3 tmp = D3DXVECTOR3(m_pVertice[i].x, m_pVertice[i].y, m_pVertice[i].z);
		D3DXVec3TransformCoord(&rel, &tmp, &mMat);
		if (rel.x < lx || rel.x > rx || rel.z < lz || rel.z > rz)
		{
			return false;
		}
	}
	return true;
}

void CCub::Yaw(float angle)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, angle);
	
	UpdateVertices(mat);
}