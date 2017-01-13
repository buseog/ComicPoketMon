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

#include "GameObject.h"

namespace Engine
{
	class CResourceMgr;
	class CTimeMgr;
	class CManagement;
	class CTexture;
	class CVIBuffer;

	class CTransform;
	class CInfomation;
	class CInfoSubject;
}

class CStaticCamera;
class CCameraObserver;
class CCollisionMgr;
class CTerrainCol;
class CMouseCol;
class CPlayer 
	: public Engine::CGameObject
{
private:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CManagement*		m_pManagement;
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CTransform*			m_pInfo;
	Engine::CInfomation*		m_pStat;
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;
	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

	float						m_fSpeed;
	bool						m_bMove;

	D3DXVECTOR3					m_vDestPos;
	const Engine::VTXTEX*		m_pTerrainVtx;

private:
	Engine::VTXTEX*			m_pVertex;
	Engine::VTXTEX*			m_pConvertVertex;
	DWORD					m_dwVtxCnt;

private:
	void		SetTransform(void);
	void		Move(void);

private:
	HRESULT		Initialize(void);
	void		KeyInput(void);
	void		SetDirection(void);

	void		StaticCamera(void);

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
	~CPlayer(void);

};

#endif // Player_h__