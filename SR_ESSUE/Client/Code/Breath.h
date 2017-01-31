/*!
 * \file Breath.h
 * \date 2017/01/23 0:19
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 일직선으로 내뿜는 이펙트
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Breath_h__
#define Breath_h__

#include "ParticleSystem.h"
#include "Export_Function.h"

namespace Engine
{
	class CLayer;
	class CInfoSubject;
	class CTimeMgr;
	class CTransform;
}

class CCameraObserver;

class CBreath
	:public Engine::CParticleSystem
{
private:
	Engine::CLayer*				m_pLayer;
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

	Engine::CTransform*			m_pBoss;
	Engine::CTransform*			m_ptarget;

	bool						m_bColCheck;

public:
	void	ResetParticle(Engine::ATTRIBUTE* pAttribute);
	void	Update(void);

public:
	virtual HRESULT Initialize(const wstring& wstrKey,  Engine::CTransform* pBoss, Engine::CTransform* pTarget, int iCount, Engine::CLayer* pLayer);
	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

public:
	static CBreath*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, Engine::CTransform* pBoss, Engine::CTransform* pTarget, int iCount, Engine::CLayer* pLayer);

private:
	explicit CBreath(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBreath(void);
};

#endif // Breath_h__
