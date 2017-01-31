/*!
 * \file ZFrustum.h
 * \date 2017/01/14 4:55
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief ����ü �ø� �̱��� Ŭ����
 *
 * TODO: long description
 *
 * \note ����ü�� �����ϴ� ������ ����� ������ ����������.
*/
#ifndef ZFrustum_h__
#define ZFrustum_h__

#include "Engine_Include.h"

class CZFrustum
{
	DECLARE_SINGLETON(CZFrustum)

private:
	D3DXVECTOR3 m_Vtx[8];
	D3DXPLANE	m_Plane[6];

public:
	HRESULT MakePlane(D3DXMATRIX* pProj);
	bool	IsIn(D3DXVECTOR3* pPos);
	bool	IsInSphere(D3DXVECTOR3* pPos, float fRadius);

public:
	CZFrustum(void);
	~CZFrustum(void);
};

#endif // ZFrustum_h__
