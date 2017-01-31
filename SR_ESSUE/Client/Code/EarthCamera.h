/*!
 * \file EarthCamera.h
 * \date 2017/01/24 0:38
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 보스의 지구던지기쓸떄 쓸 카메라
 *
 * TODO: long description
 *
 * \note
*/

#ifndef EarthCamera_h__
#define EarthCamera_h__

#include "BasicCamera.h"

namespace	Engine
{
	class CTimeMgr;
	class CTransform;
	class CInfoSubject;
}

class CEarthCamera
	: public CBasicCamera
{
private:
	Engine::CTimeMgr*				m_pTimeMgr;
	Engine::CInfoSubject*			m_pInfoSubject;
	Engine::CTransform*				m_pTargetInfo;

	float							m_fTime;
	float							m_fSwing;

private:
	void	TargetRenewal(void);

public:
	void	SetCameraTarget(Engine::CTransform* pTargetInfo);

public:
	virtual HRESULT Initialize(void);
	virtual void	Update(void);

public:
	static CEarthCamera* Create(LPDIRECT3DDEVICE9 pDevice, Engine::CTransform* pTargetInfo);

private:
	explicit CEarthCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CEarthCamera(void);
};

#endif // EarthCamera_h__