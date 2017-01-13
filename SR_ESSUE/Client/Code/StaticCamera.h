#ifndef StaticCamera_h__
#define StaticCamera_h__

#include "Camera.h"


namespace	Engine
{
	class CTimeMgr;
	class CTransform;
	class CInfoSubject;
}

class CStaticCamera : public Engine::CCamera
{
private:
	explicit CStaticCamera(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CStaticCamera(void);

public:
	static CStaticCamera*	Create(LPDIRECT3DDEVICE9 pDevice, 
									const Engine::CTransform* pTargetInfo);

	void	SetCameraTarget(const Engine::CTransform* pTargetInfo);

public:
	virtual HRESULT		Initialize(void);
	virtual void		Update(void);

private:
	void		KeyCheck(void);
	void		TargetRenewal(void);

private:
	Engine::CTimeMgr*				m_pTimeMgr;
	const Engine::CTransform*		m_pTargetInfo;
	Engine::CInfoSubject*			m_pInfoSubject;

private:
	float		m_fTargetDistance;
	float		m_fCameraSpeed;
	float		m_fAngle;
};

#endif // StaticCamera_h__