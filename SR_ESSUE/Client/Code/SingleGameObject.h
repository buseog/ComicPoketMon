/*!
 * \file SingleGameObject.h
 * \date 2017/01/14 3:48
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief �̱� ������Ʈ Ŭ����
 *
 * TODO: long description
 *
 * \note ���� ���۸� ���� Ŭ�������� ���� Ŭ����
*/

#ifndef SingleGameObject_h__
#define SingleGameObject_h__

#include "GameObject.h"

// �Ŵ���
#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"
#include "ZFrustum.h"
#include "Include.h"

// ������Ʈ
#include "Transform.h"
#include "InfoSubject.h"
#include "BoundBox.h"
#include "Status.h"


// ī�޶�
#include "CameraObserver.h"

// ĳ���� ����
#include "Texture.h"
#include "Poketmon.h"

namespace Engine
{
	class CManagement;
	class CVIBuffer;

	class CBoundBox;
}

class CCameraObserver;
class CCollisionMgr;

class CSingleGameObject
	: public Engine::CGameObject
{
protected:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CManagement*		m_pManagement;
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CTransform*			m_pInfo;
	Engine::CBoundBox*			m_pBox;

	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;

	DWORD						m_dwVtxCnt;

	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;
	CCollisionMgr*				m_pCollisionMgr;
	CZFrustum*					m_pZFrustum;


public:
	virtual HRESULT		Initialize( void );
	virtual void		Update( void );
	virtual void		Render( void );
	void				Release(void);
	

protected:
	explicit	CSingleGameObject(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CSingleGameObject(void);
};

#endif // SingleGameObject_h__