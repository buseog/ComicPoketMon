/*!
 * \file Lightning.h
 * \date 2017/01/25 0:57
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 피카츄 전기공격에 쓰일 이펙트
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Lightning_h__
#define Lightning_h__

#include "ParticleSystem.h"

namespace Engine
{
	class CInfoSubject;
	class CBoundBox;
	class CTimeMgr;
}

class CCameraObserver;

class CLightning
	:public Engine::CParticleSystem
{
private:
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

	D3DXVECTOR3					m_vOrigin;

public:
	void	ResetParticle(Engine::ATTRIBUTE* pAttribute);
	void	Update(void);

public:
	virtual HRESULT Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin);
	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

public:
	static CLightning*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin);

private:
	explicit CLightning(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CLightning(void);
};

#endif // Lightning_h__