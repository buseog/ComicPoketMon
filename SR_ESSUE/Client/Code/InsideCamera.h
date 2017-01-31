#ifndef InsideCamera_h__
#define InsideCamera_h__

#include "BasicCamera.h"

namespace	Engine
{
	class CTimeMgr;
	class CTransform;
	class CInfoSubject;
}

class CInsideCamera 
	: public CBasicCamera
{
private:
	explicit CInsideCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CInsideCamera(void);

public:
	static CInsideCamera*	Create(LPDIRECT3DDEVICE9 pDevice, 
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
	bool		m_bRbuttonDown;
	POINT		m_ptOriginPos;
	float		m_fTargetDistance;
	float       m_fCameraDistance;
	float		m_fCameraSpeed;
	float		m_fAngle;
	float		m_fAngleY;
	float		m_fMaxDitance;
	float		m_fNearDist;
	float		m_fFarDist;

	bool		m_bKeyInput;

	int			m_iKeyDown;
};

#endif // InsideCamera_h__
