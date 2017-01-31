/*!
 * \file HighlightCamera.h
 * \date 2017/01/25 0:50
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef HighlightCamera_h__
#define HighlightCamera_h__

#include "BasicCamera.h"

namespace	Engine
{
	class CTimeMgr;
	class CTransform;
	class CInfoSubject;
}

class CHighlightCamera
	: public CBasicCamera
{
private:
	explicit CHighlightCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CHighlightCamera(void);

public:
	static CHighlightCamera*	Create(LPDIRECT3DDEVICE9 pDevice, 
		const Engine::CTransform* pTargetInfo);

	void	SetCameraTarget(const Engine::CTransform* pTargetInfo);

public:
	virtual HRESULT		Initialize(void);
	virtual void		Update(void);

private:
	void		TargetRenewal(void);

private:
	Engine::CTimeMgr*				m_pTimeMgr;
	const Engine::CTransform*		m_pTargetInfo;
	Engine::CInfoSubject*			m_pInfoSubject;


private:
	float							m_fTime;
	float							m_fSwing;

};

#endif // HighlightCamera_h__