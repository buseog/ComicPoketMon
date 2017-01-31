/*!
 * \file Bullet.h
 * \date 2017/01/23 22:55
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 일정 방향으로 날아가는 총알
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Bullet_h__
#define Bullet_h__

#include "ParticleSystem.h"

namespace Engine
{
	class CInfoSubject;
	class CBoundBox;
	class CTimeMgr;
}

class CCameraObserver;

class CBullet
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
	virtual HRESULT Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir, int iCount);
	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

public:
	CBullet* Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir, int iCount);

private:
	explicit CBullet(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBullet(void);
};

#endif // Bullet_h__