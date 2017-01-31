/*!
 * \file Boss.h
 * \date 2017/01/23 4:21
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

#ifndef Boss_h__
#define Boss_h__

#include "MultiGameObject.h"
#include "Player.h"

namespace Engine
{
	class CLayer;
	class CTransform;
	class CMathMgr;
}

class CBoundCol;

class CBoss
	: public CMultiGameObject
{
private:
	Engine::CVIBuffer*			m_pHpBarBuffer;
	Engine::CTexture*			m_pHpBarTexture;

	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;

	Engine::CLayer*				m_pLayer;
	CPlayer*					m_pPlayer;
	Engine::CTransform*			m_pTargetInfo;

	// 충돌 관련
	CBoundCol*					m_pBoundCol;
	DWORD						m_dwType;

	// 패턴관련
	DWORD						m_dwPatten;
	float						m_fPattenTime;
	float						m_fSkillTime;
	bool						m_bEarthThrow;
	bool						m_bColCheck;

private:
	HRESULT		Initialize( Engine::CLayer* pLayer );
	void		Release(void);
	void		Load(void);

	void		SetTransform(void);
	void		SetDirection(void);

public:
	void		Inspect(void);
	
	void		Patrol(void);
	void		Hurricane(void);
	void		Dash(void);
	void		DestroyBeam(void);
	void		EarthThrow(void);

	virtual DWORD		GetType(void);

public:
	HRESULT		AddComponent(void);
	void		Update( void );
	void		Render( void );

public:
	static CBoss* Create(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer);

private:
	explicit CBoss(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBoss(void);
};

#endif // Boss_h__