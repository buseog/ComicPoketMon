/*!
 * \file MultiGameObject.h
 * \date 2017/01/14 3:29
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief ��Ƽ ������Ʈ Ŭ����
 *
 * TODO: long description
 *
 * \note ���� ���۰� �ƴ� ���� ���۸� ���� Ŭ�������� ������� �� ���� Ŭ����
*/

#ifndef MultiGameObject_h__
#define MultiGameObject_h__

#include "GameObject.h"

// �Ŵ���
#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Include.h"
#include "ZFrustum.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "Layer.h"

// ������Ʈ
#include "Transform.h"
#include "Status.h"
#include "Sprite.h"
#include "BoundBox.h"

// ī�޶�
#include "InfoSubject.h"
#include "CameraObserver.h"

// ĳ���� ����
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