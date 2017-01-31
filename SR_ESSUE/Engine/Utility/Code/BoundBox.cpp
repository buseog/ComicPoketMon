#include "BoundBox.h"

Engine::CBoundBox::CBoundBox(void)
: vCenter(0.f, 0.f, 0.f)
, fRadius(0.f)
, vMin(0.f, 0.f, 0.f)
, vMax(0.f, 0.f, 0.f)
, vSize(2.f, 2.f, 1.f)
{
}

Engine::CBoundBox::~CBoundBox(void)
{
}

HRESULT Engine::CBoundBox::Initialize( D3DXVECTOR3* pPos , D3DXVECTOR3* pScale)
{
	vCenter = *pPos;

	vSize.x *= pScale->x * 1.5f;
	vSize.y *= pScale->y * 1.5f;
	vSize.z *= pScale->z * 1.5f;


	fRadius = sqrt(vSize.x * vSize.x + vSize.y * vSize.y + vSize.z * vSize.z);

	vMin = vCenter - vSize;
	vMax = vCenter + vSize;
 
	return S_OK;
}


void Engine::CBoundBox::Update(  D3DXVECTOR3* pPos )
{
	vCenter = *pPos;
	vMin = vCenter - vSize;
	vMax = vCenter + vSize;
}

Engine::CBoundBox* Engine::CBoundBox::Create( D3DXVECTOR3* pPos, D3DXVECTOR3* pScale )
{
	CBoundBox* pBoundBox = new CBoundBox();

	if (FAILED(pBoundBox->Initialize(pPos, pScale)))
		Engine::Safe_Delete(pBoundBox);

	return pBoundBox;
}

bool Engine::CBoundBox::Inside(D3DXVECTOR3* vPos)
{
	if (vPos->x < vMin.x || vPos->x > vMax.x)
		return false;

	if (vPos->y < vMin.y || vPos->y > vMax.y)
		return false;

	if (vPos->z < vMin.z || vPos->z > vMax.z)
		return false;

	return true;
}
