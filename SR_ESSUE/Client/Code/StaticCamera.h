#ifndef StaticCamera_h__
#define StaticCamera_h__

#include "BasicCamera.h"

namespace	Engine
{
	class CTimeMgr;
	class CTransform;
	class CInfoSubject;
}

class CStaticCamera 
	: public CBasicCamera
{
private:
	explicit CStaticCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CStaticCamera(void);

public:
	static CStaticCamera*	Create(LPDIRECT3DDEVICE9 pDevice, 
									const Engine::CTransform* pTargetInfo);

	void	SetCameraTarget(const Engine::CTransform* pTargetInfo);

	POINT GetMousePos(void);

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

#endif // StaticCamera_h__