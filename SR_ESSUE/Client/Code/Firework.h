/*!
 * \file Firework.h
 * \date 2017/01/22 18:16
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 원으로 퍼져나가는 이펙트
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Firework_h__
#define Firework_h__

#include "ParticleSystem.h"

namespace Engine
{
	class CInfoSubject;
	class CTimeMgr;
}

class CCameraObserver;

class CFirework
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
	virtual HRESULT Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin, int iCount);
	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

public:
	static CFirework*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, int iCount);

private:
	explicit CFirework(LPDIRECT3DDEVICE9 pDevice);

public:
	~CFirework(void);
};

#endif // Firework_h__