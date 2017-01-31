/*!
 * \file MouseCol.h
 * \date 2017/01/14 22:39
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef MouseCol_h__
#define MouseCol_h__


#include "Collision.h"

namespace Engine
{
	class CInfoSubject;
}

class CCameraObserver;

class CMouseCol
	:public Engine::CCollision
{
private:
	Engine::CInfoSubject*			m_pInfoSubject;
	CCameraObserver*				m_pCameraObserver;

	bool		m_bDrag;
	D3DXVECTOR3 m_vMousePos;
	D3DXVECTOR3 m_vRayPos;
	D3DXVECTOR3	m_vRayDir;

private:
	HRESULT		Initialize(void);
	void		Translation_ViewSpace(void);
	void		Translation_Local(const D3DXMATRIX* pWorld);
	void		Release(void);

public:
	void PickTerrain(D3DXVECTOR3* pOut, const Engine::VTXTEX* pTerrainTtx);
	void PickObject(D3DXVECTOR3* pOut, const Engine::VTXTEX* pVertex, const D3DXMATRIX* pMatWorld);
	bool PickUi(RECT* pRc, D3DXVECTOR3* pPos);
	void SetDrag(void);

public:
	virtual Engine::CCollision* Clone(void);
	static	POINT		GetMousePos(void);
	static	CMouseCol*	Create(void);

private:
	CMouseCol(void);

public:
	virtual ~CMouseCol(void);
};

#endif // MouseCol_h__
