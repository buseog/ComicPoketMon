#include "StdAfx.h"
#include "ZFrustum.h"
#include "Engine_Include.h"

IMPLEMENT_SINGLETON(CZFrustum);

CZFrustum::CZFrustum(void)
{
	ZeroMemory(m_Vtx, sizeof(D3DXVECTOR3)*8);
	ZeroMemory(m_Plane, sizeof(D3DXPLANE)*6);
}

CZFrustum::~CZFrustum(void)
{
}

HRESULT CZFrustum::MakePlane( D3DXMATRIX* pViewProj )
{
	m_Vtx[0].x = -1.0f;	
	m_Vtx[0].y = 1.0f;
	m_Vtx[0].z = 0.0f;

	m_Vtx[1].x = 1.0f;	
	m_Vtx[1].y = 1.0f;	
	m_Vtx[1].z = 0.0f;

	m_Vtx[2].x = 1.0f;	
	m_Vtx[2].y = -1.0f;	
	m_Vtx[2].z = 0.0f;
	
	m_Vtx[3].x = -1.0f;	
	m_Vtx[3].y = -1.0f;	
	m_Vtx[3].z = 0.0f;

	m_Vtx[4].x = -1.0f;	
	m_Vtx[4].y = 1.0f;	
	m_Vtx[4].z = 1.0f;

	m_Vtx[5].x = 1.0f;	
	m_Vtx[5].y =  1.0f;	
	m_Vtx[5].z = 1.0f;

	m_Vtx[6].x = 1.0f;	
	m_Vtx[6].y = -1.0f;	
	m_Vtx[6].z = 1.0f;

	m_Vtx[7].x = -1.0f;	
	m_Vtx[7].y = -1.0f;	
	m_Vtx[7].z = 1.0f;

	D3DXMATRIX matRViewProj;
	D3DXMatrixInverse(&matRViewProj, NULL, pViewProj);

	for (int i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&m_Vtx[i], &m_Vtx[i], &matRViewProj);
	}

	D3DXPlaneFromPoints(&m_Plane[0], &m_Vtx[4], &m_Vtx[5], &m_Vtx[1]);	// 상 평면(top)
	D3DXPlaneFromPoints(&m_Plane[1], &m_Vtx[3], &m_Vtx[2], &m_Vtx[6]);	// 하 평면(bottom)
	D3DXPlaneFromPoints(&m_Plane[2], &m_Vtx[0], &m_Vtx[1], &m_Vtx[2]);	// 근 평면(near)
	D3DXPlaneFromPoints(&m_Plane[3], &m_Vtx[7], &m_Vtx[6], &m_Vtx[5]);	// 원 평면(far)
	D3DXPlaneFromPoints(&m_Plane[4], &m_Vtx[4], &m_Vtx[0], &m_Vtx[3]);	// 좌 평면(left)
	D3DXPlaneFromPoints(&m_Plane[5], &m_Vtx[1], &m_Vtx[5], &m_Vtx[6]);	// 우 평면(right)


	return S_OK;	
}

bool CZFrustum::IsIn( D3DXVECTOR3* pPos )
{
	float fDistance;

	for (int i = 0; i < 6; ++i)
	{
		fDistance = D3DXPlaneDotCoord(&m_Plane[i], pPos);

		if (fDistance > 0)
			return false;
	}
	return true;
}

bool CZFrustum::IsInSphere(D3DXVECTOR3* pPos, float fRadius)
{
	float fDistance;

	for (int i = 0; i < 6; ++i)
	{
		fDistance = D3DXPlaneDotCoord(&m_Plane[i], pPos);

		if (fDistance > fRadius)
			return false;
	}
	return true;
}
