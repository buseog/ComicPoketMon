/*!
 * \file Projectile.h
 * \date 2017/01/16 22:50
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \투사체, 이펙트 등 화면상에 출력될 오브젝트들의 부모클래스입니다.
*/

#ifndef Projectile_h__
#define Projectile_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CResourceMgr;
	class CTimeMgr;
	class CTransform;
	class CInfoSubject;
}

class CCameraObserver;
class CProjectile 
	: public Engine::CGameObject
{
protected:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CTransform*			m_pInfo;
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;

protected:
	Engine::VTXTEX*				m_Vertex;
	Engine::VTXTEX*				m_ConvertVertex;
	DWORD						m_dwVtxCnt;

	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

public:
	void				Release(void);
	void				SetTransform(void);
	HRESULT				AddComponent(void);


protected:
	explicit CProjectile(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CProjectile(void);

};
#endif // Projectile_h__