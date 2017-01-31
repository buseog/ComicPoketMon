/*!
 * \file MultiGameObject.h
 * \date 2017/01/14 3:29
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 멀티 오브젝트 클래스
 *
 * TODO: long description
 *
 * \note 단일 버퍼가 아닌 다중 버퍼를 가진 클래스들을 대상으로 한 상위 클래스
*/

#ifndef MultiGameObject_h__
#define MultiGameObject_h__

#include "GameObject.h"

// 매니저
#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Include.h"
#include "ZFrustum.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "Layer.h"

// 컴포넌트
#include "Transform.h"
#include "Status.h"
#include "Sprite.h"
#include "BoundBox.h"

// 카메라
#include "InfoSubject.h"
#include "CameraObserver.h"

// 캐릭터 관련
#include "CubeMotion.h"
#include "CubeObj.h"
#include "CubeTex.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Inven.h"

class CMultiGameObject
	: public Engine::CGameObject
{
protected:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CManagement*		m_pManagement;
	Engine::CTimeMgr*			m_pTimeMgr;

	Engine::CTransform*			m_pInfo;
	Engine::CStatus*			m_pStat;
	Engine::CSprite*			m_pSprite;
	Engine::CBoundBox*			m_pBox;

	Engine::CInfoSubject*		m_pInfoSubject;
	Engine::CCubeMotion*		m_pResource;
	const Engine::VTXTEX*		m_pTerrainVtx;

	CSoundMgr*					m_pSound;

	CCameraObserver*			m_pCameraObserver;
	CCollisionMgr*				m_pCollisionMgr;
	CZFrustum*					m_pZFrustum;
	wstring						m_wstrObjKey;
	wstring						m_wstrStatekey;
	

public:
	void	Release(void);
	void	LoadFile(wstring wstrLoadKey);
	void	SetPos(D3DXVECTOR3	vPos);

	void	SetSprite(wstring wstrStateKey);

public:
	virtual HRESULT Initialize( void );
	virtual void Update( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj );
	virtual void Render( void );
	void	SetHp(float Damage);

	wstring		GetObjKey(void);
	virtual DWORD		GetType(void);
	float		GetHp(void);

protected:
	explicit	CMultiGameObject(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CMultiGameObject(void);
};

#endif // MultiGameObject_h__