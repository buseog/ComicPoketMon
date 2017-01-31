/*!
 * \file Gather.h
 * \date 2017/01/24 2:36
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Gather_h__
#define Gather_h__

#include "ParticleSystem.h"

namespace Engine
{
	class CInfoSubject;
	class CTimeMgr;
}

class CCameraObserver;

class CGather
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
	virtual HRESULT Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDIr, int iCount);
	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

public:
	static CGather*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDIr, int iCount);

private:
	explicit CGather(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CGather(void);
};

#endif // Gather_h__