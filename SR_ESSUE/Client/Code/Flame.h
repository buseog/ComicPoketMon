/*!
 * \file Flame.h
 * \date 2017/01/25 2:28
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 불타오르는 이펙트
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Flame_h__
#define Flame_h__

#include "ParticleSystem.h"

namespace Engine
{
	class CInfoSubject;
	class CBoundBox;
	class CTimeMgr;
}

class CCameraObserver;

class CFlame
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
	static CFlame*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin);

private:
	explicit CFlame(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CFlame(void);
};

#endif // Flame_h__