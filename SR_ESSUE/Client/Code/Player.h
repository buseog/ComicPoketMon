/*!
 * \file Player.h
 * \date 2016/12/26 16:45
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Player_h__
#define Player_h__

#include "MultiGameObject.h"

namespace Engine
{
	class CResourceMgr;
	class CTimeMgr;
	class CManagement;
	class CTexture;
	class CVIBuffer;
	class CCubeMotion;

	class CTransform;
	class CStatus;
	class CSprite;
	class CInfoSubject;
}

class CStaticCamera;
class CCameraObserver;
class CCollisionMgr;
class CTerrainCol;
class CMouseCol;
class CAction;

class CPlayer 
	: public CMultiGameObject
{
private:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CManagement*		m_pManagement;
	Engine::CTimeMgr*			m_pTimeMgr;

	Engine::CTransform*			m_pInfo;
	Engine::CStatus*			m_pStat;
	Engine::CSprite*			m_pSprite;

	Engine::CInfoSubject*		m_pInfoSubject;
	Engine::CCubeMotion*		m_pResource;
	const Engine::VTXTEX*		m_pTerrainVtx;

	CCameraObserver*			m_pCameraObserver;

	float						m_fSpeed;
	bool						m_bMove;

	CCollisionMgr*				m_pCollisionMgr;
	CTerrainCol*				m_pTerrainCol;
	CMouseCol*					m_pMouseCol;

	D3DXVECTOR3					m_vDestPos;
	

private:
	void		Move(void);

private:
	HRESULT		Initialize(void);
	void		KeyInput(void);
	void		SetDirection(void);
	void		Load(void);

public:
	void		Update(void);
	void		Render(void);
	void		Release(void);
	HRESULT		AddComponent(void);

public:
	static	CPlayer*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit	CPlayer(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CPlayer(void);

};

#endif // Player_h__