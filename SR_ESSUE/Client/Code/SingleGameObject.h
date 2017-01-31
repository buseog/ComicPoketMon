/*!
 * \file SingleGameObject.h
 * \date 2017/01/14 3:48
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 싱글 오브젝트 클래스
 *
 * TODO: long description
 *
 * \note 단일 버퍼를 가진 클래스들의 상위 클래스
*/

#ifndef SingleGameObject_h__
#define SingleGameObject_h__

#include "GameObject.h"

// 매니저
#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"
#include "ZFrustum.h"
#include "Include.h"

// 컴포넌트
#include "Transform.h"
#include "InfoSubject.h"
#include "BoundBox.h"
#include "Status.h"


// 카메라
#include "CameraObserver.h"

// 캐릭터 관련
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