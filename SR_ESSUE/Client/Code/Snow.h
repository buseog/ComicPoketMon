/*!
 * \file Snow.h
 * \date 2017/01/21 18:54
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief ÇÏ´Ã¿¡¼­ ³»¸®´Â ´«°áÁ¤
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Snow_h__
#define Snow_h__

#include "ParticleSystem.h"

namespace Engine
{
	class CInfoSubject;
	class CBoundBox;
	class CTimeMgr;
}

class CCameraObserver;

class CSnow
	:public Engine::CParticleSystem
{
private:
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

public:
	void	ResetParticle(Engine::ATTRIBUTE* pAttribute);
	void	Update(void);

public:
	virtual HRESULT Initialize(const wstring& wstrKey, Engine::CBoundBox* pBox, int iCount);
	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

public:
	static CSnow*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, Engine::CBoundBox* pBox, int iCount);

private:
	explicit CSnow(LPDIRECT3DDEVICE9 pDevice);

public:
	~CSnow(void);
};

#endif // Snow_h__