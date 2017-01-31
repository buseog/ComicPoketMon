/*!
 * \file Hit.h
 * \date 2017/01/24 21:58
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 피격 이펙트를 나타낼 클래스
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Hit_h__
#define Hit_h__

#include "ParticleSystem.h"

namespace Engine
{
	class CInfoSubject;
	class CBoundBox;
	class CTimeMgr;
}

class CCameraObserver;

class CHit
	:public Engine::CParticleSystem
{
private:
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

	D3DXVECTOR3					m_vOrigin;
	D3DXVECTOR3					m_vDir;

public:
	void	ResetParticle(Engine::ATTRIBUTE* pAttribute);
	void	Update(void);

public:
	virtual HRESULT Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir);
	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

public:
	static CHit*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir);

private:
	explicit CHit(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CHit(void);
};

#endif // Hit_h__