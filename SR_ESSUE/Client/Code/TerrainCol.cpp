#include "stdafx.h"
#include "TerrainCol.h"

#include "Export_Function.h"
#include "Include.h"
#include "SoundMgr.h"
CTerrainCol::CTerrainCol(void)
: m_bStepOnTerrain(false)
, m_pPos(NULL)
, m_pTerrainVtx(NULL)
{

}

CTerrainCol::~CTerrainCol(void)
{
	Release();
}

void CTerrainCol::Update(void)
{

	int	iIndex = (int(m_pPos->z) / VTXITV) * VTXCNTX + (int(m_pPos->x) / VTXITV);

	if (iIndex < 0 || (iIndex + VTXCNTX) > VTXCNTX * VTXCNTZ)
	{
		m_pPos->y -= 0.1f;
		m_bStepOnTerrain = false;
		return;
	}
	if (m_pPos->x < m_pTerrainVtx[0].vPos.x || m_pPos->x > m_pTerrainVtx[VTXCNTX - 1].vPos.x)
	{
		m_pPos->y -= 0.1f;
		m_bStepOnTerrain = false;
		return;
	}

	float fRatioX = (m_pPos->x - m_pTerrainVtx[iIndex + VTXCNTX].vPos.x) / VTXITV;
	float fRatioZ = (m_pTerrainVtx[iIndex + VTXCNTX].vPos.z - m_pPos->z)  / VTXITV;

	D3DXPLANE		Plane;

	// 오른쪽 위
	if(fRatioX > fRatioZ)
	{
		D3DXPlaneFromPoints(&Plane, 
			&m_pTerrainVtx[iIndex + VTXCNTX].vPos,
			&m_pTerrainVtx[iIndex + VTXCNTX + 1].vPos,
			&m_pTerrainVtx[iIndex + 1].vPos);
	}
	// 왼쪽 아래
	else
	{
		D3DXPlaneFromPoints(&Plane, 
			&m_pTerrainVtx[iIndex + VTXCNTX].vPos,
			&m_pTerrainVtx[iIndex + 1].vPos,
			&m_pTerrainVtx[iIndex].vPos);
	}

	if(m_pPos->y <= ((-Plane.a * m_pPos->x - Plane.c * m_pPos->z - Plane.d) / Plane.b) + 0.3f)
	{
		m_pPos->y = ((-Plane.a * m_pPos->x - Plane.c * m_pPos->z - Plane.d) / Plane.b) + 0.3f;
		m_bStepOnTerrain = true;

	}
	else if(m_pPos->y > ((-Plane.a * m_pPos->x - Plane.c * m_pPos->z - Plane.d) / Plane.b) + 0.3f)
	{
		m_bStepOnTerrain = false;
	}
	else
	{
		m_bStepOnTerrain = false;
	}
}

Engine::CCollision* CTerrainCol::Clone(void)
{
	++(*m_pwRefCnt);

	return new CTerrainCol(*this);
}

CTerrainCol* CTerrainCol::Create(void)
{
	return new CTerrainCol;	
}

void CTerrainCol::SetColInfo(D3DXVECTOR3* pPos, const Engine::VTXTEX* pTerrainVtx)
{
	m_pPos			= pPos;
	m_pTerrainVtx	= pTerrainVtx;
}

void CTerrainCol::Release(void)
{
	if((*m_pwRefCnt) == 0)
	{
		Engine::CCollision::Release();
	}

	else
		--(*m_pwRefCnt);
}

bool CTerrainCol::GetColTerrainStat(void)
{
	return m_bStepOnTerrain;
}