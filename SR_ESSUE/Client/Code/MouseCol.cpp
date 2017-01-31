#include "stdafx.h"
#include "MouseCol.h"

#include "Include.h"
#include "CameraObserver.h"
#include "Export_Function.h"
#include "InfoSubject.h"

CMouseCol::CMouseCol(void)
: m_pInfoSubject(Engine::Get_InfoSubject())
, m_pCameraObserver(NULL)
, m_bDrag(false)
{


}

CMouseCol::~CMouseCol(void)
{
	Release();
}

POINT CMouseCol::GetMousePos(void)
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return pt;
}

CMouseCol* CMouseCol::Create(void)
{
	CMouseCol*	pCollision = new CMouseCol;

	if(FAILED(pCollision->Initialize()))
		Engine::Safe_Delete(pCollision);

	return pCollision;

}

Engine::CCollision* CMouseCol::Clone(void)
{
	++(*m_pwRefCnt);

	return new CMouseCol(*this);
}

void CMouseCol::PickTerrain(D3DXVECTOR3* pOut, const Engine::VTXTEX* pTerrainTtx)
{
	Translation_ViewSpace();

	D3DXMATRIX	matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	Translation_Local(&matIdentity);

	const Engine::VTXTEX*		pVertex = pTerrainTtx;

	float	fU, fV, fDist;

	for(int z = 0; z < VTXCNTZ - 1; ++z)
	{
		for(int x = 0; x < VTXCNTX - 1; ++x)
		{
			int iIndex = z * VTXCNTX + x;

			// 오른쪽 위
			if(D3DXIntersectTri(&pVertex[iIndex + VTXCNTX + 1].vPos,
				&pVertex[iIndex + VTXCNTX].vPos,
				&pVertex[iIndex + 1].vPos,
				&m_vRayPos,
				&m_vRayDir,
				&fU, &fV, &fDist))
			{
				*pOut = pVertex[iIndex + VTXCNTX + 1].vPos 
					+ (pVertex[iIndex + VTXCNTX].vPos - pVertex[iIndex + VTXCNTX + 1].vPos) * fU
					+ (pVertex[iIndex + 1].vPos - pVertex[iIndex + VTXCNTX + 1].vPos) * fV;

				return;
			}

			// 왼쪽 아래
			if(D3DXIntersectTri(&pVertex[iIndex].vPos,
				&pVertex[iIndex + 1].vPos,
				&pVertex[iIndex + VTXCNTX].vPos,
				&m_vRayPos,
				&m_vRayDir,
				&fU, &fV, &fDist))
			{
				*pOut = pVertex[iIndex].vPos 
					+ (pVertex[iIndex + 1].vPos - pVertex[iIndex].vPos) * fU
					+ (pVertex[iIndex +	VTXCNTX].vPos - pVertex[iIndex].vPos) * fV;

				return;
			}
		}
	}
}

void CMouseCol::PickObject(D3DXVECTOR3* pOut, const Engine::VTXTEX* pVertex, const D3DXMATRIX* pMatWorld)
{
	Translation_ViewSpace();
	Translation_Local(pMatWorld);

	float	fU, fV, fDist;

	// 오른쪽 위
	if(D3DXIntersectTri(&pVertex[1].vPos,
		&pVertex[0].vPos,
		&pVertex[2].vPos,
		&m_vRayPos,
		&m_vRayDir,
		&fU, &fV, &fDist))
	{
		*pOut = pVertex[1].vPos 
			+ (pVertex[0].vPos - pVertex[1].vPos) * fU
			+ (pVertex[2].vPos - pVertex[1].vPos) * fV;

		return;
	}

	// 왼쪽 아래
	if(D3DXIntersectTri(&pVertex[3].vPos,
		&pVertex[2].vPos,
		&pVertex[0].vPos,
		&m_vRayPos,
		&m_vRayDir,
		&fU, &fV, &fDist))
	{
		*pOut = pVertex[3].vPos 
			+ (pVertex[2].vPos - pVertex[3].vPos) * fU
			+ (pVertex[0].vPos - pVertex[3].vPos) * fV;
		return;
	}
}

HRESULT CMouseCol::Initialize(void)
{	
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	return S_OK;
}

void CMouseCol::Translation_ViewSpace(void)
{
	POINT	ptMouse = GetMousePos();

	D3DXMATRIX	matProj = *m_pCameraObserver->GetProj();

	D3DXVECTOR3	vTemp;

	// 뷰 포트 영역에서 투영 영역으로 마우스 변환
	vTemp.x = (float(ptMouse.x)  / (WINCX >> 1) - 1.f) / matProj._11;
	vTemp.y = (float(-ptMouse.y) / (WINCY >> 1) + 1.f) / matProj._22;
	vTemp.z = 1.f;


	m_vRayPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vRayDir   = vTemp - m_vRayPos;
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);
}

void CMouseCol::Translation_Local(const D3DXMATRIX* pWorld)
{
	D3DXMATRIX	matView = *m_pCameraObserver->GetView();
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformCoord(&m_vRayPos, &m_vRayPos, &matView);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matView);

	D3DXMATRIX		matWorld;
	D3DXMatrixInverse(&matWorld, NULL, pWorld);
	D3DXVec3TransformCoord(&m_vRayPos, &m_vRayPos, &matWorld);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matWorld);
}

void CMouseCol::Release(void)
{
	if((*m_pwRefCnt) == 0)
	{
		Engine::CCollision::Release();
		Engine::Safe_Delete(m_pCameraObserver);
	}

	else
		--(*m_pwRefCnt);
}

bool CMouseCol::PickUi( RECT* pRc, D3DXVECTOR3* pPos )
{
	POINT	ptMouse = GetMousePos();

	if(PtInRect(pRc, ptMouse))
	{
		if (m_bDrag == false)
		{
			m_bDrag = true;

			m_vMousePos.x = (float)ptMouse.x;
			m_vMousePos.y = (float)ptMouse.y;
			m_vMousePos.z = 0.f;
		}
		else if (m_bDrag == true)
		{
			pPos->x -= m_vMousePos.x - (float)ptMouse.x;
			pPos->y -= m_vMousePos.y - (float)ptMouse.y;

			m_vMousePos.x = (float)ptMouse.x;
			m_vMousePos.y = (float)ptMouse.y;
		}
	}
	
	return false;
}

void CMouseCol::SetDrag( void )
{
	m_bDrag = false;
	m_vMousePos = D3DXVECTOR3(0.f, 0.f, 0.f);
}
