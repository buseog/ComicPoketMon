#include "StdAfx.h"
#include "BoundCol.h"
#include "BoundBox.h"

CBoundCol::CBoundCol(void)
{
}

CBoundCol::~CBoundCol(void)
{
	Release();
}

HRESULT CBoundCol::Initialize( void )
{
	return S_OK;
}

void CBoundCol::Release( void )
{
	if((*m_pwRefCnt) == 0)
	{
		Engine::CCollision::Release();
	}

	else
		--(*m_pwRefCnt);
}

bool CBoundCol::ColSphere( Engine::CBoundBox* pTemp, Engine::CBoundBox* pDest )
{
	D3DXVECTOR3 vTemp = pDest->vCenter - pTemp->vCenter;

	float fDis = vTemp.x * vTemp.x + vTemp.y * vTemp.y + vTemp.z * vTemp.z;
	float fRadius = (pTemp->fRadius + pDest->fRadius) * (pTemp->fRadius + pDest->fRadius);

	if (fRadius > fDis)
		return true;

	return false;
}

bool CBoundCol::ColAABB( Engine::CBoundBox* pTemp, Engine::CBoundBox* pDest )
{
	if (pTemp->vCenter.x < pDest->vMin.x || pTemp->vCenter.x > pDest->vMax.x)
		return false;

	if (pTemp->vCenter.y < pDest->vMin.y || pTemp->vCenter.y > pDest->vMax.y)
		return false;

	if (pTemp->vCenter.z < pDest->vMin.z || pTemp->vCenter.z > pDest->vMax.z)
		return false;

	return true;
}

Engine::CCollision* CBoundCol::Clone( void )
{
	++(*m_pwRefCnt);

	return new CBoundCol(*this);
}

CBoundCol* CBoundCol::Create( void )
{
	CBoundCol*	pCollision = new CBoundCol;

	if(FAILED(pCollision->Initialize()))
		Engine::Safe_Delete(pCollision);

	return pCollision;
}

bool CBoundCol::ColBoundBox( Engine::CBoundBox* pTemp, Engine::CBoundBox* pDest )
{
	if (ColSphere(pTemp, pDest))
	{
		if (ColAABB(pTemp, pDest))
		{
			return true;
		}
	}

	return false;
}
