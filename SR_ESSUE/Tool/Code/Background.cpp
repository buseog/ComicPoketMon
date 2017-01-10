#include "StdAfx.h"
#include "Background.h"
#include "RcTerrain.h"
#include "Resources.h"
#include "VIBuffer.h"
#include "Include.h"

CBackground::CBackground( LPDIRECT3DDEVICE9 pDevice )
: CGameObject(pDevice)
, m_pBuffer(NULL)
, m_fDistance(0)
{

}

CBackground::~CBackground( void )
{
	Release();
}


void CBackground::Release( void )
{
	
}

void CBackground::KeyCheck( void )
{
	if(GetAsyncKeyState('W') & 0x8000)
	{
		m_fDistance -= 1.f;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}

	if(GetAsyncKeyState('S') & 0x8000)
	{
		m_fDistance += 1.f;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}

	//if(GetAsyncKeyState('A') & 0x8000)
	//{
	//	m_vAt.x -= 5;
	//}

	//if(GetAsyncKeyState('D') & 0x8000)
	//{
	//	m_vAt.x += 5;
	//}

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(-5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;

	}

	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(-5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;
	}

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &D3DXVECTOR3(0.f,1.f,0.f));
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

}

void CBackground::Picking( void )
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXMATRIX matRView, matRProj;

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);


	Engine::VTXCOL*	pVertex = new Engine::VTXCOL[20 * 20];
	((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(pVertex);

	float	fU, fV, fDist;
	int VTXCNTZ = 20;
	int VTXCNTX = 20;

	D3DXVECTOR3 vOut;

	for(int z = 0; z < VTXCNTZ - 1; ++z)
	{
		for(int x = 0; x < VTXCNTX - 1; ++x)
		{
			int iIndex = z * VTXCNTX + x;

			// 오른쪽 위
			if(D3DXIntersectTri(&pVertex[iIndex + VTXCNTX + 1].vPos,
				&pVertex[iIndex + VTXCNTX].vPos,
				&pVertex[iIndex + 1].vPos,
				&vRayPos,
				&vRayDir,
				&fU, &fV, &fDist))
			{
				vOut = pVertex[iIndex + VTXCNTX + 1].vPos 
					+ (pVertex[iIndex + VTXCNTX].vPos - pVertex[iIndex + VTXCNTX + 1].vPos) * fU
					+ (pVertex[iIndex + 1].vPos - pVertex[iIndex + VTXCNTX + 1].vPos) * fV;

				return;
			}

			// 왼쪽 아래
			if(D3DXIntersectTri(&pVertex[iIndex].vPos,
				&pVertex[iIndex + 1].vPos,
				&pVertex[iIndex + VTXCNTX].vPos,
				&vRayPos,
				&vRayDir,
				&fU, &fV, &fDist))
			{
				vOut = pVertex[iIndex].vPos 
					+ (pVertex[iIndex + 1].vPos - pVertex[iIndex].vPos) * fU
					+ (pVertex[iIndex +	VTXCNTX].vPos - pVertex[iIndex].vPos) * fV;

				return;
			}

		}
	}
	
}

void CBackground::AddTerrain( int iX, int iZ )
{
	MAPCOMPONENT::iterator iter = m_mapComponent.find(L"Tex Terrain");

	if (iter != m_mapComponent.end())
	{
		Engine::Safe_Delete(iter->second);
		m_mapComponent.erase(iter);
	}

	Engine::CComponent*		pResources = NULL;

	pResources = Engine::CRcTerrain::Create(m_pDevice, iX, iZ, 1);

	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pResources);

	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Tex Terrain", pResources));	
}

HRESULT CBackground::Initialize( void )
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	ZeroMemory(m_fAngle, sizeof(float) * 3);
	m_fDistance = 10.f;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);

	m_vAt = D3DXVECTOR3(0.f, -1.f, 1.f);
	D3DXVec3Normalize(&m_vAt, &m_vAt);

	m_vEye = m_vAt * -m_fDistance;
	
	D3DXMatrixLookAtLH(&matView, &m_vEye, &D3DXVECTOR3(0.f, 0.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f));

	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	// 투영행렬 함수
	D3DXMatrixPerspectiveFovLH(&matProj, 
		D3DXToRadian(45.f),					// fovY 값
		float(WINCX) / float(WINCY),		// Aspect값
		1.f,								// near 평면의 z값
		1000.f);							// far 평면의 z값

	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	return S_OK;
}

void CBackground::Update( void )
{
	
}

void CBackground::Render( void )
{
	if (m_pBuffer != NULL)
		m_pBuffer->Render();
}

CBackground* CBackground::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CBackground* pBack = new CBackground(pDevice);

	if (FAILED(pBack->Initialize()))
		Engine::Safe_Delete(pBack);

	return pBack;
}
